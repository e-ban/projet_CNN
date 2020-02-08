#ifndef __CNN_H__
#define __CNN_H__
#include "types.h"
#include "parameters.h"
#include "convolutionReLU.h"
#include "normalize.h"
#include "maxpool.h"
#include "perceptron.h"
#include "display.h"
#include "loadPicture.h"
#include "imageNorm.h"
extern bool verbosity;
void CNN(CNN_IMAGE_TYPE* img_in,CNN_IMAGE_TYPE* img_out);

#endif
