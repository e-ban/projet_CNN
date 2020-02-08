#!/usr/bin/env python
import numpy as np

def loadMaskPGM(masktype):
    with open("masks/mask_"+masktype+".pgm","r") as img:
        format=img.readline()
        line=img.readline()
        while line[0] == '#' :
            line=img.readline()
        (width,height)= [int(i) for i in line.split()]
        lumMax=img.readline()
        mat = []
        values = img.readlines()
        for i in range(len(values)):
            mat.append([int(c) for c in values[i].split()])
        A=np.array(mat)
        return A.reshape(height,width)

def deleteWhiteZone(matrix):
    left=matrix.shape[1]-1
    right=0
    bottom=0
    top=matrix.shape[0]-1
    for line in range (matrix.shape[0]):
        for col in range (matrix.shape[1]):
            if(matrix[line,col]!=0):
                if(line<top):
                    top=line
                if(line>bottom):
                    bottom=line
                if(col<left):
                    left=col
                if(col>right):
                    right=col
                matrix[line,col]=1
    fullHeight = matrix.shape[0]
    fullWidth = matrix.shape[1]
    matrix=np.delete(matrix,[i for i in range(top)],0)
    matrix=np.delete(matrix,[i for i in range(left)],1)
    matrix=np.delete(matrix,[i for i in range(bottom-top,fullHeight-top)],0)
    matrix=np.delete(matrix,[i for i in range(right-left,fullWidth-left)],1)
    return(matrix,top,bottom,left,right)

def writePGM(label,mat):
    with open(label+".pgm","w") as f:
        f.write("P2\n")
        f.write(str(mat.shape[1])+" "+str(mat.shape[0])+"\n")
        f.write("255\n")
        for line in range(mat.shape[0]):
            for col in range(mat.shape[1]):
                f.write(str(mat[line,col])+" ")
            f.write("\n")



def writeMaskFile(filename):
    with open(filename,"w") as f:
        macroFile = open("include/macroMask.h","w")
        f.write("//Masks for CNN overlay\n")
        f.write("#include \"types.h\"\n")
        labels = ("airplane","automobile","bird","cat","deer","dog","frog","horse","ship","truck")
        for lab in labels:
            mat = loadMaskPGM(lab)
            (mask,top,bottom,left,right)=deleteWhiteZone(mat)
            macroFile.write("\n\n//Macro for label "+lab+"\n")
            macroFile.write("#define CNN_MASK_"+lab+"_TOP "+str(top)+"\n")
            macroFile.write("#define CNN_MASK_"+lab+"_BOTTOM "+str(bottom)+"\n")
            macroFile.write("#define CNN_MASK_"+lab+"_LEFT "+str(left)+"\n")
            macroFile.write("#define CNN_MASK_"+lab+"_RIGHT "+str(right)+"\n")
            macroFile.write("#define CNN_MASK_"+lab+"_SIZE "+str(mask.shape[0]*mask.shape[1])+"\n")
            f.write("static CNN_MASK_TYPE maskArray_"+lab+"[ CNN_MASK_"+lab+"_SIZE ] = { ")
            for line in range(mask.shape[0]):
                f.write("\n")
                for col in range(mask.shape[1]):
                    f.write(str(mask[line,col]))
                    if(line!=mask.shape[0] and col!=mask.shape[1]):
                        f.write(",")
            f.write("};\n")
        macroFile.close()


writeMaskFile("include/masks.h")
