#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include "loadPicture.h"


int loadFilePGM(din_type image[IMGPROC_IMAGE_IN_SIZE])
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
    image[i]= din_type(temp);
    i++;
  }
  f.close();
  return 0;
}

int savePicture(std::string fileName,din_type image[IMGPROC_IMAGE_IN_SIZE])
{
  std::ofstream f(fileName);
  f<<"P3"<<std::endl;
  f<<"24 24"<<std::endl;
  f<<"255"<<std::endl;
  for (int i=0;i<IMGPROC_IMAGE_IN_SIZE;i++){
    f << image[i] << " ";
    if ((i+1)%(24*3)==0) f<<std::endl;
  }
  f.close();
  return 0;
}

void printMatrix(din_type image[IMGPROC_IMAGE_IN_SIZE])
{
  for(int i=0; i<IMGPROC_IMAGE_IN_SIZE; i++)
  {
    if(i%(24)==0) std::cout<<std::endl;
    std::cout << image[i] << " ";
  }
}

/*int main()
{
  din_type input[24*24*3];
//  din_type output[24*24*3];
  loadFilePGM(input);
  printMatrix(input);
  savePicture("save.ppm",input);
}
*/
