/**
* @file ioImage.cpp
* @author Iban Guinebert & Antoine Maillefert
* @brief Contains routines to read and writes images during the CNN process
**/
#include "ioImage.h"
#include <iostream>
#include <fstream>
#include <sstream>
/**
* @param fileName name of the file to be written
* @param image pointer to the array to print out
* @param type Type of the image array
*             =>'d' for an array of CNN_DATA_TYPE as input
*             =>'i' for an array of CNN_IMAGE_TYPE as input
* @param height height of input
* @param width width of input
* @param canal_size number of total canals of input
* @param format PGM format "P3" or "P2"
* @param canal select Canal to be printed in case format is "P2"
* @brief Print the input image as a pgm file in grayscale or RGB
**/
void saveOutput(std::string filename,void* image,char type,int height,int width,int canal_size,std::string format,int canal)
{
  std::ofstream f(filename+".pgm");
  int iter=1;
  if(format=="P2") iter=canal_size;
  f<<format<<std::endl;
  f<<width<<" "<<height<<std::endl;
  f<<"255"<<std::endl;
    for (int i=canal;i<height*width*canal_size;i+=iter){
      switch(type)
      {
        case 'd': f << (CNN_IMAGE_TYPE)((CNN_DATA_TYPE*)image)[i] << " ";
        break;
        case 'i': f << ((CNN_IMAGE_TYPE*)image)[i] << " ";
        break;
        case 'f': f << ((CNN_DATA_TYPE*)image)[i] << " ";
        default:
        break;
      }
      if (i!=canal && (i)%(width*canal_size)==canal) f<<std::endl;
    }
  f<< std::endl;
  f.close();
}
/**
* @param fileName name of the file to be written
* @param image pointer to the array to print out
* @param type Type of the image array
*             =>'d' for an array of CNN_DATA_TYPE as input
*             =>'i' for an array of CNN_IMAGE_TYPE as input
* @param height height of input
* @param width width of input
* @param canal_size number of total canals of input
* @brief Print each canal of input into a pgm file in grayscale
**/
void saveMultiOutput(std::string filename,void* image,char type,int height,int width,int canal_size)
{
  for(int c=0;c<canal_size;c++)
  {
    saveOutput(filename+"_"+std::to_string(c),image,type,height,width,canal_size,"P2",c);
  }
}

void testPGM()
{
  std::ofstream f("output/test.pgm");
  f<<"P2"<<std::endl;
  f<<"320 240"<<std::endl;
  f<<"255"<<std::endl;
    for (int i=0;i<240;i++){
      for(int j=0;j<320;j++){
        if(i%4==0) f<<255<<" ";
        else f<<0<<" ";
      }
      f<<std::endl;
    }
  f<< std::endl;
  f.close();
}

/**
* @param image pointer to the array to print out
* @param type Type of the image array
*             =>'d' for an array of CNN_DATA_TYPE as input
*             =>'i' for an array of CNN_IMAGE_TYPE as input
* @param height height of input
* @param width width of input
* @param canal number of total canals of input
* @brief Print picture matrix in standard output
**/
void printMatrix(void* image,char type,int height,int width,int canal)
{
  for(int i=0; i<height*width*canal; i++)
  {
    if(i%(width*canal)==0) std::cout<<std::endl;
    switch(type)
    {
      case 'd': std::cout << ((CNN_DATA_TYPE*)image)[i] << " ";
      break;
      case 'i': std::cout << ((CNN_IMAGE_TYPE*)image)[i] << " ";
      break:
      default:
      break;
    }
  }
}

/**
* @param image pointer to the array to write in
* @param fileName name of the binary file to read
* @param shift Indicate the index of the picture to be read in binary file
* @brief Load picture from a binary file into 1D array of CNN_IMAGE_TYPE
**/
char loadPictureRAW(CNN_IMAGE_TYPE* image,std::string fileName,int shift)
{
  std::ifstream f(fileName,std::ios::in | std::ios::binary);
  if(!f.is_open()) {
    std::cout << "Cannot open file" << std::endl;
    return -1;
  }
  char* redblock = new char[1024];
  char* greenblock = new char[1024];
  char* blueblock = new char[1024];
  f.seekg(shift*3073);
  char* label=new char[1];
  f.read(label,1);
  f.read(redblock,1024);
  f.read(greenblock,1024);
  f.read(blueblock,1024);
  f.close();
  for (int i; i<1024;i++)
  {
    image[3*i] = CNN_IMAGE_TYPE((unsigned char)redblock[i]);
    image[3*i+1] = CNN_IMAGE_TYPE((unsigned char)greenblock[i]);
    image[3*i+2] = CNN_IMAGE_TYPE((unsigned char)blueblock[i]);
  }
  return *label;
}
