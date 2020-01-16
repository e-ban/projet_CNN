#include "CNN.h"
#include "types.h"
#include "parameters.h"
#include "convolutionReLU.h"
#include "normalize.h"
#include "loadPicture.h"
#include "maxpool.h"
#pragma hls_design top

void CNN()
{
  static din_type image[IMGPROC_IMAGE_IN_SIZE];
  static din_type normOut[IMGPROC_IMAGE_IN_SIZE];
  static dout_type conv1Out[IMGPROC_CONV1_OUT_SIZE];
  static dout_type maxpoolOut[IMGPROC_CONV1_OUT_SIZE];

  loadFilePGM(image);//load picture's data from pgm file
  normalize(image,normOut);
  savePicture("norm.pgm",normOut,0);
  convolutionReLU1(normOut,conv1_weights,conv1_biases,conv1Out); //execute convolution 1 and store result in output
  maxpool1(conv1Out,maxpoolOut);
  savePicture("output.pgm",maxpoolOut,0);
}
