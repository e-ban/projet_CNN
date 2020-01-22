#ifndef __CNN_H__
#define __CNN_H__
#include "types.h"
#include "parameters.h"
#include "convolutionReLU.h"
#include "normalize.h"
#include "maxpool.h"
#include "perceptron.h"

void CNN(CNN_DATA_TYPE imageIN[],CNN_DATA_TYPE mem1[],CNN_DATA_TYPE mem2[]);
#endif
