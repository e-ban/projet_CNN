#include "CNN.h"
#include "loadPicture.h"

#pragma hls_design top

void CNN(CNN_DATA_TYPE* imageIN,CNN_DATA_TYPE* mem1,CNN_DATA_TYPE* mem2)
{
  normalize(imageIN,mem1);

  convolutionReLU(mem1,mem2,conv1_weights,conv1_biases,1);

  maxpool(mem2,mem1,1);

  convolutionReLU(mem1,mem2,conv2_weights,conv2_biases,2);

  maxpool(mem2,mem1,2);

 convolutionReLU(mem1,mem2,conv3_weights,conv3_biases,3);

  maxpool(mem2,mem1,3);

  perceptron(mem1,mem2,local3_weights,local3_biases);

}
