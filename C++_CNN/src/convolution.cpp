#include "types.h"
#include "convolutionReLU.h"



void convolutionReLU1(
  din_type datain[IMGPROC_IMAGE_IN_SIZE],
  c_type weights[IMGPROC_KERNEL1_SIZE],
  c_type biases[IMGPROC_CONV1_OUT_C],
  dout_type dataout[IMGPROC_CONV1_OUT_SIZE]
  )
  {
    dout_type s= 0;
    for(int row=0;row<IMGPROC_IMAGE_IN_H;row++)
    {
      for(int col=0; col<IMGPROC_IMAGE_IN_W;col++)
      {
        for (int outChannel=0;outChannel<IMGPROC_CONV1_OUT_C;outChannel++)
        {
          s=0;
          for (int kerH=-IMGPROC_KERNEL1_H/2; kerH< IMGPROC_KERNEL1_H/2;kerH++)
          {
            for (int kerW=-IMGPROC_KERNEL1_W/2; kerW< IMGPROC_KERNEL1_W/2;kerW++)
            {
              for(int inChannel=0;inChannel<IMGPROC_IMAGE_IN_C;inChannel++)
              {
                if(row+kerH>=0 && row+kerH<IMGPROC_IMAGE_IN_H && col+kerW>=0 && col+kerW<IMGPROC_IMAGE_IN_W){
                  s=s+datain[IMGPROC_IMAGE_IN_H*(row+kerH)+IMGPROC_IMAGE_IN_W*(col+kerW)+inChannel]*weights[IMGPROC_KERNEL1_H*kerH+IMGPROC_KERNEL1_W*kerW+IMGPROC_IMAGE_IN_C*inChannel+outChannel];
                }
              }
            }
          }
          s=s+biases[outChannel];
          if(s<0)  s=0;
          dataout[IMGPROC_IMAGE_IN_H*row+IMGPROC_IMAGE_IN_W*col+outChannel]=s;
        }
      }
    }
  }
