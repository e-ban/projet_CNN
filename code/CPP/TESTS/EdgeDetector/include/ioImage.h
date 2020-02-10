#ifndef __IOIMAGE_H__
#define __IOIMAGE_H__
#include "types.h"
#include <string>
void saveOutput(std::string,void*,char,int,int,int,std::string,int);
void saveMultiOutput(std::string ,void* ,char ,int ,int,int);
void printMatrix(void*,char,int,int,int);
char loadPictureRAW(CNN_DATA_OUT_TYPE* ,std::string ,int );
int loadFilePGM(CNN_DATA_OUT_TYPE* image,std::string fileName);
void testPGM();
#endif
