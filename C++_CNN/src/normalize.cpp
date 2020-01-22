#include "normalize.h"

void normalize(  CNN_DATA_TYPE imageIN[],  CNN_DATA_TYPE imageOUT[])
{
  CNN_NORM_TYPE u[3]={0,0,0};
  CNN_NORM_TYPE s[3]={0,0,0};
  for(int ipix=0; ipix< CNN_IMAGE_IN_SIZE;ipix+=3)
  {
    for (int k=0;k<3;k++)
    {
      u[k]+=imageIN[ipix+k];
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
      s[k]+=(imageIN[j+k]-u[k])*(imageIN[j+k]-u[k]);
    }
  }
  for(int k=0;k<3;k++)
  {
    ac_math::ac_sqrt(s[k],s[k]);
    s[k]=s[k]/24;
  }
  for(int j=0;j<CNN_IMAGE_IN_SIZE;j+=3)
  {
    for (int k=0;k<3;k++)
    {
      if(s[k]>0.03125) imageOUT[j+k]=(imageIN[j+k]-u[k])/s[k];
      else imageOUT[j+k]=(imageIN[j+k]-u[k])*24;
    }
  }
}
