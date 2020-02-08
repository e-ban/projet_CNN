#include "imgproc_vfix_config.h"
#include "types.h"
#include "parameters.h"


#pragma hls_design top


void convolutionReLU1(
  din_type img_in[CAM_IMG_SIZE],
  dout_type img_out[CAM_IMG_SIZE]
  )
  {
    dout_type s= 0;
    for(int row=0;row<CAM_IMG_SIZE_1;row++)
    {
      for(int col=0; col<CAM_IMG_SIZE_0;col++)
      {
        for (int outChannel=0;outChannel<1;outChannel++)
        {
          s=0;
          for (int kerH=-IMGPROC_KERNEL1_H/2; kerH<=IMGPROC_KERNEL1_H/2;kerH++)
          {
            for (int kerW=-IMGPROC_KERNEL1_W/2; kerW<=IMGPROC_KERNEL1_W/2;kerW++)
            {
              std::cout << row << " & " << kerH << std::endl;
              std::cout << col << " & " << kerW << "\n" << std::endl;
              for(int inChannel=0;inChannel<1;inChannel++)
              {
                if(row+kerH>=0 && row+kerH<CAM_IMG_SIZE_1 && col+kerW>=0 && col+kerW<CAM_IMG_SIZE_0){
                  s=s+img_in[CAM_IMG_SIZE_1 *(row+kerH)+CAM_IMG_SIZE_0*(col+kerW)+inChannel]*conv1_weights[IMGPROC_KERNEL1_H*kerH+IMGPROC_KERNEL1_W*kerW+IMGPROC_IMAGE_IN_C*inChannel+outChannel];
                }
              }
            }
          }
          s=s+conv1_biases[outChannel];
          if(s<0)  s=0;
          img_out[CAM_IMG_SIZE_1*row+CAM_IMG_SIZE_0*col+outChannel]=s;
        }
      }
    }
  }
