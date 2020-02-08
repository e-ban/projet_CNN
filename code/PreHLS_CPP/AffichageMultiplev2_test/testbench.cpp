#include "ac_fixed.h"
#include "ac_channel.h"
#include 

#include "centeredCrop.h"

#define CNN_DATA_P 20, 10, true, AC_RND
#define CNN_COEFF_P 20, 10, true, AC_RND
#define CNN_NORM_P 20,10,false,AC_RND
#define CNN_DATA_OUT_P 8, 8, false, AC_RND

#define CNN_IMAGE_IN_H 24
#define CNN_IMAGE_IN_W 32
#define CNN_IMAGE_IN_C 1
#define CNN_IMAGE_IN_SIZE CNN_IMAGE_IN_H*CNN_IMAGE_IN_W*CNN_IMAGE_IN_C

#define CNN_CONV1_OUT_H 24
#define CNN_CONV1_OUT_W 32
#define CNN_CONV1_OUT_C 64
#define CNN_CONV1_OUT_RC 4
#define CNN_CONV1_OUT_SIZE CNN_CONV1_OUT_H*CNN_CONV1_OUT_W*CNN_CONV1_OUT_RC


typedef ac_fixed<CNN_DATA_P> CNN_DATA_TYPE;
typedef ac_fixed<CNN_COEFF_P> CNN_COEFF_TYPE;
typedef ac_fixed<CNN_NORM_P> CNN_NORM_TYPE;
typedef ac_fixed<CNN_DATA_OUT_P> CNN_DATA_OUT_TYPE;

static CNN_DATA_TYPE input[CNN_CONV1_OUT_SIZE];
static CNN_DATA_TYPE output[CNN_IMAGE_IN_SIZE];

void create_pic(CNN_DATA_TYPE input[CNN_CONV1_OUT_SIZE]){
  for (int i=0;i<CNN_CONV1_OUT_SIZE/4;i++) input[i]=1;
  for (int j=0;j<CNN_CONV1_OUT_SIZE/4;j++) input[j]=2;
  for (int k=0;k<CNN_CONV1_OUT_SIZE/4;k++) input[k]=3;
  for (int l=0;l<CNN_CONV1_OUT_SIZE/4;l++) input[l]=4;}

void centered_crop(CNN_DATA_TYPE input[CNN_CONV1_OUT_SIZE], CNN_DATA_TYPE output[CNN_IMAGE_IN_SIZE]){

  int rh=CNN_CONV1_OUT_H % (2*CNN_CONV1_OUT_RC);
  int rw=CNN_CONV1_OUT_W % (2*CNN_CONV1_OUT_RC);
  int red_h;
  int red_w;

  if (rh!=0){
    red_h = (CNN_CONV1_OUT_H-rh) / (2*CNN_CONV1_OUT_RC);
  }else red_h = CNN_CONV1_OUT_H / (2*CNN_CONV1_OUT_RC);
  
  if (rw!=0){
    red_w = (CNN_CONV1_OUT_W-rw) / (2*CNN_CONV1_OUT_RC);
  }else red_w = CNN_CONV1_OUT_W / (2*CNN_CONV1_OUT_RC);
  

  int c=0;
  for (int k=0; k<CNN_CONV1_OUT_RC; k++){
    int w=0;
    for (int i=CNN_CONV1_OUT_W*red_h; i<CNN_IMAGE_IN_SIZE-CNN_CONV1_OUT_W*red_h;i++){

      if (w>=red_w && w<(CNN_CONV1_OUT_W-red_w+1)){
        output[c]=input[k*CNN_IMAGE_IN_SIZE+i];
        c+=1;
      }else if (w==CNN_CONV1_OUT_W){
        w=0;
      w+=1;
      }
    }
  }
}

void show_pic(CNN_DATA_TYPE output[CNN_IMAGE_IN_SIZE]){
  








