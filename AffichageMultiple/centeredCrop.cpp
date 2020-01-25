#include "centeredCrop.h"

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
