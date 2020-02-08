#include "perceptron.h"


void perceptron(CNN_DATA_TYPE input[], CNN_DATA_TYPE output[], CNN_COEFF_TYPE weights[],CNN_DATA_TYPE biases[])
{
  CNN_DATA_TYPE s=0;
  for (int i = 0 ; i< CNN_OUT; i++)
  {
    s=0;
    for (int j=0; j< CNN_PER_IN_SIZE;j++)
    {
      s+=input[j]*weights[j*CNN_OUT+i];
    }
    output[i]=s+biases[i];
  }

}
