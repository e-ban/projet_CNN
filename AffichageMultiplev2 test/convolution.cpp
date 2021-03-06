#include "convolutionReLU.h"

void convolutionReLU(  CNN_DATA_OUT_TYPE datain[CNN_IMAGE_IN_SIZE], CNN_DATA_TYPE dataout[CNN_CONV1_OUT_SIZE], CNN_COEFF_TYPE weights[CNN_KERNEL1_SIZE],  CNN_COEFF_TYPE biases[CNN_CONV1_IN_C],  int sel )
  {
    int height_in,width_in,canal_in,height_out, width_out, canal_out;
    if(sel==1){
      height_in = CNN_IMAGE_IN_H;
      width_in = CNN_IMAGE_IN_W;
      canal_in = CNN_IMAGE_IN_C;
      height_out = CNN_CONV1_OUT_H;
      width_out = CNN_CONV1_OUT_W;
      canal_out = CNN_CONV1_OUT_RC;
    }
    else if(sel==2){
      height_in = CNN_CONV2_IN_H;
      width_in = CNN_CONV2_IN_W;
      canal_in = CNN_CONV2_IN_C;
      height_out = CNN_CONV2_OUT_H;
      width_out = CNN_CONV2_OUT_W;
      canal_out = CNN_CONV2_OUT_C;
    }
    else {
      height_in = CNN_CONV3_IN_H;
      width_in = CNN_CONV3_IN_W;
      canal_in = CNN_CONV3_IN_C;
      height_out = CNN_CONV3_OUT_H;
      width_out = CNN_CONV3_OUT_W;
      canal_out = CNN_CONV3_OUT_C;
    }
    CNN_DATA_TYPE s= 0;
    for(int row=0;row<height_out;row++)
    {
      for(int col=0; col<width_out;col++)
      {
        for (int outChannel=0;outChannel<canal_out;outChannel++)
        {
          s=0;
          for (int kerH=-CNN_KERNEL_H/2; kerH<=CNN_KERNEL_H/2;kerH++)
          {
            for (int kerW=-CNN_KERNEL_W/2; kerW<=CNN_KERNEL_W/2;kerW++)
            {
              for(int inChannel=0;inChannel<canal_in;inChannel++)
              {
                if(row+kerH>=0 && row+kerH<height_in && col+kerW>=0 && col+kerW<width_in){
                  s=s+(CNN_DATA_OUT_TYPE)datain[width_in*canal_in*(row+kerH)+canal_in*(col+kerW)+inChannel]*weights[CNN_KERNEL_W*canal_in*canal_out*(kerH+1)+canal_in*canal_out*(kerW+1)+canal_in*inChannel+outChannel];
                }
              }
            }
          }
          s=s+biases[outChannel];
          if(s<0)  s=0;
          dataout[width_out*canal_out*row+canal_out*col+outChannel]=s;
        }
      }
    }
  }
