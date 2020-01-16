#ifndef __IMGPROC_VFIX__
#define __IMGPROC_VFIX__


#define IMGPROC_A_PS 20, 10, true, AC_RND
#define IMGPROC_IMAGE_IN_H 24
#define IMGPROC_IMAGE_IN_W 24
#define IMGPROC_IMAGE_IN_C 3
#define IMGPROC_IMAGE_IN_P 20, 10, true, AC_RND
#define IMGPROC_IMAGE_IN_SIZE IMGPROC_IMAGE_IN_H*IMGPROC_IMAGE_IN_W*IMGPROC_IMAGE_IN_C

#define IMGPROC_CONV1_IN_H 24
#define IMGPROC_CONV1_IN_W 24
#define IMGPROC_CONV1_IN_C 3
#define IMGPROC_CONV1_IN_P 20, 10, true, AC_RND
#define IMGPROC_CONV1_IN_SIZE IMGPROC_CONV1_IN_H*IMGPROC_CONV1_IN_W*IMGPROC_CONV1_IN_C

#define IMG_PROC_NORM_P 20,10,false,AC_RND
#define IMGPROC_CONV1_OUT_H 24
#define IMGPROC_CONV1_OUT_W 24
#define IMGPROC_CONV1_OUT_C 64
#define IMGPROC_CONV1_OUT_P 20, 10, true, AC_RND
#define IMGPROC_CONV1_OUT_SIZE IMGPROC_CONV1_OUT_H*IMGPROC_CONV1_OUT_W*IMGPROC_CONV1_OUT_C

#define IMGPROC_KERNEL1_H 3
#define IMGPROC_KERNEL1_W 3
#define IMGPROC_KERNEL1_P 20, 10, true, AC_RND
#define IMGPROC_KERNEL1_SIZE IMGPROC_KERNEL1_H*IMGPROC_KERNEL1_W*IMGPROC_CONV1_OUT_C*IMGPROC_IMAGE_IN_C

#define IMGPROC_CONV2_IN_H 12
#define IMGPROC_CONV2_IN_W 12
#define IMGPROC_CONV2_IN_C 64
#define IMGPROC_CONV2_IN_P 20, 10, true, AC_RND
#define IMGPROC_CONV2_IN_SIZE IMGPROC_CONV2_IN_H*IMGPROC_CONV2_IN_W*IMGPROC_CONV2_IN_C

#define IMGPROC_CONV2_OUT_H 12
#define IMGPROC_CONV2_OUT_W 12
#define IMGPROC_CONV2_OUT_C 32
#define IMGPROC_CONV2_OUT_P 20, 10, true, AC_RND
#define IMGPROC_CONV2_OUT_SIZE IMGPROC_CONV2_OUT_H*IMGPROC_CONV2_OUT_W*IMGPROC_CONV2_OUT_C

#define IMGPROC_KERNEL2_H 3
#define IMGPROC_KERNEL2_W 3
#define IMGPROC_KERNEL2_P 20, 10, true, AC_RND
#define IMGPROC_KERNEL2_SIZE IMGPROC_KERNEL2_H*IMGPROC_KERNEL2_W*IMGPROC_CONV2_OUT_C*IMGPROC_CONV1_OUT_C

#define IMGPROC_CONV3_IN_H 6
#define IMGPROC_CONV3_IN_W 6
#define IMGPROC_CONV3_IN_C 32
#define IMGPROC_CONV3_IN_P 20, 10, true, AC_RND
#define IMGPROC_CONV3_IN_SIZE IMGPROC_CONV3_IN_H*IMGPROC_CONV3_IN_W*IMGPROC_CONV3_IN_C

#define IMGPROC_CONV3_OUT_H 6
#define IMGPROC_CONV3_OUT_W 6
#define IMGPROC_CONV3_OUT_C 20
#define IMGPROC_CONV3_OUT_P 20, 10, true, AC_RND
#define IMGPROC_CONV3_OUT_SIZE IMGPROC_CONV3_OUT_H*IMGPROC_CONV3_OUT_W*IMGPROC_CONV3_OUT_C

#define IMGPROC_KERNEL3_H 3
#define IMGPROC_KERNEL3_W 3
#define IMGPROC_KERNEL3_P 20, 10, true, AC_RND
#define IMGPROC_KERNEL3_SIZE IMGPROC_KERNEL3_H*IMGPROC_KERNEL3_W*IMGPROC_CONV3_OUT_C*IMGPROC_CONV2_OUT_C

#define IMGPROC_PER_IN_H 180
#define IMGPROC_PER_IN_W 10
#define IMGPROC_PER_IN_P 20, 10, true, AC_RND
#define IMGPROC_PER_IN_SIZE IMGPROC_PER_IN_H*IMGPROC_PER_IN_W

#define IMGPROC_CNN_OUT 10

#define IMGPROC_MAXP_SIZE 3
#define IMCPROC_MAXP_STRIDE 2

#endif
