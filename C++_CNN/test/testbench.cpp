#include "CNN.h"
#include "loadPicture.h"

int main()
{
  CNN_DATA_TYPE image[CNN_IMAGE_IN_SIZE];
  CNN_DATA_TYPE mem1[CNN_CONV1_OUT_SIZE];
  CNN_DATA_TYPE mem2[CNN_CONV1_OUT_SIZE];
  //loadFilePGM(image);
  int success=0;
  char* labelsTab[10]={
    "airplane",
    "automobile",
    "bird",
    "cat",
    "deer",
    "dog",
    "frog",
    "horse",
    "ship",
    "truck"};
  for (int i=0; i<1;i++)
  {
    char label=loadPictureRAW(image,"data_batch_1.bin",i);
    savePicture("image.pgm",image,0);
    printMatrix(image);
    char resultLabel=0;
    CNN(image,mem1,mem2);
    printResults(mem2);
    CNN_DATA_TYPE max=0;
    for (int j=0;j<10;j++)
    {
      if (mem2[j]>max)
      {
        max=mem2[j];
        resultLabel = j;
      }
    }
    if(label==resultLabel) success++;
    printf("Image %d [%s] : result : %s | success Rate=%d\n",i,labelsTab[label],labelsTab[resultLabel],success/(i+1));
  }

}
