#include "normalize.h"
#include <math.h>
void normalize(  CNN_DATA_TYPE* imageIN,  CNN_DATA_TYPE* imageOUT)
{
  double u[3]={0,0,0};
  double s[3]={0,0,0};
  for(int ipix=0; ipix< CNN_IMAGE_IN_SIZE;ipix+=3)
  {
    for (int k=0;k<3;k++)
    {
      u[k]+=imageIN[ipix+k].to_int();
    }
  }
  for(int k =0; k<3;k++)
  {
    u[k]=u[k]/576;
  }
  for(int j=0;j<CNN_IMAGE_IN_SIZE;j+=3)
  {
    for (int k=0;k<3;k++)
    {
      s[k]+=(imageIN[j+k].to_int()-u[k])*(imageIN[j+k].to_int()-u[k]);
    }
  }
  for(int k=0;k<3;k++)
  {
    s[k]=sqrt(s[k]);
    s[k]=s[k]/24;
  }
  for(int j=0;j<CNN_IMAGE_IN_SIZE;j+=3)
  {
    for (int k=0;k<3;k++)
    {
      if(s[k]>0.03125) imageOUT[j+k]=(CNN_DATA_TYPE)((imageIN[j+k].to_int()-u[k])/s[k]);
      else imageOUT[j+k]=(CNN_DATA_TYPE)((imageIN[j+k].to_int()-u[k])*24);
    }
  }
}
