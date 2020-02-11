#include "edgeDetector.h"

#pragma hls_design top

void ImgProcTest(CNN_DATA_OUT_TYPE img_in[CNN_IMAGE_IN_SIZE],CNN_DATA_OUT_TYPE img_out[CNN_IMAGE_IN_SIZE])
{
  convolutionReLU(img_in,img_out,kernel1);
}
