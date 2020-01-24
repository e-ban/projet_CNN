#include "display.h"
#include "masks.h"

void display(char label,CNN_IMAGE_TYPE imageIn[CNN_IMAGE_IN_SIZE],CNN_IMAGE_TYPE imageOut[CNN_VGA_SIZE])
{
  int maskTop,maskBottom,maskLeft,maskRight;
  CNN_MASK_TYPE* mask;
  switch(label)
  {
    case 0: //airplane
      maskTop = CNN_MASK_airplane_TOP;
      maskBottom = CNN_MASK_airplane_BOTTOM;
      maskLeft = CNN_MASK_airplane_LEFT;
      maskRight = CNN_MASK_airplane_RIGHT;
      mask=maskArray_airplane;
      break;
    case 1: //automobile
      maskTop = CNN_MASK_automobile_TOP;
      maskBottom = CNN_MASK_automobile_BOTTOM;
      maskLeft = CNN_MASK_automobile_LEFT;
      maskRight = CNN_MASK_automobile_RIGHT;
      mask=maskArray_automobile;
      break;
    case 2: //bird
      maskTop = CNN_MASK_bird_TOP;
      maskBottom = CNN_MASK_bird_BOTTOM;
      maskLeft = CNN_MASK_bird_LEFT;
      maskRight = CNN_MASK_bird_RIGHT;
      mask=maskArray_bird;
      break;
    case 3: //cat
      maskTop = CNN_MASK_cat_TOP;
      maskBottom = CNN_MASK_cat_BOTTOM;
      maskLeft = CNN_MASK_cat_LEFT;
      maskRight = CNN_MASK_cat_RIGHT;
      mask=maskArray_cat;
      break;
    case 4: //deer
      maskTop = CNN_MASK_deer_TOP;
      maskBottom = CNN_MASK_deer_BOTTOM;
      maskLeft = CNN_MASK_deer_LEFT;
      maskRight = CNN_MASK_deer_RIGHT;
      mask=maskArray_deer;
      break;
    case 5: //dog
      maskTop = CNN_MASK_dog_TOP;
      maskBottom = CNN_MASK_dog_BOTTOM;
      maskLeft = CNN_MASK_dog_LEFT;
      maskRight = CNN_MASK_dog_RIGHT;
      mask=maskArray_dog;
      break;
    case 6: //frog
      maskTop = CNN_MASK_frog_TOP;
      maskBottom = CNN_MASK_frog_BOTTOM;
      maskLeft = CNN_MASK_frog_LEFT;
      maskRight = CNN_MASK_frog_RIGHT;
      mask=maskArray_frog;
      break;
    case 7: //horse
      maskTop = CNN_MASK_horse_TOP;
      maskBottom = CNN_MASK_horse_BOTTOM;
      maskLeft = CNN_MASK_horse_LEFT;
      maskRight = CNN_MASK_horse_RIGHT;
      mask=maskArray_horse;
      break;
    case 8: //ship
      maskTop = CNN_MASK_ship_TOP;
      maskBottom = CNN_MASK_ship_BOTTOM;
      maskLeft = CNN_MASK_ship_LEFT;
      maskRight = CNN_MASK_ship_RIGHT;
      mask=maskArray_ship;
      break;
    case 9: //truck
      maskTop = CNN_MASK_truck_TOP;
      maskBottom = CNN_MASK_truck_BOTTOM;
      maskLeft = CNN_MASK_truck_LEFT;
      maskRight = CNN_MASK_truck_RIGHT;
      mask=maskArray_truck;
      break;
    default:
      maskTop = 0;
      maskBottom = 0;
      maskLeft = 0;
      maskRight = 0;
      break;
  }

  int ii=0,ji=0;
  int canal=0;
  int widthMask=maskRight-maskLeft;

  for (int io=0;io<CNN_VGA_H;io++)
  {
    ji=0;
    for(int jo=0; jo<CNN_VGA_W;jo++)
    {
      if(io>CADRE_VGA_TOP && io<CADRE_VGA_BOTTOM && jo>CADRE_VGA_LEFT && jo<CADRE_VGA_RIGHT)
      {
        imageOut[io*CNN_VGA_W+jo] = imageIn[ii*CNN_IMAGE_IN_W*CNN_IMAGE_IN_C+ji*CNN_IMAGE_IN_C+canal];
      }
      else imageOut[io*CNN_VGA_W+jo]=0;
      ji++;
      //overlay
      if(io>maskTop && io<maskBottom && jo>maskLeft && jo<maskRight)
      {
        imageOut[io*CNN_VGA_W+jo]= imageOut[io*CNN_VGA_W+jo] + 255*mask[(io-maskTop)*widthMask+jo-maskLeft];
      }
    }
    ii++;
  }
}
