#include "order.h"

void order(CNN_DATA_TYPE input[CNN_IMAGE_IN_SIZE], CNN_DATA_TYPE output[CNN_IMAGE_IN_SIZE]){


  int ligne;
  if ((CNN_IMAGE_IN_H % 2)!=0){
    ligne=(CNN_IMAGE_IN_H+1)/2;
  }else ligne=CNN_IMAGE_IN_H/2;


  int nb_col;
  int r_col;
  int colonne;
    if ((CNN_CONV1_OUT_RC % 2)!=0){
      nb_col = (CNN_CONV1_OUT_RC+1)/2;
      r_col=CNN_IMAGE_IN_W % nb_col;
      if (r_col!=0){
        colonne=(CNN_IMAGE_IN_W+r_col)/nb_col;
      }else colonne=(CNN_IMAGE_IN_W/nb_col);

    }else{
      nb_col = CNN_CONV1_OUT_RC/2;
      r_col=CNN_IMAGE_IN_W % nb_col;
      if (r_col!=0){
        colonne=(CNN_IMAGE_IN_W+r_col)/nb_col;
      }else colonne=(CNN_IMAGE_IN_W/nb_col);
    }

  int c=0;
  for (int i=0; i<nb_col; i++){
    for (int k=0; k<ligne; k++){  
      for (int j=0; j<colonne; j++){
        output[k*(i*colonne+j)]=input[c];
        c+=1;
      }
    }
  }

  for (int i=0; i<nb_col; i++){
    for (int k=ligne; k<CNN_IMAGE_IN_H; k++){  
      for (int j=0; j<colonne; j++){
        output[k*(i*colonne+j)]=input[c];
        c+=1;
      }
    }  
  }
}
