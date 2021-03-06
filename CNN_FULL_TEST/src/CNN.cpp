#include "CNN.h"
#include "ioImage.h"

#pragma hls_design top

extern CNN_DATA_TYPE* imageIN;
extern char resultlabel;
extern bool verbosity;
extern bool outFiles;
void ImgProcTest(CNN_IMAGE_TYPE* img_in,CNN_IMAGE_TYPE* img_out)
{

  CNN_DATA_TYPE mem1[CNN_CONV1_OUT_SIZE];
  CNN_DATA_TYPE mem2[CNN_CONV1_OUT_SIZE];
//  img_out[0]=img_in[0];

  convolutionReLU(imageIN,mem2,conv1_weights,conv1_biases,1);
  if(outFiles) saveMultiOutput("output/conv1",(void*)mem2,'d',CNN_CONV1_OUT_H,CNN_CONV1_OUT_W,CNN_CONV1_OUT_C);
  maxpool(mem2,mem1,1);
  if(outFiles) saveMultiOutput("output/max1",(void*)mem1,'d',CNN_CONV2_IN_H,CNN_CONV2_IN_W,CNN_CONV2_IN_C);
  convolutionReLU(mem1,mem2,conv2_weights,conv2_biases,2);
  if(outFiles) saveMultiOutput("output/conv2",(void*)mem2,'d',CNN_CONV2_OUT_H,CNN_CONV2_OUT_W,CNN_CONV2_OUT_C);
  maxpool(mem2,mem1,2);
  if(outFiles) saveMultiOutput("output/max2",(void*)mem1,'d',CNN_CONV3_IN_H,CNN_CONV3_IN_W,CNN_CONV3_IN_C);
  convolutionReLU(mem1,mem2,conv3_weights,conv3_biases,3);
  if(outFiles) saveMultiOutput("output/conv3",(void*)mem2,'d',CNN_CONV3_OUT_H,CNN_CONV3_OUT_W,CNN_CONV3_OUT_C);
  maxpool(mem2,mem1,3);
  if(outFiles) saveMultiOutput("output/max3",(void*)mem1,'d',CNN_PER_IN_H,CNN_PER_IN_W,CNN_PER_IN_C);
  //reshape(mem1,mem2);
  /*if(verbosity){
    std::cout << "pre-perc="<<std::endl;
    printMatrix(mem1,'d',180,1,1);
  }*/
  perceptron(mem1,mem2,local3_weights,local3_biases);
  if(outFiles) saveOutput("output/perceptron",(void*)mem2,'d',10,1,1,"P2",0);
  char label=0;
  CNN_DATA_TYPE max=-510;
  for (int j=0;j<10;j++)
  {
    if (mem2[j]>max)
    {
      max=mem2[j];
      label = j;
    }
  }
/*  if(verbosity){
    std::cout << "Proba="<<std::endl;
    printMatrix(mem2,'d',1,10,1);
  }*/
  resultlabel=label;
  display(label,imageIN,img_out);
}
