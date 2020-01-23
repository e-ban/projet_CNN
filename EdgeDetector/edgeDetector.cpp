#include "edgeDetector.h"
#include "ac_math.h"

#pragma hls_design top

void ImgProcTest(CNN_DATA_OUT_TYPE img_in[CNN_IMAGE_IN_SIZE],CNN_DATA_OUT_TYPE img_out[CNN_IMAGE_IN_SIZE])
{
  int length_out = CNN_CONV1_OUT_SIZE;

  CNN_DATA_TYPE mem1[CNN_CONV1_OUT_SIZE];
  CNN_DATA_TYPE mem2[CNN_CONV1_OUT_SIZE];
  CNN_DATA_TYPE memS[CNN_CONV1_OUT_SIZE];

  convolutionReLU(img_in,mem1,kernel1);
  convolutionReLU(img_in,mem2,kernel2);

  for(int l=0;l<length_out;l++){
    memS[l]=ac_math::ac_sqrt(mem1[l]*mem1[l]+mem2[l]*mem2[l],mem1[l]*mem1[l]+mem2[l]*mem2[l]);
    }
    
  display(memS,img_out);
}
