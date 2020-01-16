#ifndef __CONVOLRELU_H__
#define __CONVOLRELU_H__

#include "types.h"


void convolutionReLU1(
  din_type datain[IMGPROC_IMAGE_IN_SIZE],
  c_type weights[IMGPROC_KERNEL1_SIZE],
  c_type biases[IMGPROC_CONV1_OUT_C],
  dout_type dataout[IMGPROC_CONV1_OUT_SIZE]
);

#endif
