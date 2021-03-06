#include "loadPicture.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
int loadFilePGM(CNN_IMAGE_TYPE* image)
{
  std::string taille;
  std::string format;
  std::string stemp;

  int max;
  int temp;
  int tx=0;
  int ty=0;

  std::ifstream f("input.ppm");
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
  while (i<tx*ty*3)
  {
    f >> temp;
    std::cout << temp;
    image[i]= CNN_IMAGE_TYPE(temp);
    i++;
  }
  f.close();
  return 0;
}

int savePicture(std::string fileName,CNN_IMAGE_TYPE* image,int sel)
{
  if(sel==0){
  std::ofstream f(fileName+".pgm");
  f<<"P3"<<std::endl;
  f<<"32 32"<<std::endl;
  f<<"255"<<std::endl;
    for (int i=0;i<CNN_IMAGE_FULL_SIZE;i++){
      f << image[i].to_int()<< " ";
      if ((i+1)%(32*3)==0) f<<std::endl;
    }
  f.close();
  }
  else {
    for (int c=0;c<CNN_CONV1_OUT_C;c++)
    {
      std::ofstream f(fileName+std::to_string(c)+".pgm");
      f<<"P2"<<std::endl;
      f<<"24 24"<<std::endl;
      f<<"255"<<std::endl;
      for (int i=0;i<CNN_CONV1_OUT_H;i++)
      {
        for (int j=0;j<CNN_CONV1_OUT_W;j++)
        {
          f << image[i*CNN_CONV1_OUT_W*CNN_CONV1_OUT_C+j*CNN_CONV1_OUT_C+c].to_int()<< " ";
        }
        f<<std::endl;
      }
      f.close();
    }

  }

  return 0;
}
int savePictureRed(std::string fileName,CNN_IMAGE_TYPE* image,int sel)
{
  if(sel==0){
  std::ofstream f(fileName+".pgm");
  f<<"P3"<<std::endl;
  f<<"24 24"<<std::endl;
  f<<"255"<<std::endl;
    for (int i=0;i<CNN_IMAGE_IN_SIZE;i++){
      f << image[i].to_int()<< " ";
      if ((i+1)%(24*3)==0) f<<std::endl;
    }
  f.close();
  }
  else if(sel==1){
    for (int c=0;c<CNN_CONV1_OUT_C;c++)
    {
      std::ofstream f(fileName+std::to_string(c)+".pgm");
      f<<"P2"<<std::endl;
      f<<"24 24"<<std::endl;
      f<<"255"<<std::endl;
      for (int i=0;i<CNN_CONV1_OUT_H;i++)
      {
        for (int j=0;j<CNN_CONV1_OUT_W;j++)
        {
          f << image[i*CNN_CONV1_OUT_W*CNN_CONV1_OUT_C+j*CNN_CONV1_OUT_C+c].to_int()<< " ";
        }
        f<<"\n";
      }
      f.close();
    }
  }
    else if(sel==2){
      for (int c=0;c<CNN_CONV2_IN_C;c++)
      {
        std::ofstream f(fileName+std::to_string(c)+".pgm");
        f<<"P2"<<std::endl;
        f<<"12 12"<<std::endl;
        f<<"255"<<std::endl;
        for (int i=0;i<CNN_CONV2_IN_H;i++)
        {
          for (int j=0;j<CNN_CONV2_IN_W;j++)
          {
            f << image[i*CNN_CONV2_IN_W*CNN_CONV2_IN_C+j*CNN_CONV2_IN_C+c].to_int()<< " ";
          }
          f<<"\n";
        }
        f.close();
      }
  }
  else if(sel==4){
    for (int c=0;c<CNN_PER_IN_C;c++)
    {
      std::ofstream f(fileName+std::to_string(c)+".pgm");
      f<<"P2"<<std::endl;
      f<<CNN_PER_IN_W <<" "<< CNN_PER_IN_H <<std::endl;
      f<<"255"<<std::endl;
      for (int i=0;i<CNN_PER_IN_H;i++)
      {
        for (int j=0;j<CNN_PER_IN_W;j++)
        {
          f << image[i*CNN_PER_IN_W*CNN_PER_IN_C+j*CNN_PER_IN_C+c].to_int()<< " ";
        }
        f<<"\n";
      }
      f.close();
    }
}
  return 0;
}
void saveOutput(std::string filename,CNN_IMAGE_TYPE* image)
{
  std::ofstream f(filename+".pgm");
  f<<"P2"<<std::endl;
  f<<"320 240"<<std::endl;
  f<<"255"<<std::endl;
    for (int i=0;i<CNN_VGA_SIZE;i++){
      f << image[i]<< " ";
      if ((i+1)%(320)==0) f<<std::endl;
    }
  f.close();
}
void printMatrix(CNN_DATA_TYPE image[CNN_IMAGE_FULL_SIZE])
{
  for(int i=0; i<CNN_IMAGE_FULL_SIZE; i++)
  {
    if(i%(CNN_IMAGE_FULL_W*CNN_IMAGE_FULL_C)==0) std::cout<<std::endl;
    std::cout << image[i] << " ";
  }
}

void printMatrixRed(CNN_DATA_TYPE image[CNN_IMAGE_IN_SIZE])
{
  for(int i=0; i<CNN_IMAGE_IN_SIZE; i++)
  {
    if(i%(CNN_IMAGE_IN_W*CNN_IMAGE_IN_C)==0) std::cout<<std::endl;
    std::cout << image[i] << " ";
  }
}
void saveDATA(std::string fileName,CNN_DATA_TYPE* image)
{
  std::ofstream f(fileName+".h");
  f << "static image[CNN_IMAGE_IN_SIZE]={ ";
    for (int i=0;i<CNN_IMAGE_IN_SIZE;i++){
      f << image[i];
      if(i!=CNN_IMAGE_IN_SIZE-1) f<<",";
      if ((i+1)%(CNN_IMAGE_IN_C*CNN_IMAGE_IN_W)==0) f<<std::endl;
    }
    f<<"};"<<std::endl;
  f.close();
}
void printResults(CNN_DATA_TYPE* resultsArray)
{
  for (int i=0; i< CNN_OUT;i++)
  {
    std::cout << resultsArray[i] << std::endl;
  }
}
/*int main()
{
  CNN_IMAGEIN_TYPE input[24*24*3];
//  CNN_IMAGEIN_TYPE output[24*24*3];
  loadFilePGM(input);
  printMatrix(input);
  savePicture("save.ppm",input);
}
*/
