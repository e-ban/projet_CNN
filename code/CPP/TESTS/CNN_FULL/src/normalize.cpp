/**
* @file CNN.cpp
* @author Iban Guinebert & Antoine Maillefert
* @brief normalization of picture
**/
#include "normalize.h"
#include <math.h>
void normalize(  CNN_DATA_TYPE* imageIN,  CNN_DATA_TYPE* imageOUT)
{
  double u[3]={0,0,0};
  double s[3]={0,0,0};
  double umoy=0,sigmoy=0;
  for(int ipix=0; ipix< CNN_IMAGE_IN_SIZE;ipix+=3)
  {
    for (int k=0;k<3;k++)
    {
      u[k]+=imageIN[ipix+k].to_double();
    }
  }
  for(int k =0; k<3;k++)
  {
    u[k]=u[k]/576.0;
    umoy+=u[k];
  }
  umoy=umoy/3;
  for(int j=0;j<CNN_IMAGE_IN_SIZE;j+=3)
  {
    for (int k=0;k<3;k++)
    {
      s[k]+=(imageIN[j+k].to_double()-umoy)*(imageIN[j+k].to_double()-umoy);
    }
  }
  for(int k=0;k<3;k++)
  {
    s[k]=sqrt(s[k]);
    s[k]=s[k]/24;
    sigmoy+=s[k];
  }
  sigmoy=sigmoy/3;
  for(int j=0;j<CNN_IMAGE_IN_SIZE;j+=3)
  {
    for (int k=0;k<3;k++)
    {
      if(s[k]>0.03125) imageOUT[j+k]=(CNN_DATA_TYPE)((imageIN[j+k].to_double()-umoy)/sigmoy);
      else imageOUT[j+k]=(CNN_DATA_TYPE)((imageIN[j+k].to_double()-umoy)*24);
    }
  }
}
