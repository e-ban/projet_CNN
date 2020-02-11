#!/usr/bin/env python
from CNN_upgrade import *
from ioPGM import *
import numpy as np

PictureSel=0

if __name__=="__main__":
    import dicoCoeff
    d=dicoCoeff.DicoCoeff("CNN_coeff_3x3.txt")
    imglder=ImageLoader("data_batch_1.bin",PictureSel)
    label,image = imglder.loadNewImage()
    #imageTest=centered_crop(image,24,24)
    write_pgm(image,"input")
    cnn=CNN(d.dico)

    #normalization
    cnn.addNormalizeLayer()
    res=cnn.run(image)
    resBig=np.array([80*abs(res.reshape(res.size)[i]) for i in range(res.size)]).reshape(res.shape)
    write_pgm(resBig,"inputNormalized")
    #crop
    imageTest=centered_crop(res,24,24)
    resBig=np.array([80*abs(imageTest.reshape(imageTest.size)[i]) for i in range(imageTest.size)]).reshape(imageTest.shape)
    write_pgm(resBig,"inputCropped")
    #Convolution tests
    cnn.addConvolLayer("conv1")
    res=cnn.run(imageTest)
    resBig=np.array([80*abs(res.reshape(res.size)[i]) for i in range(res.size)]).reshape(res.shape)
    write_Npgm(resBig,"convol1")

    #Maxpool tests
    cnn.addMaxPoolingLayer([3,3],[2,2])
    res=cnn.run(imageTest)
    resBig=np.array([80*abs(res.reshape(res.size)[i]) for i in range(res.size)]).reshape(res.shape)
    write_Npgm(resBig,"maxpool1")

    #Convolution tests
    cnn.addConvolLayer("conv2")
    res=cnn.run(imageTest)
    resBig=np.array([80*abs(res.reshape(res.size)[i]) for i in range(res.size)]).reshape(res.shape)
    write_Npgm(resBig,"convol2")

    #Maxpool tests
    cnn.addMaxPoolingLayer([3,3],[2,2])
    res=cnn.run(imageTest)
    resBig=np.array([80*abs(res.reshape(res.size)[i]) for i in range(res.size)]).reshape(res.shape)
    write_Npgm(resBig,"maxpool2")

    #Convolution tests
    cnn.addConvolLayer("conv3")
    res=cnn.run(imageTest)
    resBig=np.array([80*abs(res.reshape(res.size)[i]) for i in range(res.size)]).reshape(res.shape)
    write_Npgm(resBig,"convol3")

    #Maxpool tests
    cnn.addMaxPoolingLayer([3,3],[2,2])
    res=cnn.run(imageTest)
    resBig=np.array([80*abs(res.reshape(res.size)[i]) for i in range(res.size)]).reshape(res.shape)
    write_Npgm(resBig,"maxpool3")
