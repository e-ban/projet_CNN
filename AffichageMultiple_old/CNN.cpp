#include "CNN.h"

#pragma hls_design top

void ImgProcTest(CNN_DATA_OUT_TYPE img_in[CNN_IMAGE_IN_SIZE],CNN_DATA_OUT_TYPE img_out[CNN_IMAGE_IN_SIZE])
{
  CNN_DATA_TYPE mem2[CNN_CONV1_OUT_SIZE];
  convolutionReLU(img_in,mem2,conv1_weights,conv1_biases,1);

  CNN_DATA_TYPE crop[CNN_IMAGE_IN_SIZE];
  centered_crop(mem2,crop);
  
  CNN_DATA_TYPE last[CNN_IMAGE_IN_SIZE];
  order(crop,last);
  
  display(last,img_out);}

