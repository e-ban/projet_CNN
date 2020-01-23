#ifndef __TYPES_H__
#define __TYPES_H__

#include "macros_CNN.h"


#include "ac_fixed.h"
#include "ac_channel.h"

typedef ac_fixed<CNN_IMAGE_P> CNN_IMAGE_TYPE;
typedef ac_fixed<CNN_UDATA_P> CNN_UDATA_TYPE;
typedef ac_fixed<CNN_DATA_P> CNN_DATA_TYPE;
typedef ac_fixed<CNN_COEFF_P> CNN_COEFF_TYPE;
typedef ac_fixed<CNN_NORM_P> CNN_NORM_TYPE;

#endif
