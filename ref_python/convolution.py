import numpy as np


class Layer:
    def __init__(self,image_input,kernel,image_output):
        self.input = image_input
        self.kernel = kernel
        self.output = image_output
        
    def compute(self):
        pass

class Convolution(Layer):
    
    def compute(self):
        if(isinstance(self.input,Image)):
            for i in range(self.output.height):
                for j in range(self.output.width):
                    for c in range(self.output.depth):
                        for m in range(self.kernel.height):
                            for n in range(len(self.kernel.width):
                                for l in range(self.input.depth):
                                    self.output.matrixPix[i][j][c] = self.input.matrixPix[i+m][j+n][l]*self.kernel[l][m][n][c]
        
    


def __main__():
    
    input = Image()
    input.generate_Random(32,32,3,255,"P3")
    output = Image()
    output.genZero(32,32,32)
    
    kernel = Kernel()
    kernel.generate_Random(3,3,)
    cvLayer = Convolution(input,kernel,output)