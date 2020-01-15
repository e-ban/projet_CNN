#include "types.h"
#include "array"

int loadFilePGM(din_type image[IMGPROC_IMAGE_IN_SIZE]);
int savePicture(std::string fileName,din_type image[IMGPROC_IMAGE_IN_SIZE]);
void printMatrix(din_type image[IMGPROC_IMAGE_IN_SIZE]);
