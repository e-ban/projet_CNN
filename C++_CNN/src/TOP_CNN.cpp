#include "CNN.h"
#include "types.h"
#include "parameters.h"
#include "convolutionReLU.h"
#include "normalize.h"
#include "loadPicture.h"

#pragma hls_design top

void CNN()
{
  static din_type input[IMGPROC_IMAGE_IN_SIZE];
  static dout_type output[IMGPROC_CONV1_OUT_SIZE];
  loadFilePGM(input);//load picture's data from pgm file
  normalize(input,output);
  savePicture("norm.pgm",output,0);
  convolutionReLU1(input,conv1_weights,conv1_biases,output); //execute convolution 1 and store result in output
  savePicture("conv1.pgm",output,1);
}
