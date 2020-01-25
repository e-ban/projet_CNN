#include "display.h"

void display(CNN_DATA_TYPE input[CNN_IMAGE_IN_SIZE], CNN_DATA_OUT_TYPE output[CNN_IMAGE_IN_SIZE]){
	
	for(int i=0; i<CNN_IMAGE_IN_H;i++){
		for (int j=0;j<CNN_IMAGE_IN_W;j++){
			if (input[i*CNN_IMAGE_IN_W+j]<0) output[i*CNN_IMAGE_IN_W + j]=0;
			else output[i*CNN_IMAGE_IN_W + j]=(CNN_DATA_OUT_TYPE)input[i*CNN_IMAGE_IN_W+j];
		}
	}
}
