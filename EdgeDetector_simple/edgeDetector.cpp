#include "edgeDetector.h"

#pragma hls_design top

void ImgProcTest(CNN_DATA_OUT_TYPE img_in[CNN_IMAGE_IN_SIZE],CNN_DATA_OUT_TYPE img_out[CNN_IMAGE_IN_SIZE])
{

  CNN_DATA_TYPE mem1[CNN_CONV1_OUT_SIZE];

  convolutionReLU(img_in,mem1,kernel1);
   
  display(mem1,img_out);
}
