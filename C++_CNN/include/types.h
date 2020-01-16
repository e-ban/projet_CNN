#ifndef __TYPES_H__
#define __TYPES_H__

#include "imgproc_vfix_config.h"


#include "ac_fixed.h"
#include "ac_channel.h"

typedef ac_fixed<IMGPROC_IMAGE_IN_P> din_type;
typedef ac_fixed<IMGPROC_CONV1_OUT_P> dout_type;
typedef ac_fixed<IMGPROC_KERNEL1_P> c_type;

#endif
