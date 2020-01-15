#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include "loadPicture.h"


std::array<din_type,24*24*3> loadFilePGM()
{
  std::string taille;
  std::string format;
  std::string temp;
  int max;
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
  std::getline(f,temp);
  std::stringstream(temp) >> max;
  std::cout << max<<std::endl;
  std::array<din_type,24*24*3> image;
  int i =0;
  while (i<tx*ty*3)
  {
    f >> image[i];
    i++;
  }
  f.close();
  return(image);
}


void printMatrix(std::array<din_type,24*24*3> image)
{
  for(int i=0; i<(24)*(24)*3; i++)
  {
    if(i%(24)==0) std::cout<<std::endl;
    std::cout << image[i] << " ";
  }
}
/*
int main()
{
  std::array<int,24*24*3> image = loadFilePGM();
  printMatrix(image);
  return(0);
}
*/
