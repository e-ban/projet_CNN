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
      |__ testConvolution.py : python script that processes a picture with a convolution alone and write pgm files of each canal
      |
      |__ testNormalization.py : python script that write input picture as pgm and normalized picture as well

To run the script files :
python3 CNN.py
python3 testCIFAR10.py
python3 testConvolution.py
python3 testNormalization.py

To clean pgm and .h :
./clean.sh
