#!/usr/bin/env python
import random as rd
import numpy as np
import math
import struct



class DicoCoeff:

    def __init__(self,filename):
        self.load_dicoCoeff(filename)

    def initFSM(self):

        if(len(self.buffer)!=0):
            self.dico[self.name]=np.array(list(self.buffer[0]),dtype=np.float64)
            self.buffer=[]
        if (self.currentElement()=="tensor_name:"):
            self.state = 1
        elif (self.currentElement()=='\n'):
            self.state = 0
        elif (self.index == len(self.file)-1):
            self.state = 0
        else :
            print("\nError:init\n")
            self.state = -1
        return([])
    def acquireDicoElementName(self):
        if(len(self.currentElement())!=0):
            self.name=self.currentElement()
            self.state=2
            self.nbDim=0
        else:
            self.state=1
        return(self.buffer)

    def getValues(self):
        buffer=[]
        self.state = 0
        while(self.index<len(self.file)):
            element = self.currentElement()
            if (len(self.currentElement())==0):
                self.incrIndex()
            elif (element=="tensor_name:"):

                self.index=self.index-1
                return(buffer)
            elif (element[0]=='['):
                self.nbDim = self.nbDim +1
                self.file[self.index]=element[1:]#enlève le premier crochet
                buffer.append(self.getValues())

            elif (element[-1]==']'):
                if(len(element[:element.find(']')])!=0):
                    buffer.append(float(element[:element.find(']')]))#on stocke la valeur numérique si elle existe
                self.file[self.index]=element[element.find(']'):-1] #on enlève le dernier crochet
                return(buffer)

            else :
                buffer.append(float(element))
                self.incrIndex()

        if(self.index != len(self.file)):
            self.state=-1
            print("\nError:getValues\n")
            return([])
        else :

            self.dico[self.name]=np.array(list(buffer[0]),dtype=np.float64)
            return(buffer)

    def currentElement(self):
        return(self.file[self.index])

    def incrIndex(self):
        self.index = self.index+1

    def errorFSM(self):
        print("error fsm\n")


    def load_dicoCoeff(self,coeffFile):
        self.dico = {}
        stateSwitch={
            -1:self.errorFSM,
            0:self.initFSM,
            1:self.acquireDicoElementName,
            2:self.getValues
        }
        self.buffer=[]
        self.file=[]
        self.index=0
        self.state=0
        countline=0
        with open(coeffFile,"r") as f:
            self.file = f.read().split()

            while self.index < len(self.file):
                if(len(self.currentElement())!=0):
                    func=stateSwitch.get(self.state,lambda:'Undefined state')
                    self.buffer=list(func())
                    self.incrIndex()
                if(self.state==-1):
                    self.index = len(self.file)
        return(self.dico)

if __name__== "__main__":
    dico=DicoCoeff("CNN_coeff_3x3.txt")
    dicoCoeff=dico.dico
    print("\n")
    print(dicoCoeff)
    print("\n")
    print(dicoCoeff.keys())
    mat=dicoCoeff["conv2/weights"]
    print(np.shape(mat))
