#include "types.h"


void convolutionReLU(  din_type datain[IMGPROC_IMAGE_IN_SIZE],
  c_type weights[IMGPROC_KERNEL_SIZE],
  c_type biases[IMGPROC_IMAGE_OUT_C],
  dout_type dataout[IMGPROC_IMAGE_OUT_SIZE]);
