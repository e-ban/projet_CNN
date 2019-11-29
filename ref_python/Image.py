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
        self.depth = l


    def generate_Random(self):
        line=[]
        pixel=[]
        layer=[]
        temp=[]
        for c in range (self.canal):
            for i in range(self.height):
                for j in range(self.width):
                    pixel =[]
                    for l in range(self.depth):
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
    def __init__(self):
        self.matrixPix=[]
        self.height = 0
        self.width = 0
        self.depth = 0
        self.format=""
        self.lumMax=0
        self.label=""

    def cleanUp(self):
        self.matrixPix=[]
        self.height=0
        self.width=0
        self.depth = 0
        self.format=""
        self.label=""

    def copy(self,image):
        self.height = image.height
        self.width = image.width
        self.depth = image.depth
        self.format = image.format
        self.lumMax = image.lumMax
        self.matrixPix = copy.deepcopy(image.matrixPix)
        self.label = image.label

    def load_pgm(self,FileName,format):
        self.cleanUp()  #reset all fields to initial values
        img=open(FileName)
        self.format=img.readline()

        if format=="P3":

            self.color = 3
        else :
            self.color = 1

        line=img.readline()

        while line[0] == '#' : line=img.readline()

        (self.width,self.height) = [int(i) for i in line.split()]
        self.lumMax=img.readline()
        mat = [[] for c in range(self.color)]
        values = img.readlines()
        count=1
        for i in range(len(values)):
            for c in values[i].split():
                if(count==self.color):
                    count=1
                else :
                    count=count+1
                mat[count-1].append(int(c))
        for col in range(self.color):
            mat[col]=np.array(mat[col]).reshape(self.height,self.width)
        self.matrixPix=mat
        img.close()




    def generate_Random(self,width,height,color,max,format):
        self.cleanUp()
        pixel=[]
        for c in range(color*width*height):
            pixel.append(int(max*(rd.random())))
        self.matrixPix = np.array(pixel).reshape(color,height,width)
        self.height=height
        self.width=width
        self.color = color
        self.lumMax=max
        self.format=format

    def centered_crop(self,newWidth,newHeight):
        if((newWidth>self.width) or (newHeight>self.height)):
            return -1

        xmargin= (self.width-newWidth)//2
        ymargin = (self.height-newHeight)//2


        #crop the up & bottom lines
        for i in range(ymargin):
            self.matrixPix.pop(0)
            self.matrixPix.pop(len(self.matrixPix)-1)

        for i in range(0,newHeight,1):
            for j in range(xmargin):
                self.matrixPix[i].pop(0)
                self.matrixPix[i].pop(len(self.matrixPix[i])-1)

        self.height=newHeight
        self.width=newWidth
        return 0

    def normalize(self):
        for c in range (self.depth):
            N=self.width * self.height
            u=0
            sig=0
            for i in range(self.height):
                for j in range(self.width):
                    u=u+self.matrixPix[i][j][c]
            u=u/N
            for i in range(self.height):
                for j in range(self.width):
                    sig=sig+(self.matrixPix[i][j][c]-u)**2
            sig=math.sqrt(sig/N)
            for i in range(self.height):
                for j in range(self.width):
                    self.matrixPix[i][j][c] = (self.matrixPix[i][j][c]-u)/max(sig,1/(math.sqrt(N)))
        return 0

    def convolutionReLU(self,kernel):
        matS = [[[0 for canal in range (kernel.canal)] for col in range(self.width)] for p in range(self.height)]
        for i in range(self.height):
                    for j in range(self.width):
                        for c in range(kernel.canal):
                            s = 0
                            for m in range(kernel.height):
                                for n in range(kernel.width):
                                    for l in range(self.depth):
                                        if (i+m < self.height and j+n < self.width):
                                            s = s + self.matrixPix[i+m][j+n][l]*kernel.k[c][m][n][l]
                            if (s<0):
                                s=0
                            matS[i][j][c] = s
        self.matrixPix = matS
        self.depth = kernel.canal
        return 0

    def maxPool(self,stride):
        matS = [[[0 for canal in range (self.depth)] for col in range(self.width//stride)] for line in range(self.height//stride)]
        for i in range(0,self.height,stride):
                    for j in range(0,self.width,stride):
                        for c in range(self.depth):
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


    def genZero(self,width,height,color,max,format):
        self.cleanUp()
        pixel=[]
        for c in range(color*width*height):
            pixel.append(0)
        self.matrixPix = np.array(pixel).reshape(color,height,width)
        self.height=height
        self.width=width
        self.color = color
        self.lumMax=max
        self.format=format

    def reshapeToVector(self):
        Vector = []
        for c in range(self.color):
                for i in range(self.height):
                    for j in range(self.width):
                        Vector.append(self.matrixPix[c][i][j])
        self.matrixPix = Vector
        self.height=self.height*self.width*self.color
        self.width=0
        self.color=0

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
        self.color=3


img=Image()
#img.load_pgm("grosTest.pgm","P3")
#img.generate_Random(16,16,3,255,"P3")
img.load_bin("data_batch_1.bin")
#print(img.matrixPix)
# img.convertNumpy()
#img.format="P3"
#img.lumMax=255
#img.write_pgm("test_bin")
#print(img.label)
# img.centered_crop(12,12)
# img.write_pgm("grosTestCropped.pgm")
# img.normalize()
# ker=kernel(3,3,16,3)
# ker.generate_Random()
# #ker.print_ker()
# img.convolutionReLU(ker)
# #img.write_pgm("convol.pgm")
# img.genZero(16,16,3,255,"P3")
# img.maxPool(3)
# img.reshapeToVector()
# img.softMax()
print(img.matrixPix)
