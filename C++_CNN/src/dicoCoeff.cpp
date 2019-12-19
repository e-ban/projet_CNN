#include "CNN.hpp"
#include <iostream>
#include <fstream>

struct dicoElement
{
  string label;
  c_type* tab;
};

enum dicoState

class CDicoCoeff{
 private :
    (struct dicoElement) * dico;
    enum dicoState currentState;
 public:
   void loadDico(string filename);
   void dicoFsm(string line);
};



void CDicoCoeff::loadDico(string filename)
{
  ifstream INPUT_FILE(filename);
  if(INPUT_FILE.is_open())
  {
    while(INPUT_FILE.getline())
    {
      /*call to fsm*/
    }
  }
}
