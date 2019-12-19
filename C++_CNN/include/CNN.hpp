#include <iostream>
#include "imgproc_vfix_config.h"


#include "ac_fixed.h"
#include "ac_channel.h"

typedef ac_fixed<IMGPROC_IMAGE_IN_P> din_type;
typedef ac_fixed<IMGPROC_IMAGE_OUT_P> dout_type;


void convolution(  din_type datain[IMGPROC_IMAGE_IN_SIZE],
  c_type weights[IMGPROC_KERNEL_SIZE],
  c_type biases[IMGPROC_IMAGE_OUT_SIZE_2],
  dout_type dataout[IMGPROC_IMAGE_OUT_SIZE]);
