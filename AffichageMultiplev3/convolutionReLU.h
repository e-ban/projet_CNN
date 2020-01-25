#ifndef __CONVOLRELU_H__
#define __CONVOLRELU_H__

#include "types.h"

void convolutionReLU(  CNN_DATA_OUT_TYPE datain[CNN_IMAGE_IN_SIZE], CNN_DATA_TYPE dataout[CNN_CONV1_OUT_SIZE], CNN_COEFF_TYPE weights[CNN_KERNEL1_SIZE],  CNN_COEFF_TYPE biases[CNN_CONV1_IN_C],  int sel );

#endif
