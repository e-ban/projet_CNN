#!/usr/bin/env python
import random as rd
import numpy as np
import math
import struct
import pickle as pckl
class kernel :
    def __init__(self,h,w,c,l):
        self.k =[]
        self.height =h
        self.width = w
        self.canal = c
        self.color = l


    def generate_Random(self):
        line=[]
        pixel=[]
        layer=[]
        temp=[]
        for c in range (self.canal):
            for i in range(self.height):
                for j in range(self.width):
                    pixel =[]
                    for l in range(self.color):
                        pixel.append(rd.random())
                    line.append(pixel)
                layer.append(line)
                line=[]
            temp.append(layer)
            layer=[]
        temp = np.array()
        self.k = temp
        return 0

    def print_ker(self):
        for line in self.k:
            print(line)
            print("\n")


class Image :
    def __init__(self,coeffFile):
        self.height = 0
        self.width = 0
        self.canal = 0
        self.format=""
        self.lumMax=0
        self.label=""
        self.coeffFile=coeffFile

    def cleanUp(self):
        self.height=0
        self.width=0
        self.canal = 0
        self.format=""
        self.label=""

    def copy(self,image):
        self.height = image.height
        self.width = image.width
        self.canal = image.canal
        self.format = image.format
        self.lumMax = image.lumMax
        self.matrixPix = image.matrixPix
        self.label = image.label

    def load_pgm(self,FileName,format):
        self.cleanUp()  #reset all fields to initial values
        img=open(FileName)
        self.format=img.readline()

        if format=="P3":

            self.canal = 3
        else :
            self.canal = 1

        line=img.readline()

        while line[0] == '#' : line=img.readline()

        (self.width,self.height) = [int(i) for i in line.split()]
        self.lumMax=img.readline()
        mat = [[] for c in range(self.canal)]
        values = img.readlines()
        count=1
        for i in range(len(values)):
            for c in values[i].split():
                if(count==self.canal):
                    count=1
                else :
                    count=count+1
                mat[count-1].append(int(c))
        for col in range(self.canal):
            mat[col]=np.array(mat[col]).reshape(self.height,self.width)
        self.matrixPix=mat
        img.close()




    def generate_Random(self,width,height,canal,max,format):
        self.cleanUp()
        pixel=[]
        for c in range(canal*width*height):
            pixel.append(int(max*(rd.random())))
        self.matrixPix = np.array(pixel).reshape(canal,height,width)
        self.height=height
        self.width=width
        self.canal = canal
        self.lumMax=max
        self.format=format

    def centered_crop(self,newWidth,newHeight):
        if((newWidth>self.width) or (newHeight>self.height)):
            return -1

        wmargin= (self.width-newWidth)//2
        hmargin = (self.height-newHeight)//2
        self.matrixPix = np.delete(self.matrixPix,[i for i in range(wmargin)],2)
        self.matrixPix = np.delete(self.matrixPix,[i for i in range(self.width-wmargin,self.width,1)],2)
        self.matrixPix = np.delete(self.matrixPix,[i for i in range(hmargin)],1)
        self.matrixPix = np.delete(self.matrixPix,[i for i in range(self.height-hmargin,self.height,1)],1)
        self.height=newHeight
        self.width=newWidth
        return 0

    def normalize(self):
        self.matrixPix=self.matrixPix.astype(np.float64)

        for c in range (self.canal):
            N=self.width * self.height
            u=0
            sig=0
            for i in range(self.height):
                for j in range(self.width):
                    u=u+self.matrixPix[c,i,j]
            u=u/N
            for k in range(self.height):
                for l in range(self.width):
                    sig=sig+(self.matrixPix[c,k,l]-u)**2
            sig=math.sqrt(sig/N)
            div = max(sig,1/(math.sqrt(N)))

            for m in range(self.height):
                for n in range(self.width):
                    self.matrixPix[c,m,n] = (self.matrixPix[c,m,n]-u)/div

        return 0

    def convolutionReLU(self,kernel):
        matS = [[[0 for canal in range (kernel.canal)] for col in range(self.width)] for p in range(self.height)]
        for i in range(self.height):
                    for j in range(self.width):
                        for c in range(kernel.canal):
                            s = 0
                            for m in range(kernel.height):
                                for n in range(kernel.width):
                                    for l in range(self.canal):
                                        if (i+m < self.height and j+n < self.width):
                                            s = s + self.matrixPix[i+m][j+n][l]*kernel.k[c][m][n][l]
                            if (s<0):
                                s=0
                            matS[i][j][c] = s
        self.matrixPix = matS
        self.canal = kernel.canal
        return 0

    def maxPool(self,stride):
        matS = [[[0 for canal in range (self.canal)] for col in range(self.width//stride)] for line in range(self.height//stride)]
        for i in range(0,self.height,stride):
                    for j in range(0,self.width,stride):
                        for c in range(self.canal):
                            maxi=0
                            for m in range(stride):
                                for n in range(stride):
                                    if(maxi < self.matrixPix[i+m][j+n][c]):
                                        maxi = self.matrixPix[i+m][j+n][c]
                            matS[i//stride][j//stride][c] = maxi
        self.matrixPix = matS
        self.height = self.height//stride
        self.width = self.width//stride
        return 0


    def write_pgm(self,file):
        img=open(file,"w")
        img.write(self.format+"\n")
        size=str(self.width)+" "+str(self.height)+"\n"
        img.write(size)
        img.write(str(self.lumMax)+"\n")
        for i in range(self.height):
            for j in range(self.width):
                for c in range(3):
                    img.write(str(self.matrixPix[c][i][j])+" ")
            img.write("\n")
        img.close()
        return 0;

    def genZero(self,width,height,canal,max,format):
        self.cleanUp()
        pixel=[]
        for c in range(canal*width*height):
            pixel.append(0)
        self.matrixPix = np.array(pixel).reshape(canal,height,width)
        self.height=height
        self.width=width
        self.canal = canal
        self.lumMax=max
        self.format=format

    def reshapeToVector(self):
        self.matrixPix =self.matrixPix.reshape(self.height*self.width*self.canal)
        self.height=self.height*self.width*self.canal
        self.width=0
        self.canal=0

    def softMax(self):
        sexp=0
        for i in range(self.height):
            exp=math.exp(self.matrixPix[i])
            sexp = exp + sexp
            self.matrixPix[i] = exp
        for i in range(self.height):
            self.matrixPix[i] = self.matrixPix[i]/sexp
        return 0

    def multiplyMat(self,mat):
        A=np.array(self.matrix)*mat
        return A

    def print_matrixPix(self):
        A=self.matrixPix
        print(A.dtype)
        print(A.size)
        print(A)


    def load_bin(self,FileName):
        self.cleanUp()  #reset all fields to initial values
        mat=[[],[],[]]
        with open(FileName, "rb") as f:
            byte=struct.unpack('B',f.read(1))
            self.label=byte
            for c in range(3):
                byte=struct.unpack('1024B',f.read(1024))
                mat[c].append(byte)
        for n in range(3):
            mat[n]=np.array(mat[n]).reshape(32,32)
        self.matrixPix=mat
        self.height=32
        self.width=32
        self.canal=3


img=Image("CNN_coeff_3x3.txt")
#img.load_pgm("grosTest.pgm","P3")
#img.generate_Random(16,16,3,255,"P3")
img.load_bin("data_batch_1.bin")
#print(img.matrixPix)
# img.convertNumpy()
img.format="P3"
img.lumMax=255
img.write_pgm("test_bin")
print(img.label)
img.centered_crop(24,24)
print("\nCentered crop\n")
img.print_matrixPix()
img.write_pgm("TestCropped.pgm")
img.normalize()
print("\nNormalized\n")
img.print_matrixPix()
img.write_pgm("TestNormalized.pgm")
# ker=kernel(3,3,16,3)
# ker.generate_Random()
# #ker.print_ker()
# img.convolutionReLU(ker)
# #img.write_pgm("convol.pgm")
# img.maxPool(3)
# img.reshapeToVector()
# img.softMax()
# print(img.matrixPix)
