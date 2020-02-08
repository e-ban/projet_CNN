#include "CNN.h"

#pragma hls_design top

void CNN(CNN_DATA_OUT_TYPE imageIN[CNN_IMAGE_IN_SIZE],CNN_DATA_OUT_TYPE imageOUT[CNN_IMAGE_IN_SIZE])
{
  CNN_DATA_TYPE mem2[CNN_CONV1_OUT_SIZE];
  convolutionReLU(imageIN,mem2,conv1_weights,conv1_biases,1);
  display(mem2,imageOUT);}

