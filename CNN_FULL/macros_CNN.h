#ifndef __MACROS_CNN__
#define __MACROS_CNN__

/*Parameters of ac_fixed*/
#define CNN_IMAGE_P 8,8,false,AC_RND
#define CNN_UDATA_P 20, 10, false, AC_RND
#define CNN_DATA_P 20, 10, true, AC_RND
#define CNN_COEFF_P 20, 10, true, AC_RND
#define CNN_NORM_P 20,10,false,AC_RND
#define CNN_MASK_P 1,1,false,AC_RND

/*Size of arrays*/
#define CNN_IMAGE_FULL_H 32
#define CNN_IMAGE_FULL_W 32
#define CNN_IMAGE_FULL_C 3
#define CNN_IMAGE_FULL_SIZE CNN_IMAGE_FULL_H*CNN_IMAGE_FULL_W*CNN_IMAGE_FULL_C

#define CNN_IMAGE_IN_H 24
#define CNN_IMAGE_IN_W 24
#define CNN_IMAGE_IN_C 3
#define CNN_IMAGE_IN_SIZE CNN_IMAGE_IN_H*CNN_IMAGE_IN_W*CNN_IMAGE_IN_C

#define CNN_CONV1_IN_H 24
#define CNN_CONV1_IN_W 24
#define CNN_CONV1_IN_C 3
#define CNN_CONV1_IN_SIZE CNN_CONV1_IN_H*CNN_CONV1_IN_W*CNN_CONV1_IN_C


#define CNN_CONV1_OUT_H 24
#define CNN_CONV1_OUT_W 24
#define CNN_CONV1_OUT_C 64
#define CNN_CONV1_OUT_SIZE CNN_CONV1_OUT_H*CNN_CONV1_OUT_W*CNN_CONV1_OUT_C


#define CNN_CONV2_IN_H 12
#define CNN_CONV2_IN_W 12
#define CNN_CONV2_IN_C 64
#define CNN_CONV2_IN_SIZE CNN_CONV2_IN_H*CNN_CONV2_IN_W*CNN_CONV2_IN_C

#define CNN_CONV2_OUT_H 12
#define CNN_CONV2_OUT_W 12
#define CNN_CONV2_OUT_C 32
#define CNN_CONV2_OUT_SIZE CNN_CONV2_OUT_H*CNN_CONV2_OUT_W*CNN_CONV2_OUT_C


#define CNN_CONV3_IN_H 6
#define CNN_CONV3_IN_W 6
#define CNN_CONV3_IN_C 32
#define CNN_CONV3_IN_SIZE CNN_CONV3_IN_H*CNN_CONV3_IN_W*CNN_CONV3_IN_C

#define CNN_CONV3_OUT_H 6
#define CNN_CONV3_OUT_W 6
#define CNN_CONV3_OUT_C 20
#define CNN_CONV3_OUT_SIZE CNN_CONV3_OUT_H*CNN_CONV3_OUT_W*CNN_CONV3_OUT_C


#define CNN_PER_IN_H 3
#define CNN_PER_IN_W 3
#define CNN_PER_IN_C 20
#define CNN_PER_IN_SIZE CNN_PER_IN_H*CNN_PER_IN_W*CNN_PER_IN_C

#define CNN_KERNEL_H 3
#define CNN_KERNEL_W 3
#define CNN_KERNEL1_SIZE CNN_KERNEL_H*CNN_KERNEL_W*CNN_CONV1_OUT_C*CNN_IMAGE_IN_C
#define CNN_KERNEL2_SIZE CNN_KERNEL_H*CNN_KERNEL_W*CNN_CONV2_IN_C*CNN_CONV2_OUT_C
#define CNN_KERNEL3_SIZE CNN_KERNEL_H*CNN_KERNEL_W*CNN_CONV3_IN_C*CNN_CONV3_OUT_C

#define CNN_OUT 10
#define CNN_MAXP_SIZE 3
#define CNN_MAXP_STRIDE 2

#define CNN_VGA_H 240
#define CNN_VGA_W 320
#define CNN_VGA_C 1
#define CNN_VGA_SIZE CNN_VGA_H*CNN_VGA_W*CNN_VGA_C

#endif
