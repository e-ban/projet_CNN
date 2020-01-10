#include "CNN.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef std::map<string,std::array> dicoElement;

enum dicoState{
  initFSM,
  acquireDicoElementName,
  getValues
};

class CDicoCoeff{
 private :
    dicoElement * dico;
    enum dicoState currentState;
 public:
   void loadDico(string filename);
   void dicoFsm(string line);
};

void CDicoCoeff::dicoFsm(string line)
{
  switch(currentState)
  {
    case initFSM:
      


    break;

  }
}

void CDicoCoeff::loadDico(string filename)
{
  ifstream INPUT_FILE(filename);
  string lex;
  if(INPUT_FILE.is_open())
  {
    while(lex=INPUT_FILE.getline(" "))
    {
      cout << lex;
    }
  }
}
