This directory contains python files to test the Convolutional Neural Network

Content of directory :

Reference_python
      |
      |__ generated_pgm/  : contains the generated images from python programs
      |
      |__ clean.sh : script to clean the generated files of the directory
      |
      |__ CNN_upgrade.py : Latest version of the CNN functions
      |
      |__ CNN.py : older version of the CNN functions (not up-to-date)
      |
      |__ dicoCoeff.py : contains the functions to generate a coefficient dictionary for the CNN, when you run it as a script, it creates a .h file for the PreHLS that contains the coefficients
      |
      |__ ioPGM.py : contains the functions that writes or read images from pgm or binaries
      |
      |__ README.md : the current file
      |
      |__ testCIFAR10.py : python script that processes images from data_batch_1.bin in the CNN then compare the resulting label with the right one
      |
      |__ testLayers.py : python script that processes a picture through layers of CNN and print pgm traces for debugging
      |
      |__ generateImageHeader.py : python script that read a picture in raw format and create C header files with initialised array of the picture and its normalization
      |
      |__ generatePNGTraces.sh : script that generate PGM traces and convert some in png at a bigger size for report

Usage :
To run the script files :
python3 CNN.py
python3 testCIFAR10.py
python3 testLayers.py
python3 generateImageHeader.py

To generate useful traces for report :
./generatePNGTraces.sh

To clean pgm and .h :
./clean.sh

To generate documentation :
doxygen Doxyfile
