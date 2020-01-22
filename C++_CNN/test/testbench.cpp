#include "CNN.h"
#include "loadPicture.h"
int main()
{
  CNN_DATA_TYPE image[CNN_IMAGE_IN_SIZE];
  CNN_DATA_TYPE mem1[CNN_CONV1_OUT_SIZE];
  CNN_DATA_TYPE mem2[CNN_CONV1_OUT_SIZE];
  loadFilePGM(image);
  CNN(image,mem1,mem2);
  for (int i =0; i<10; i++)
  {
    printf("%lf",mem2[i]);
    printf("\n");
  }
}
