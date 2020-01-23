#ifndef __PICTURES_H__
#define __PICTURES_H__
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include "types.h"

char loadPictureRAW(CNN_DATA_TYPE* image,std::string fileName,int shift);
int loadFilePGM(CNN_DATA_TYPE* image);
int savePicture(std::string fileName,CNN_DATA_TYPE* image,int);
void printMatrix(CNN_DATA_TYPE* image);
void printResults(CNN_DATA_TYPE* resultsArray);
#endif
