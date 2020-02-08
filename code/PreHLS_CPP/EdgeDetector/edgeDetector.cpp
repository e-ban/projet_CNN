#include "edgeDetector.h"

#pragma hls_design top

void ImgProcTest(CNN_DATA_OUT_TYPE img_in[CNN_IMAGE_IN_SIZE],CNN_DATA_OUT_TYPE img_out[CNN_IMAGE_IN_SIZE])
{
  int length_out = CNN_CONV1_OUT_SIZE;

  CNN_DATA_TYPE mem1[CNN_CONV1_OUT_SIZE];
  CNN_DATA_TYPE mem2[CNN_CONV1_OUT_SIZE];
  CNN_DATA_TYPE memS[CNN_CONV1_OUT_SIZE];
  CNN_NORM_TYPE Result;

  convolutionReLU(img_in,mem1,kernel1);
  convolutionReLU(img_in,mem2,kernel2);

  for(int l=0;l<length_out;l++){
    CNN_NORM_TYPE mem12 = mem1[l]*mem1[l];
    CNN_NORM_TYPE mem22 = mem2[l]*mem2[l];
    ac_math::ac_sqrt(mem12+mem22,Result);
    memS[l]=Result;
    }
    
  display(memS,img_out);
}
