# projet_CNN
This repository contains all the final files of project Convolutional Neural Network

Hierarchical structure :

projet_CNN/
      |
      |__code/
      |   |__CPP/
      |   |   |__TEST/
      |   |   |   |__MultipleDisplay/  => C/CPP sources and tests for the display of several output on a screen
      |   |   |   |__CNN_FULL/         => C/CPP sources and tests for the Computation of the entirety of the CNN
      |   |   |   |__EdgeDetector/     => C/CPP sources and tests for the edge detector convolution
      |   |   |
      |   |   |__PreHLS/ => sources ready to be synthesized with Catapult
      |   |       |__CNN/
      |   |       |__Convolution/
      |   |       |__EdgeDetector/
      |   |
      |   |__Python/                   => Python sources and scripts for evaluation of the algorithm
      |
      |__Bitstreams/
      |   |__CNN.bit                   => [old] version of CNN that prints normalized picture
      |   |__CNN_v2.bit                => final version of CNN that prints input picture
      |   |__edge_detector1.bit        => [old] version of edge detector
      |   |__edge_detector2.bit        => final version of edge detector
      |
      |__doc/
      |__libs/                      => contains ac_types and ac_math libraries
      |__masks/                     => contains the 10 masks for the overlay in pgm format
      |__scripts/                   => contains several useful python scripts
      |->Makefile
      |->sourceme.sh

Necessary files :
ac_types : https://github.com/hlslibs/ac_types
ac_math : https://github.com/hlslibs/ac_math

Usage :
make install_ac_libs (get ac_types and ac_maths)
make clean_all => clean all repositories in project folder
make cleaner => clean_all+uninstall libraries

Source libraries for tests :
source sourceme.h
