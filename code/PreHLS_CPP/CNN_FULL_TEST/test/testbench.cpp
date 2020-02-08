#include "CNN.h"
#include "ioImage.h"
#include "normalize.h"
#include <string>
#include <iostream>
#include "image_test_CNN.h"
bool verbosity=false;
bool outFiles=false;
//CNN_DATA_TYPE* imageIN;
char resultlabel;

using namespace std;
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

void resizeMatrix(CNN_IMAGE_TYPE* imageIn,CNN_DATA_TYPE* imageOUT)
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
          imageOUT[io*CNN_IMAGE_IN_C*CNN_IMAGE_IN_W+jo*CNN_IMAGE_IN_C+c]=(CNN_DATA_TYPE)imageIn[ii*CNN_IMAGE_FULL_C*CNN_IMAGE_FULL_W+ji*CNN_IMAGE_FULL_C+c];
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

        case 'o':case 'O':
        outFiles=true;
        break;

        default:
        usage(argv[0]);
        break;
      }
    }
    NBloop=atoi(argv[2]);
  }
  else usage(argv[0]);
  CNN_IMAGE_TYPE* img_in = (CNN_IMAGE_TYPE*)calloc(CNN_VGA_SIZE,sizeof(*img_in));
  CNN_IMAGE_TYPE* img_out = (CNN_IMAGE_TYPE*)calloc(CNN_VGA_SIZE,sizeof(*img_out));
  CNN_IMAGE_TYPE* imgInput = (CNN_IMAGE_TYPE*)calloc(CNN_IMAGE_FULL_SIZE,sizeof(*img_out));
  CNN_DATA_TYPE* imgResized = (CNN_DATA_TYPE*)calloc(CNN_IMAGE_IN_SIZE,sizeof(*imgResized));
  CNN_DATA_TYPE imageIN [CNN_IMAGE_IN_SIZE];
  //Start of test
  cout << "Start CNN" << endl;
  char label=6;
  double success=0;
  for (int i =NBloop-1;i<NBloop;i++)
  {
    label=loadPictureRAW(imgInput,"data_batch_1.bin",i);
    if(label<0) break;
    if(outFiles) saveOutput("output/input"+to_string(i),(void*)imgInput,'i',CNN_IMAGE_FULL_H,CNN_IMAGE_FULL_W,CNN_IMAGE_FULL_C,"P3",0);

    resizeMatrix(imgInput,imgResized);//Resized);
    if(outFiles) saveOutput("output/inputResized"+to_string(i),(void*)imgResized,'d',CNN_IMAGE_IN_H,CNN_IMAGE_IN_W,CNN_IMAGE_IN_C,"P3",0);

    normalize(imgResized,imageIN);

    if(outFiles) saveOutput("output/inputNormalized"+to_string(i),(void*)imageIN,'d',CNN_IMAGE_IN_H,CNN_IMAGE_IN_W,CNN_IMAGE_IN_C,"P3",0);

    ImgProcTest(img_in,imageIN,img_out);
    if(outFiles) saveOutput("output/output"+to_string(i)+labelsTab[label]+to_string(i),(void*)img_out,'i',CNN_VGA_H,CNN_VGA_W,CNN_VGA_C,"P2",0);

    if(label==resultlabel)
    {
      if(verbosity) cout << "Image "<<i<<" : Success"<<endl;
      success++;
    }
    if(verbosity) cout <<"Image "<<i<<" ("<<labelsTab[label]<<") result is "<<labelsTab[resultlabel]<< "\n\ttotal success rate = "<< success/(i+1)<<endl;
  }

  free(img_out);
  free(img_in);
  free(imgResized);
  free(imgInput);

  if(label<0) exit(2);
}
