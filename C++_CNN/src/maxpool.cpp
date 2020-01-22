#include "types.h"
#include "maxpool.h"

void maxpool(  CNN_DATA_TYPE datain[],  CNN_DATA_TYPE dataout[],int sel  ){
  int height_in,width_in,canal_in, width_out, canal_out;
  if(sel==1){
    height_in = CNN_CONV1_OUT_H;
    width_in = CNN_CONV1_OUT_W;
    canal_in = CNN_CONV1_OUT_C;
  //  height_out = CNN_CONV2_IN_H;
    width_out = CNN_CONV2_IN_W;
    canal_out = CNN_CONV2_IN_C;
  }
  else if(sel==2){
    height_in = CNN_CONV2_OUT_H;
    width_in = CNN_CONV2_OUT_W;
    canal_in = CNN_CONV2_OUT_C;
  //  height_out = CNN_CONV3_IN_H;
    width_out = CNN_CONV3_IN_W;
    canal_out = CNN_CONV3_IN_C;
  }
  else {
    height_in = CNN_CONV3_OUT_H;
    width_in = CNN_CONV3_OUT_W;
    canal_in = CNN_CONV3_OUT_C;
  //  height_out = CNN_PER_IN_H;
    width_out = CNN_PER_IN_W;
    canal_out = CNN_PER_IN_C;
  }
  CNN_DATA_TYPE maxi=0;
    for (int x=0; x<height_in; x+=CNN_MAXP_STRIDE){
      for (int y=0; y<width_in; y+=CNN_MAXP_STRIDE){
        for (int c=0; c<canal_in; c++){
          maxi=0;
          for (int poolH=0; poolH<CNN_MAXP_SIZE; poolH++){
            for (int poolW=0; poolW<CNN_MAXP_SIZE; poolW++){
              if (((x+poolH)<height_in) && ((y+poolW)<width_in)){
                if (datain[canal_in*width_in*(x+poolH)+canal_in*(y+poolW)+c] > maxi){
                  maxi = datain[canal_in*width_in*(x+poolH)+canal_in*(y+poolW)+c];
                }
                else { //zero padding
                  if (maxi<0){
                    maxi=0;
                  }
                }
              }
            }
          }
          dataout[((width_out*canal_out*x)/CNN_MAXP_STRIDE) + ((canal_out*y)/CNN_MAXP_STRIDE)+canal_out]=maxi;
        }
      }
    }
  }
