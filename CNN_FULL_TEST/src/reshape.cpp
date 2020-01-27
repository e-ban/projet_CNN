#include "reshape.h"


void reshape(CNN_DATA_TYPE* input,CNN_DATA_TYPE* output){
  for (int depth=0;depth<CNN_PER_IN_H;depth++)
  {
    for (int col=0;col<CNN_PER_IN_H;col++)
    {
      for (int line=0;line<CNN_PER_IN_H;line++)
      {
        output[depth*CNN_PER_IN_H*CNN_PER_IN_W+line*CNN_PER_IN_W+col]=input[line*CNN_PER_IN_W*CNN_PER_IN_C+col*CNN_PER_IN_C+depth];
      }
    }
  }
}
