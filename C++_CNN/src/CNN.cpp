#include "CNN.h"


#pragma hls_design top
void printMatrix(CNN_DATA_TYPE mem,int height,int width,int canal1, int canal2)
{
  printf("\n[ ");
  for (int i=0;i<height;i++)
  {
    printf("[ ");
    for (int j=0 ; j< width;j++)
    {
      printf("%lf, ",mem[i*width*canal1*canal2+j*canal1*canal2]);
    }
    printf(" ]\n");
  }
}

void CNN(CNN_DATA_TYPE imageIN[],CNN_DATA_TYPE mem1[],CNN_DATA_TYPE mem2[])
{
  printMatrix(imageIN,CNN_IMAGE_IN_H,CNN_IMAGE_IN_W,1,1);
  normalize(imageIN,mem1);
  convolutionReLU(mem1,mem2,conv1_weights,conv1_biases,1);

  maxpool(mem2,mem1,1);

  convolutionReLU(mem1,mem2,conv2_weights,conv2_biases,2);

  maxpool(mem2,mem1,2);

 convolutionReLU(mem1,mem2,conv3_weights,conv3_biases,3);

  maxpool(mem2,mem1,3);

  perceptron(mem1,mem2,local3_weights,local3_biases);

}
