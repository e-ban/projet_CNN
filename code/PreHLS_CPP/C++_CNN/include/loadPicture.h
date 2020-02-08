#ifndef __PICTURES_H__
#define __PICTURES_H__

#include "types.h"

char loadPictureRAW(CNN_IMAGE_TYPE* image,std::string fileName,int shift);
int loadFilePGM(CNN_DATA_TYPE* image);
int savePicture(std::string fileName,CNN_IMAGE_TYPE* image,int);
void saveOutput(std::string fileName,CNN_IMAGE_TYPE* image);
void printMatrix(CNN_DATA_TYPE* image);
void saveDATA(std::string fileName,CNN_DATA_TYPE* image);
int savePictureRed(std::string fileName,CNN_IMAGE_TYPE* image,int);
void printMatrixRed(CNN_DATA_TYPE* image);
void printResults(CNN_DATA_TYPE* resultsArray);
#endif
