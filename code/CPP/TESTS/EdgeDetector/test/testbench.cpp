#include "edgeDetector.h"
#include "ioImage.h"

int main()
{
  CNN_DATA_OUT_TYPE img_in[CNN_IMAGE_IN_SIZE];
  CNN_DATA_OUT_TYPE img_out[CNN_IMAGE_IN_SIZE];
  loadFilePGM(img_in,"tigre.pgm");
  ImgProcTest(img_in,img_out);
  saveOutput("output",img_out,'i',240,320,1,"P2",1);

}
