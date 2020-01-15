#include "types.h"


void convolutionRELU(  din_type datain[IMGPROC_IMAGE_IN_SIZE],
  c_type weights[IMGPROC_KERNEL_SIZE],
  c_type biases[IMGPROC_IMAGE_OUT_SIZE_2],
  dout_type dataout[IMGPROC_IMAGE_OUT_SIZE]);
