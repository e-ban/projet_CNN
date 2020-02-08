#!/usr/bin/env python
import numpy as np
import struct
with open("input.ppm", "rb") as f:
    sh=0
    f.read(sh*3073)
    byte=struct.unpack('B',f.read(1))
    label=byte
    mat=struct.unpack('3072B',f.read(3072))
    print (label,np.array(mat,dtype=np.float64).reshape(3,32,32).transpose(1,2,0))
with open("image1.coe","wt") as fo:
    fo.write("memory_initialization_radix=10;")
    fo.write("memory_initialization_vector=")
    fo.write(",\n".join(str(val) for val in mat) + ";")
