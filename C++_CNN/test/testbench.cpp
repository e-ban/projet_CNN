#include "CNN.h"
#include "loadPicture.h"


bool verbosity=false;

void resizeMatrix(CNN_IMAGE_TYPE imageIN[CNN_IMAGE_FULL_SIZE],CNN_DATA_TYPE imageOUT[CNN_IMAGE_IN_SIZE])
{
  int marginH = (CNN_IMAGE_FULL_H-CNN_IMAGE_IN_H)/2;
  int marginW = (CNN_IMAGE_FULL_W-CNN_IMAGE_IN_W)/2;
  int io=0,jo=0;
  for (int ii =marginH;ii<CNN_IMAGE_FULL_H-marginH;ii++)
  {
    for (int ji =marginW;ji<CNN_IMAGE_FULL_W-marginW;ji++)
    {
      for (int c =0 ; c<CNN_IMAGE_FULL_C;c++)
        {
          imageOUT[io*CNN_IMAGE_IN_C*CNN_IMAGE_IN_W+jo*CNN_IMAGE_IN_C+c]=(CNN_DATA_TYPE)imageIN[ii*CNN_IMAGE_FULL_C*CNN_IMAGE_FULL_W+ji*CNN_IMAGE_FULL_C+c];
        }
      jo++;
    }
    io++;
    jo=0;
  }
}
int usage(char* progname)
{
    std::cout<< "Usage : "<<progname<<"[-v] number_of_pictures_to_process\nadding -v enable verbosity"<<std::endl;
    exit(1);
}
int main(int argc,char* argv[] )
{
  int NBloop=0;
  if(argc==2) NBloop=atoi(argv[1]);
  else if(argc==3)
  {
    char* p=argv[1];
    while(*p)
    {
      switch(*p++)
      {
        case '-':
        break;

        case 'v':case'V':
        verbosity=true;
        break;

        default:
        usage(argv[0]);
        break;
      }
    }
    NBloop=atoi(argv[2]);
  }
  else usage(argv[0]);

  CNN_IMAGE_TYPE image[CNN_IMAGE_FULL_SIZE];
  CNN_DATA_TYPE imageResized[CNN_IMAGE_IN_SIZE];
  CNN_DATA_TYPE mem1[CNN_CONV1_OUT_SIZE];
  CNN_DATA_TYPE mem2[CNN_CONV1_OUT_SIZE];
  CNN_IMAGE_TYPE imageOut[CNN_VGA_SIZE];
  //loadFilePGM(image);
  int success=0;
  string labelsTab[10]={
    "airplane",
    "automobile",
    "bird",
    "cat",
    "deer",
    "dog",
    "frog",
    "horse",
    "ship",
    "truck"};
  for (int i=0; i<NBloop;i++)
  {
    char resultLabel=0;
    char label=loadPictureRAW(image,"data_batch_1.bin",i);
    //if(verbosity) savePicture("gen_pic/imagefull",image,0);

    resizeMatrix(image,imageResized);
    //if(verbosity) savePictureRed("gen_pic/imageCut",imageResized,0);


    normalize(imageResized,mem1);
    if(verbosity) saveDATA("gen_pic/normalized",mem1);
/*
    convolutionReLU(mem1,mem2,conv1_weights,conv1_biases,1);
    if(verbosity) savePictureRed("gen_pic/conv1_",mem2,1);

    maxpool(mem2,mem1,1);
    if(verbosity) savePictureRed("gen_pic/maxp1_",mem1,2);

    convolutionReLU(mem1,mem2,conv2_weights,conv2_biases,2);
    //if(verbosity) savePictureRed("gen_pic/conv2_",mem2,1);

    maxpool(mem2,mem1,2);

    convolutionReLU(mem1,mem2,conv3_weights,conv3_biases,3);

    maxpool(mem2,mem1,3);
    if(verbosity) savePictureRed("gen_pic/maxp3_",mem1,4);*/
    //perceptron(mem1,mem2,local3_weights,local3_biases);
  //  CNN(imageResized,mem1,mem2,imageOut);
    /*if(verbosity) printResults(mem2);
    CNN_DATA_TYPE max=0;
    for (int j=0;j<10;j++)
    {
      if (mem2[j]>max)
      {
        max=mem2[j];
        resultLabel = j;
      }
    }
    if(label==resultLabel) success++;
    std::cout<<"Image "<<i<<" ["<<labelsTab[label]<<"] : result : "<<labelsTab[resultLabel]<<" |\t success Rate = "<<success/(i+1) << std::endl;
    */
  }
  //  if(verbosity) savePictureRed("output",imageOut,3);

}
