#!/usr/bin/env python
from CNN_upgrade import *
import numpy as np

if __name__=="__main__":
    imglder=ImageLoader("data_batch_1.bin",0)
    (label,image)=imglder.loadNewImage()
    #print(image)
    import dicoCoeff
    d=dicoCoeff.DicoCoeff("CNN_coeff_3x3.txt")
    cnn=CNN(d.dico)
    cnn.addNormalizeLayer()
    crop=centered_crop(image,24,24)
    result=cnn.run(crop)
    print(result)
    f=open("imageNorm.h","w")
    f.write("CNN_DATA_TYPE imageNorm["+str(result.size)+"={")
    for line in range(result.shape[0]):
        for col in range(result.shape[1]):
            for can in range(result.shape[2]):
                f.write(str(result[line,col,can]))
                f.write(",")
        f.write("\n")
    f.write("};")
    f.close()
    f=open("image.h","w")
    f.write("CNN_DATA_TYPE imageIN["+str(result.size)+"={")
    for line in range(crop.shape[0]):
        for col in range(crop.shape[1]):
            for can in range(crop.shape[2]):
                f.write(str(crop[line,col,can]))
                f.write(",")
        f.write("\n")
    f.write("};")
    f.close()
