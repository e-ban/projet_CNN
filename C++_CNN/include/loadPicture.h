#ifndef __PICTURES_H__
#define __PICTURES_H__

#include "types.h"


int loadFilePGM(din_type image[IMGPROC_IMAGE_IN_SIZE]);
int savePicture(std::string fileName,din_type image[IMGPROC_IMAGE_IN_SIZE],int);
void printMatrix(din_type image[IMGPROC_IMAGE_IN_SIZE]);

#endif
