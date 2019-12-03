#!/usr/bin/env python
import random as rd
import numpy as np
import math
import struct


class CNN :
    def __init__(self,coeffDico,dicoLabelFile):
        self.height = 0
        self.width = 0
        self.canal = 0
        self.format=""
        self.lumMax=0
        self.label=""
        self.matrixPix=[]
        self.coeffDico=coeffDico
        self.dicoLabel=self.load_labels(dicoLabelFile)

    def cleanUp(self):
        self.height=0
        self.width=0
        self.canal = 0
        self.format=""
        self.label=""
        self.matrixPix=[]


    def copy(self,image):
        self.height = image.height
        self.width = image.width
        self.canal = image.canal
        self.format = image.format
        self.lumMax = image.lumMax
        self.matrixPix = image.matrixPix
        self.label = image.label

    def load_labels(self,labelsFile):
        with open(labelsFile,"r") as f:
            dicolabel=[]
            line=f.readline()
            while len(line)!=0:
                dicolabel.append(line[:-1])
                line=f.readline()
        return(dicolabel)

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
        mat = []
        values = img.readlines()
        for i in range(len(values)):
            mat.append([int(c) for c in values[i].split()])
        A = np.array(mat)
        self.matrixPix=A.reshape(self.height,self.width,self.canal)
        img.close()



    def generate_Random(self,width,height,canal,max,format):
        self.cleanUp()
        pixel=[]
        for c in range(canal*width*height):
            pixel.append(int(max*(rd.random())))
        self.matrixPix = np.array(pixel).reshape(height,width,canal)
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
        self.matrixPix = np.delete(self.matrixPix,[i for i in range(wmargin)],1)
        self.matrixPix = np.delete(self.matrixPix,[i for i in range(self.width-wmargin,self.width,1)],1)
        self.matrixPix = np.delete(self.matrixPix,[i for i in range(hmargin)],0)
        self.matrixPix = np.delete(self.matrixPix,[i for i in range(self.height-hmargin,self.height,1)],0)
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
                    u=u+self.matrixPix[i,j,c]
            u=u/N
            for k in range(self.height):
                for l in range(self.width):
                    sig=sig+(self.matrixPix[k,l,c]-u)**2
            sig=math.sqrt(sig/N)
            div = max(sig,1/(math.sqrt(N)))

            for m in range(self.height):
                for n in range(self.width):
                    self.matrixPix[m,n,c] = (self.matrixPix[m,n,c]-u)/div

        return 0

    def convolutionReLU(self,coeffKey):
        kernel=self.coeffDico[coeffKey+"/weights"]
        biasesVect = self.coeffDico[coeffKey+"/biases"]
        matS = np.array([[[0 for canal in range (np.shape(kernel)[3])] for col in range(self.width)] for p in range(self.height)],dtype=np.float64)
        for i in range(self.height):
                    for j in range(self.width):
                        for c in range((np.shape(kernel)[3])):#depth of kernel
                            s = 0
                            h_ker=np.shape(kernel)[0]#height of kernel
                            w_ker=np.shape(kernel)[1]#width of kernel
                            for m in range(-(h_ker-1)//2,(h_ker-1)//2):
                                for n in range(-(w_ker-1)//2,(w_ker-1)//2):
                                    for l in range(self.canal): #colors
                                        if (i+m < self.height and j+n < self.width and i+m>=0 and j+n>=0):
                                            s = s + self.matrixPix[i+m,j+n,l]*kernel[m,n,l,c] + biasesVect[c]
                            if (s<0):
                                s=0
                            matS[i][j][c] = s
        self.matrixPix = matS
        self.canal = (np.shape(kernel)[3])
        return 0

    def maxPool(self,size,stride):
        k=1
        matS = [[[0 for canal in range (self.canal)] for col in range(self.width//stride[1])] for line in range(self.height//stride[1])]
        for i in range(stride[0]-size[0],self.height+size[0]-stride[0],k*stride[0]):
                    for j in range(stride[1]-size[1],self.width+size[1]-stride[1],stride[1]):
                        for c in range(self.canal):
                            maxi=0
                            for m in range(0,size[0]):
                                for n in range(0,size[1]):
                                    if(i+m<0 or j+n<0 or i+m>=self.height or j+n>=self.width):
                                        if maxi<0:
                                            maxi=0
                                    elif(maxi < self.matrixPix[i+m][j+n][c]):
                                        maxi = self.matrixPix[i+m][j+n][c]
                            matS[i//stride[0]][j//stride[1]][c] = maxi
                    if (i == self.height+size[0]-stride[0]-1):
                        k=-1*k
        self.matrixPix = np.array(matS,dtype=np.float64)
        self.height = self.height//stride[0]
        self.width = self.width//stride[1]
        return 0


    def write_pgm(self,file):
        img=open(file,"w")
        img.write(self.format+"\n")
        size=str(self.width)+" "+str(self.height)+"\n"
        img.write(size)
        img.write(str(self.lumMax)+"\n")
        for i in range(self.height):
            for j in range(self.width):
                for c in range(self.canal):
                    img.write(str(self.matrixPix[i,j,c])+" ")
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
        result=[]
        for i in range(self.height):
            exp=math.exp(self.matrixPix[i])
            sexp = exp + sexp
            result.append(exp)
        for i in range(self.height):
            result[i] = result[i]/sexp
        return result

    def multiplyMat(self,dicoKey):
        B=np.array([[self.coeffDico[dicoKey+"/weights"][i,j] for i in range(180)] for j in range(10)])
        C=np.array([self.coeffDico[dicoKey+"/biases"][i] for i in range(10)])
        A=np.matmul(B,self.matrixPix)+C
        self.height=A.shape[0]
        self.width=0
        self.canal=0
        self.matrixPix=A.reshape(self.height)

    def print_matrixPix(self):
        A=self.matrixPix
        print(A.dtype)
        print(A.shape)
        print(A)


    def load_bin(self,FileName,shift):
        self.cleanUp()  #reset all fields to initial values
        mat=[[],[],[]]
        with open(FileName, "rb") as f:
            f.read(shift*3073)
            byte=struct.unpack('B',f.read(1))
            self.label=byte
            for c in range(3):
                byte=struct.unpack('1024B',f.read(1024))
                mat[c].append(byte)
        for n in range(3):
            mat[n]=np.array(mat[n]).reshape(32,32)
        self.height=32
        self.width=32
        self.canal=3
        self.matrixPix = np.array([[[mat[c][i,j] for c in range(3)] for j in range(32) ] for i in range(32)],dtype=np.float64)




if __name__=="__main__":
    import dicoCoeff
    d = dicoCoeff.DicoCoeff("CNN_coeff_3x3.txt")
    cnn=CNN(d.dico,"batches.meta.txt")
    #cnn.generate_Random(32,32,3,255,"P3")
    success=0
    for shift in range(1):
        cnn.cleanUp()
        cnn.load_bin("data_batch_1.bin",4000)
        cnn.format="P3"
        cnn.lumMax=255
        #cnn.write_pgm("test_bin"+str(shift)+".pgm")
        #print("\nImage : ")
        #print(cnn.label)
        #print("\n")
        cnn.centered_crop(24,24)
        cnn.write_pgm("crop_"+str(shift)+".pgm")
        cnn.normalize()
        cnn.write_pgm("normal_"+str(shift)+".pgm")
        cnn.convolutionReLU("conv1")
        cnn.write_pgm("conv1_"+str(shift)+".pgm")
        cnn.maxPool([3,3],[2,2])
        cnn.write_pgm("max1_"+str(shift)+".pgm")
        cnn.convolutionReLU("conv2")
        cnn.write_pgm("conv2_"+str(shift)+".pgm")
        cnn.maxPool([3,3],[2,2])
        cnn.write_pgm("max2_"+str(shift)+".pgm")
        cnn.convolutionReLU("conv3")
        cnn.write_pgm("conv3_"+str(shift)+".pgm")
        cnn.maxPool([3,3],[2,2])
        cnn.write_pgm("max3_"+str(shift)+".pgm")
        cnn.reshapeToVector()
        cnn.multiplyMat("local3")
        cnn.print_matrixPix()
        Result=cnn.softMax()

        if(np.argmax(Result)==cnn.label):
            print("CNN : Success")
            print(cnn.dicoLabel[int(''.join(map(str,cnn.label))) ])
            print(cnn.dicoLabel)
            print(Result)
            success = success+1
        else :
            print("CNN : Fail")
            print(cnn.dicoLabel[int(''.join(map(str,cnn.label)))])
            print(cnn.dicoLabel)
            print(Result)
        print("Synthesis : "+str(shift+1)+" images treated, "+str(success)+" success, "+str(shift-success+1)+" failures\n")
