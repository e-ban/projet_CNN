#ifndef __PICTURES_H__
#define __PICTURES_H__

#include "types.h"


int loadFilePGM(CNN_DATA_TYPE image[CNN_IMAGE_IN_SIZE]);
int savePicture(std::string fileName,CNN_DATA_TYPE image[CNN_IMAGE_IN_SIZE],int);
void printMatrix(CNN_DATA_TYPE image[CNN_IMAGE_IN_SIZE]);

#endif
