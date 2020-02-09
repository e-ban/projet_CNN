#!/usr/bin/env python
from CNN_upgrade import *
from ioPGM import *
import numpy as np

if __name__=="__main__":
    import dicoCoeff
    d=dicoCoeff.DicoCoeff("CNN_coeff_3x3.txt")
    imglder=ImageLoader("data_batch_1.bin",0)
    cnn=CNN(d.dico)
    cnn.addConvolLayer("conv1")
    label,image = imglder.loadNewImage()
    imageTest=centered_crop(image,24,24)
    write_pgm(imageTest,"input")
    results=cnn.run(imageTest)
    print(results)
    write_Npgm(results,"convolTest")
