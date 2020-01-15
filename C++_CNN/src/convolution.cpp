#include "types.h"
#include "convolutionReLU.h"


#pragma hls_design top

void convolutionReLU(
  din_type datain[IMGPROC_IMAGE_IN_SIZE],
  c_type weights[IMGPROC_KERNEL_SIZE],
  c_type biases[IMGPROC_IMAGE_OUT_C],
  dout_type dataout[IMGPROC_IMAGE_OUT_SIZE])
  {
    dout_type s= 0;
    for(int row=0;row<IMGPROC_IMAGE_IN_H;row++)
    {
      for(int col=0; col<IMGPROC_IMAGE_IN_W;col++)
      {
        for (int outChannel=0;outChannel<IMGPROC_IMAGE_OUT_C;outChannel++)
        {
          s=0;
          for (int kerH=0; kerH< IMGPROC_KERNEL_H;kerH++)
          {
            for (int kerW=0; kerW< IMGPROC_KERNEL_W;kerW++)
            {
              for(int inChannel=0;inChannel<IMGPROC_IMAGE_IN_C;inChannel++)
              {
                s=s+datain[IMGPROC_IMAGE_IN_H*(row+kerH)+IMGPROC_IMAGE_IN_W*(col+kerW)+inChannel]*weights[IMGPROC_KERNEL_H*kerH+IMGPROC_KERNEL_W*kerW+IMGPROC_IMAGE_IN_C*inChannel+outChannel];
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
