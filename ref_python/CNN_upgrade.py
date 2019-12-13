#!/usr/bin/env python
import random as rd
import numpy as np
import math
import struct
import dicoCoeff

class layer :
    def __init__(self):
        self.output=[]

    def build(self,input):
        return (-1)


class ConvRELU(layer):
    def __init__(self,parameters):
        self.weights=parameters[0]
        self.biases=parameters[1]

    def build(self,input):
        height,width,canal=input.shape
        ker=self.weights
        bias=self.biases
        kHeight,kWidth,kChannelI,kChannelO=ker.shape
        self.output=np.array([0 for t in range(height*width*kChannelO)],dtype=np.float64).reshape(height,width,kChannelO)
        for row in range(height):
            for col in range(width):
                for outChannel in range(kChannelO):
                    s=0
                    for kerH in range(-kHeight//2,kHeight//2+1):
                        for kerW in range(-kWidth//2,kWidth//2+1):
                            for inChannel in range(canal):
                                if (kerH+row < height and kerW+col < width and kerH+row>=0 and kerW+col>=0):
                                    s=s+input[row+kerH,col+kerW,inChannel]*ker[kerH,kerW,inChannel,outChannel]
                    s=s+bias[outChannel]
                    if (s<0):
                        s=0
                    self.output[row,col,outChannel]=s

        return 0

class MaxPool(layer):
    def __init__(self,stride,size):
        self.stride=stride
        self.size=size

    def build(self,input):
        height,width,canal=input.shape
        self.output=np.array([0 for i in range((height//self.stride[0])*(width//self.stride[1])*canal)],dtype=np.float64).reshape(height//self.stride[0],width//self.stride[1],canal)
        for x in range(0,height,self.stride[0]):
            for y in range(0,width,self.stride[1]):
                for c in range(canal):
                    maxi=0
                    for poolH in range(self.size[0]):
                        for poolW in range(self.size[1]):
                            if(((x+poolH) < height) and ((y+poolW) < width) ):
                                if(input[x+poolH,y+poolW,c]) > maxi:
                                    maxi = input[x+poolH,y+poolW,c]
                            else :#zero padding
                                if(maxi<0):
                                    maxi=0
                    self.output[x//self.stride[0],y//self.stride[1],c]=maxi
        return(0)

class Normalize(layer):
    def build(self,input):
        height,width,canal=input.shape
        N=height * width
        self.output = np.array([0 for i in range(N*canal)],dtype=np.float64).reshape(input.shape)
        u=0
        sig=0
        for i in range(height):
            for j in range(width):
                for c in range (canal):
                    u=u+input[i,j,c]/N
        for k in range(height):
            for l in range(width):
                for c in range (canal):
                    sig=sig+(input[k,l,c]-u)**2

        sig=math.sqrt(sig/N)
        div = max(sig,1/(math.sqrt(N)))

        for m in range(height):
            for n in range(width):
                for c in range (canal):
                    self.output[m,n,c] = (input[m,n,c]-u)/div

class ReshapeToVector(layer):
    def build(self,input):
        shape=input.shape
        self.output=input.reshape(shape[0]*shape[1]*shape[2])

class Perceptron(layer):
    def __init__(self,parameters):
        self.weights=parameters[0]
        self.biases=parameters[1]


    def build(self,input):
        shape=self.weights.shape
        self.output=np.array([0 for i in range(shape[1])],dtype=np.float64)
        for outDim in range(shape[1]):
            val=0
            for inDim in range(shape[0]):
                val=val+input[inDim]*self.weights[inDim,outDim]
            self.output[outDim]=val+self.biases[outDim]

class CNN:
    def __init__(self,dicoCoeff):
        self.layers=[]
        self.dicoCoeff=dicoCoeff

    def addConvolLayer(self,dicoKey):
        newConv=ConvRELU((self.dicoCoeff[dicoKey+"/weights"],self.dicoCoeff[dicoKey+"/biases"]))
        self.layers.append(newConv)

    def addMaxPoolingLayer(self,size,stride):
        newMaxPooling=MaxPool(stride,size)
        self.layers.append(newMaxPooling)

    def addReshapeToVectorLayer(self):
        nwReshapeToVec=ReshapeToVector()
        self.layers.append(nwReshapeToVec)

    def addPerceptron(self,dicoKey):
        nwPerceptron=Perceptron((self.dicoCoeff[dicoKey+"/weights"],self.dicoCoeff[dicoKey+"/biases"]))
        self.layers.append(nwPerceptron)

    def addNormalizeLayer(self):
        nwNormalize=Normalize()
        self.layers.append(nwNormalize)

    def run(self,inputPic):
        buf=inputPic
        #write_pgm(inputPic,"input.ppm")
        if(len(inputPic)>0):
            for layer in self.layers:
                #print(type(layer))
                layer.build(buf)
                buf=layer.output
                #write_pgm(buf,str(type(layer).__name__)+".ppm")
        return buf

class ImageLoader:
    def __init__(self,filename,shift):
        self.file=filename
        self.shift=shift
        self.label=0

    def loadNewImage(self):
        sh=self.shift
        filename=self.file
        with open(filename, "rb") as f:
            f.read(sh*3073)
            byte=struct.unpack('B',f.read(1))
            self.label=byte
            mat=struct.unpack('3072B',f.read(3072))
        self.shift=self.shift+1
        return (self.label,np.array(mat,dtype=np.float64).reshape(3,32,32).transpose(1,2,0))

def centered_crop(mat,newWidth,newHeight):
    if((newWidth>mat.shape[1]) or newHeight>mat.shape[0]):
        return -1
    wmargin= (mat.shape[1]-newWidth)//2
    hmargin = (mat.shape[0]-newHeight)//2
    mat = np.delete(mat,[i for i in range(wmargin)],1)
    mat = np.delete(mat,[i for i in range(mat.shape[1]-wmargin,mat.shape[1],1)],1)
    mat = np.delete(mat,[i for i in range(hmargin)],0)
    mat = np.delete(mat,[i for i in range(mat.shape[0]-hmargin,mat.shape[0],1)],0)
    return(mat)

def load_labels(labelsFile):
    with open(labelsFile,"r") as f:
        dicolabel=[]
        line=f.readline()
        while len(line)!=0:
            dicolabel.append(str(line[:-1]))
            line=f.readline()
    return(dicolabel)


def write_pgm(matrix,file):
    if(len(matrix.shape)==3):
        img=open(file,"w")
        height,width,canal=matrix.shape
        img.write("P3"+"\n")
        size=str(width)+" "+str(height)+"\n"
        img.write(size)
        img.write(str(255)+"\n")
        for i in range(height):
            for j in range(width):
                for c in range(canal):
                    img.write(str(int(matrix[i,j,c]))+" ")
            img.write("\n")
        img.close()

if __name__=="__main__":
    import dicoCoeff

    d=dicoCoeff.DicoCoeff("CNN_coeff_3x3.txt")
    labels=load_labels("batches.meta.txt")
    cnn=CNN(d.dico)
    cnn.addNormalizeLayer()
    cnn.addConvolLayer("conv1")
    cnn.addMaxPoolingLayer([3,3],[2,2])
    cnn.addConvolLayer("conv2")
    cnn.addMaxPoolingLayer([3,3],[2,2])
    cnn.addConvolLayer("conv3")
    cnn.addMaxPoolingLayer([3,3],[2,2])
    cnn.addReshapeToVectorLayer()
    cnn.addPerceptron("local3")
    imglder=ImageLoader("data_batch_2.bin",0)
    success=0
    while imglder.shift<10000:
        (label,image)=imglder.loadNewImage()
        results=cnn.run(centered_crop(image,24,24))
        if (np.argmax(results)==label):
            success=success+1
            print("Success")
        else:
            print("Fail")
        print(results)
        print(labels)
        print("Image n°",imglder.shift,labels[int(label[0])])
        print("result = ",labels[np.argmax(results)])
        print("Synthese : taux de réussite=",success/(imglder.shift),"(",imglder.shift," images treated, ",success," success, "+str(imglder.shift-success+1)+" failures\n")
