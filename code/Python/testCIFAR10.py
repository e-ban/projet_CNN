#!/usr/bin/env python
from CNN_upgrade import *
from ioPGM import *

if __name__=="__main__":
    cnn=cifar10()
    labels=load_labels("batches.meta.txt")
    imglder=ImageLoader("data_batch_1.bin",0)
    success=0
    while imglder.shift<100:
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
        print("Synthese : taux de réussite=",success/(imglder.shift),"(",imglder.shift," images treated, ",success," success, "+str(imglder.shift-success)+" failures\n")
