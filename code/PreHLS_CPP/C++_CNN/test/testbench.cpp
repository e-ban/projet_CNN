#include "CNN.h"
#include "loadPicture.h"
#include <string>
bool verbosity=false;

void resizeMatrix(CNN_IMAGE_TYPE* imageIn,CNN_IMAGE_TYPE* imageOUT)
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
          imageOUT[io*CNN_IMAGE_IN_C*CNN_IMAGE_IN_W+jo*CNN_IMAGE_IN_C+c]=(CNN_IMAGE_TYPE)imageIn[ii*CNN_IMAGE_FULL_C*CNN_IMAGE_FULL_W+ji*CNN_IMAGE_FULL_C+c];
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
  CNN_IMAGE_TYPE imageOut[CNN_VGA_SIZE];
  for (int j=0;j<CNN_VGA_SIZE;j++)
  {
    imageOut[j]=0;
  }
  CNN_IMAGE_TYPE imageCam[CNN_VGA_SIZE];
  //loadFilePGM(image);
  for (int i=NBloop-1; i<NBloop;i++)
  {
    /*loadPictureRAW(image,"data_batch_1.bin",i);
    resizeMatrix(image,imageCam);*/
    /*if(verbosity) savePicture("gen_pic/image_in"+std::to_string(i),image,0);
    if(verbosity) savePictureRed("gen_pic/image_rsized"+std::to_string(i),imageCam,0);
*/
    CNN(imageCam,imageOut);
    if(verbosity) saveOutput("gen_pic/image_out"+std::to_string(i),imageOut);
  }

}
