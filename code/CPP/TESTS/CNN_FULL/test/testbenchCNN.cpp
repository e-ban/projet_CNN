/**
* @file testbench.cpp
* @author Iban Guinebert & Antoine Maillefert
* @brief Testbench of CNN_FULL
**/
#include "CNN.h"
#include "ioImage.h"
#include "normalize.h"
#include <string>
#include <iostream>
#include "image.h"


using namespace std;

int main()
{
  //Start of test
  cout << "Start CNN" << endl;
  CNN_IMAGE_TYPE* img_in = (CNN_IMAGE_TYPE*)calloc(CNN_VGA_SIZE,sizeof(*img_in));
  CNN_IMAGE_TYPE* img_out = (CNN_IMAGE_TYPE*)calloc(CNN_VGA_SIZE,sizeof(*img_out));
  ImgProcTest(img_in,img_out);
  saveOutput("output/output",(void*)img_out,'i',CNN_VGA_H,CNN_VGA_W,CNN_VGA_C,"P2",0);
  free(img_out);
  free(img_in);

}
