//-------------------------------------------- Functions Declaration ----------------------------------------------//

//---------------- Includes --------------------------//
#include "definitions_header.h"

//---------------- Functions --------------------------//
void drawTile1x1(uint8_t x,uint8_t y,uint8_t *ptile)
{
  u8x8.drawTile(x,y, 1, ptile);
}

void drawTile2x2(uint8_t x,uint8_t y,uint8_t *ptile)
{
  uint8_t top_tile[16];
  uint8_t bottom_tile[16];
  for(int i=0;i<8;i++)
  {
    top_tile[i]=0;
  }
  u8x8.drawTile(x,y, 1, ptile);
}
