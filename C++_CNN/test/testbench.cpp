#include "CNN.h"
#include "loadPicture.h"
int main()
{
  CNN_DATA_TYPE image[CNN_IMAGE_IN_SIZE];
  CNN_DATA_TYPE mem1[CNN_CONV1_OUT_SIZE];
  CNN_DATA_TYPE mem2[CNN_CONV1_OUT_SIZE];
  //for (int k=0; k< CNN_IMAGE_IN_SIZE; k++) image[k]=127;
  loadFilePGM(image);
  //printMatrix(image);
  CNN(image,mem1,mem2);
  printf("end\n\n");
  //printMatrix(mem2);
  printResults(mem2);
}
