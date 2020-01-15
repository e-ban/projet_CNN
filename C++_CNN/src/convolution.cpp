#include "types.h"
#include "convolutionReLU.h"


#pragma hls_design top

void convolutionReLU(
  din_type datain[IMGPROC_IMAGE_IN_SIZE],
  c_type weights[IMGPROC_KERNEL_SIZE],
  c_type biases[IMGPROC_IMAGE_OUT_SIZE_2],
  dout_type dataout[IMGPROC_IMAGE_OUT_SIZE])
  {
    double s= 0;
    for(int row=0;row<IMGPROC_IMAGE_IN_SIZE_0;row++)
    {
      for(int col=0; col<IMGPROC_IMAGE_IN_SIZE_1;col++)
      {
        for (int outChannel=0;outchannel<IMGPROC_IMAGE_OUT_SIZE_2;outchannel++)
        {
          s=0;
          for (int kerH=0; kerH< IMGPROC_KERNEL_SIZE_0;kerH++)
          {
            for (int kerW=0; kerW< IMGPROC_KERNEL_SIZE_1;kerW++)
            {
              for(int inChannel=0;inChannel<IMGPROC_IMAGE_IN_SIZE_2;inChannel++)
              {
                s=s+datain[IMGPROC_IMAGE_IN_SIZE_0*(row+kerH)+IMGPROC_IMAGE_IN_SIZE_1*(col+kerW)+inChannel]*weights[IMGPROC_KERNEL_SIZE_0*kerH+IMGPROC_KERNEL_SIZE_1*kerW+IMGPROC_IMAGE_IN_SIZE_2*inChannel+outChannel];
              }
            }
          }
          s=s+biases[outChannel];
          if(s<0):
            s=0;
          dataout[IMGPROC_IMAGE_IN_SIZE_0*row+IMGPROC_IMAGE_IN_SIZE_1*col+outChannel]=s;
        }
      }
    }
  }

}
