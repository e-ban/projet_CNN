#ifndef __CNN_H__
#define __CNN_H__
#include "types.h"
#include "parameters.h"
#include "convolutionReLU.h"
#include "display.h"
#include "centeredCrop.h"
#include "order.h"

void ImgProcTest(CNN_DATA_OUT_TYPE img_in[CNN_IMAGE_IN_SIZE],CNN_DATA_OUT_TYPE img_out[CNN_IMAGE_IN_SIZE],CNN_DATA_TYPE mem2[CNN_CONV1_OUT_SIZE],
  CNN_DATA_TYPE crop[CNN_IMAGE_IN_SIZE]);
#endif
