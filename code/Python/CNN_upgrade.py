import random as rd
import numpy as np
import math
import dicoCoeff
from ioPGM import *

class layer : #basic class for all CNN layers
    def __init__(self):
        self.output=[]

    def build(self,input):
        return (-1)


class ConvRELU(layer):#layer of convolution which proceeds to a ReLU activation
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
                    for kerH in range(-(kHeight//2),kHeight//2+1):
                        for kerW in range(-(kWidth//2),kWidth//2+1):
                            for inChannel in range(canal):
                                if (kerH+row < height and kerW+col < width and kerH+row>=0 and kerW+col>=0):
                                    s=s+input[row+kerH,col+kerW,inChannel]*ker[kerH+1,kerW+1,inChannel,outChannel]
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
        u=[0,0,0]
        sig=[0,0,0]
        sigmoy=0
        umoy=0
        self.output = np.array([0 for i in range(N*canal)],dtype=np.float64).reshape(input.shape)
        for i in range(height):
            for j in range(width):
                for c in range (canal):
                    u[c]=u[c]+input[i,j,c]/N
        umoy=(u[0]+u[1]+u[2])/3
        for k in range(height):
            for l in range(width):
                for c in range (canal):
                    sig[c]=sig[c]+(input[k,l,c]-umoy)**2
        for c in range(canal):
            sig[c]=math.sqrt(sig[c]/N)
            sigmoy=sigmoy+sig[c]

        sigmoy=sigmoy/3
        div = max(sigmoy,1/(math.sqrt(N)))

        for m in range(height):
            for n in range(width):
                for c in range (canal):
                    self.output[m,n,c] = (input[m,n,c]-umoy)/div
        #print(u,sig)

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
        if(len(inputPic)>0):
            for layer in self.layers:
                #print(type(layer).__name__)
                layer.build(buf)
                buf=layer.output
                #print(buf)
        return buf

def cifar10():
    import dicoCoeff
    d=dicoCoeff.DicoCoeff("CNN_coeff_3x3.txt")
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
    return(cnn)
