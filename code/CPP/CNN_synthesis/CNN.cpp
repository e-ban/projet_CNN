#include "CNN.h"

#include "image.h"
#pragma hls_design top



void ImgProcTest(CNN_IMAGE_TYPE* img_in,CNN_IMAGE_TYPE* img_out)
{

  CNN_DATA_TYPE mem1[CNN_CONV1_OUT_SIZE];
  CNN_DATA_TYPE mem2[CNN_CONV1_OUT_SIZE];
  img_out[0]=img_in[0];

  convolutionReLU(imageIN,mem2,conv1_weights,conv1_biases,1);

  maxpool(mem2,mem1,1);

  convolutionReLU(mem1,mem2,conv2_weights,conv2_biases,2);

  maxpool(mem2,mem1,2);

  convolutionReLU(mem1,mem2,conv3_weights,conv3_biases,3);

  maxpool(mem2,mem1,3);

  perceptron(mem1,mem2,local3_weights,local3_biases);

  char label=0;
  CNN_DATA_TYPE max=-510;
  for (int j=0;j<10;j++)
  {
    if (mem2[j]>max)
    {
      max=mem2[j];
      label = j;
    }
  }

  resultlabel=label;
  display(label,imageIN,img_out);
}
