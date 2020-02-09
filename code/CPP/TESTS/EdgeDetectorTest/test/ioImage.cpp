#include "ioImage.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
        case 'd': f << (CNN_DATA_OUT_TYPE)((CNN_DATA_TYPE*)image)[i] << " ";
        break;
        case 'i': f << ((CNN_DATA_OUT_TYPE*)image)[i] << " ";
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


void printMatrix(void* image,char type,int height,int width,int canal)
{
  for(int i=0; i<height*width*canal; i++)
  {
    if(i%(width*canal)==0) std::cout<<std::endl;
    switch(type)
    {
      case 'd': std::cout << ((CNN_DATA_TYPE*)image)[i] << " ";
      break;
      case 'i': std::cout << ((CNN_DATA_OUT_TYPE*)image)[i] << " ";
      break;
      case 'f': std::cout << (((CNN_DATA_TYPE*)image)[i]).to_double() << " ";
      default:
      break;
    }
  }
}
int loadFilePGM(CNN_DATA_OUT_TYPE* image,std::string fileName)
{
  std::string taille;
  std::string format;
  std::string stemp;

  int max;
  int temp;
  int tx=0;
  int ty=0;

  std::ifstream f(fileName);
  std::getline(f,format);
  std::cout << format << std::endl;
  /* Lit la ligne qui contient la taille */
  std::getline(f,taille);
  std::cout << taille << std::endl;
  /* mais passe les commentaires */
  while (taille[0]=='#') std::getline(f,taille);
  // lit la taille dans la chaine
  std::stringstream staille;
  staille << taille;
  std::cout << taille << std::endl;
  staille >> tx >>ty;
  std::cout << tx <<" et "<< ty << std::endl;
  std::getline(f,stemp);
  std::stringstream(stemp) >> max;
  std::cout << max<<std::endl;
  int i =0;
  while (i<tx*ty)
  {
    f >> temp;
    image[i]= CNN_DATA_OUT_TYPE(temp);
    i++;
  }
  f.close();
  return 0;
}


char loadPictureRAW(CNN_DATA_OUT_TYPE* image,std::string fileName,int shift)
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
    image[3*i] = CNN_DATA_OUT_TYPE((unsigned char)redblock[i]);
    image[3*i+1] = CNN_DATA_OUT_TYPE((unsigned char)greenblock[i]);
    image[3*i+2] = CNN_DATA_OUT_TYPE((unsigned char)blueblock[i]);
  }
  return *label;
}
