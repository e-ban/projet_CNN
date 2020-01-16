#include "types.h"
#include "maxpool.h"

void maxpool1(
  dout_type datain[IMGPROC_CONV1_OUT_SIZE];
  dout_type2 dataout[IMGPROC_CONV2_IN_SIZE];
  ){
    dout_type2 maxi=0;
    for (int x=0; x<IMGPROC_CONV1_OUT_H; IMGPROC_MAXP_STRIDE){
      for (int y=0; y<IMGPROC_CONV1_OUT_W; IMGPROC_MAXP_STRIDE){
        for (int c=0, c<IMGPROC_CONV1_OUT_C; c++){
          maxi=0;
          for (int poolH=0; poolH<IMGPROC_MAXP_SIZE; poolH++){
            for (int poolW=0; poolW<IMGPROC_MAXP_SIZE; poolW++){
              if (((x+poolH)<IMGPROC_CONV1_OUT_H) && ((y+poolW)<IMGPROC_CONV1_OUT_W)){
                if (datain[IMGPROC_CONV1_OUT_H*(x+poolH)+IMGPROC_CONV1_OUT_W*(y+poolW)+IMGPROC_CONV1_OUT_C*c] > maxi){
                  maxi = datain[IMGPROC_CONV1_OUT_H*(x+poolH)+IMGPROC_CONV1_OUT_W*(y+poolW)+IMGPROC_CONV1_OUT_C*c];
                }
                else { //zero padding
                  if (maxi<0){
                    maxi=0;
                  }
                }
              }
            }
          }
          dataout[((IMGPROC_CONV2_IN_H*x)/IMCPROC_MAXP_STRIDE) + ((IMGPROC_CONV2_IN_W*y)/IMCPROC_MAXP_STRIDE)+IMGPROC_CONV2_IN_C]=maxi;
        }
      }
    }
  }


