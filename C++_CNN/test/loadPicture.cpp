#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include "loadPicture.h"


int loadFilePGM(CNN_DATA_TYPE image[CNN_IMAGE_IN_SIZE])
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
    image[i]= CNN_DATA_TYPE(temp);
    i++;
  }
  f.close();
  return 0;
}

int savePicture(std::string fileName,CNN_DATA_TYPE image[CNN_IMAGE_IN_SIZE],int sel)
{
  if(sel==0){
  std::ofstream f(fileName);
  f<<"P3"<<std::endl;
  f<<"24 24"<<std::endl;
  f<<"255"<<std::endl;
    for (int i=0;i<CNN_IMAGE_IN_SIZE;i++){
      f << image[i].to_int()<< " ";
      if ((i+1)%(24*3)==0) f<<std::endl;
    }
  f.close();
  }
  else {
    for (int c=0;c<CNN_CONV1_OUT_C;c++)
    {
      std::ofstream f((std::to_string(c))+(fileName));
      f<<"P2"<<std::endl;
      f<<"24 24"<<std::endl;
      f<<"255"<<std::endl;
      for (int i=0;i<CNN_CONV1_IN_H;i++)
      {
        for (int j=0;j<CNN_CONV1_IN_W;j++)
        {
          f << image[i*CNN_CONV1_IN_H+j*CNN_CONV1_IN_W+c].to_int()<< " ";
        }
        f<<std::endl;
      }
      f.close();
    }

  }

  return 0;
}

void printMatrix(CNN_DATA_TYPE image[CNN_IMAGE_IN_SIZE])
{
  for(int i=0; i<CNN_IMAGE_IN_SIZE; i++)
  {
    if(i%(24)==0) std::cout<<std::endl;
    std::cout << image[i] << " ";
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
