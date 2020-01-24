#include "order.h"

void order((CNN_DATA_TYPE input[CNN_IMAGE_IN_SIZE], CNN_DATA_OUT_TYPE output[CNN_IMAGE_IN_SIZE]){


  CNN_DATA_OUT_TYPE ligne;
  if ((CNN_IMAGE_IN_H % 2)=!0){
    ligne=(CNN_IMAGE_IN_H+1)/2;
  }else ligne=CNN_IMAGE_IN_H/2;


  CNN_DATA_OUT_TYPE colonne;
    if ((CNN_CONV1_OUT_RC % 2)=!0){
      int nb_col = (CNN_CONV1_OUT_RC+1)/2;
      int r_col=CNN_IMAGE_IN_W % nb_col;
      if ((r_col)=!0{
        colonne=((CNN_IMAGE_IN_W+r_col)/nb_col;
      }else colonne=(CNN_IMAGE_IN_W/nb_col;

    }else{
      int nb_col = CNN_CONV1_OUT_RC/2;
      int r_col=CNN_IMAGE_IN_W % nb_col;
      if ((r_col)=!0{
        colonne=((CNN_IMAGE_IN_W+r_col)/nb_col;
      }else colonne=(CNN_IMAGE_IN_W/nb_col;


  int c=0
  for (int i=0; i<CNN_IMAGE_IN_SIZE;i++){
      
