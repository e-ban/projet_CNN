#ifndef __CNN_H__
#define __CNN_H__
#include "types.h"
#include "parameters.h"
#include "convolutionReLU.h"
#include "normalize.h"
#include "maxpool.h"
#include "perceptron.h"
#include "display.h"

void CNN(CNN_IMAGE_TYPE* imageIN,CNN_DATA_TYPE* mem1,CNN_DATA_TYPE* mem2,CNN_IMAGE_TYPE* imageOUT);

#endif
