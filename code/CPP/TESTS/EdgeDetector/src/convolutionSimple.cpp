/**
* @file convolution.cpp
* @author Iban Guinebert & Antoine Maillefert
* @brief Contains the convolution function
**/
#include "convolutionSimple.h"
/**
* @param datain An array of data as input
* @param dataout An array to write the resulting array in
* @param kernel Array of weights coefficient for the kernel
* @brief Proceeds to the convolution of a kernel of weights on datain
**/
void convolutionReLU( CNN_DATA_OUT_TYPE datain[CNN_IMAGE_IN_SIZE], CNN_DATA_OUT_TYPE dataout[CNN_CONV1_OUT_SIZE], CNN_COEFF_TYPE kernel[CNN_KERNEL1_SIZE]){

	int height_in,width_in,canal_in,height_out, width_out, canal_out;
	height_in = CNN_IMAGE_IN_H;
        width_in = CNN_IMAGE_IN_W;
        canal_in = CNN_IMAGE_IN_C;
        height_out = CNN_CONV1_OUT_H;
        width_out = CNN_CONV1_OUT_W;
        canal_out = CNN_CONV1_OUT_RC;

	CNN_DATA_TYPE s= 0;
    	for(int row=0;row<height_out;row++)
	{
      	  for(int col=0; col<width_out;col++)
	  {
            for (int outChannel=0;outChannel<canal_out;outChannel++)
	      {
       	      s=0;
       	      for (int kerH=-CNN_KERNEL_H/2; kerH<=CNN_KERNEL_H/2;kerH++)
	      {
       	        for (int kerW=-CNN_KERNEL_W/2; kerW<=CNN_KERNEL_W/2;kerW++)
		{
       	          for(int inChannel=0;inChannel<canal_in;inChannel++)
		  {
       	            if(row+kerH>=0 && row+kerH<height_in && col+kerW>=0 && col+kerW<width_in)
		    {
       	              s=s+(CNN_DATA_OUT_TYPE)datain[width_in*canal_in*(row+kerH)+canal_in*(col+kerW)+inChannel]*kernel[CNN_KERNEL_W*canal_in*canal_out*(kerH+1)+canal_in*canal_out*(kerW+1)+canal_out*inChannel+outChannel];
       	            }
       	          }
       	        }
       	      }
       	      if(s<0)  s=0;
       	      dataout[width_out*canal_out*row+canal_out*col+outChannel]=s;
       	    }
      	  }
	}
  }
