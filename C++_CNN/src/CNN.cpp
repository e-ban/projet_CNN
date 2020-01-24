#include "CNN.h"


#pragma hls_design top

void CNN(CNN_IMAGE_TYPE imageIN[CNN_IMAGE_IN_SIZE],CNN_DATA_TYPE mem1[CNN_CONV1_IN_SIZE],CNN_DATA_TYPE mem2[CNN_CONV1_IN_SIZE],CNN_IMAGE_TYPE imageOUT[CNN_VGA_SIZE])
{
//  normalize(imageIN,mem1);

  convolutionReLU(mem1,mem2,conv1_weights,conv1_biases,1);

  maxpool(mem2,mem1,1);

  convolutionReLU(mem1,mem2,conv2_weights,conv2_biases,2);

  maxpool(mem2,mem1,2);

  convolutionReLU(mem1,mem2,conv3_weights,conv3_biases,3);

  maxpool(mem2,mem1,3);

  perceptron(mem1,mem2,local3_weights,local3_biases);

  char label;
  CNN_DATA_TYPE max=0;
  for (int j=0;j<10;j++)
  {
    if (mem2[j]>max)
    {
      max=mem2[j];
      label = j;
    }
  }
  display(label,imageIN,imageOUT);
}
