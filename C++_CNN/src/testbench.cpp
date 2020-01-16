#include "convolutionReLU.h"
#include "types.h"
#include "loadPicture.h"
#include "parameters.h"

int main()
{

  static din_type input[IMGPROC_IMAGE_IN_SIZE];
  static dout_type output[IMGPROC_CONV1_OUT_SIZE];
  loadFilePGM(input);
  std::cout << "Image loaded"<<std::endl;
  convolutionReLU1(input,conv1_weights,conv1_biases,output);
  std::cout << "Convolution executed"<<std::endl;
  savePicture("save.ppm",output);
}
