import struct
import numpy as np

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
        img=open("generated_pgm/"+file+".pgm","w")
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

def write_Npgm(matrix,file):
    if(len(matrix.shape)==3):
        height,width,canal=matrix.shape
        for c in range(canal):
            img=open("generated_pgm/"+file+"_"+str(c)+".pgm","w")
            img.write("P2"+"\n")
            size=str(width)+" "+str(height)+"\n"
            img.write(size)
            img.write(str(255)+"\n")
            for i in range(height):
                for j in range(width):
                        img.write(str(int(matrix[i,j,c]))+" ")
                img.write("\n")
            img.close()
