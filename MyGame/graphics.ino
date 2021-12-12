//------------------------------------- Graphics --------------------------------//

//---------------- Includes --------------------------//
#include "globals.h"

//---------------- Functions --------------------------//
void cleanTile1x1(uint8_t x,uint8_t y)
{
  uint8_t tile[]={0,0,0,0,0,0,0,0};
  u8x8.drawTile(x,y, 1, tile);
}

void cleanTile2x2(uint8_t x,uint8_t y)
{
  uint8_t tile[]={0,0,0,0,0,0,0,0};
  u8x8.drawTile(x,y, 1, tile);
  u8x8.drawTile(x,y+1, 1, tile);
  u8x8.drawTile(x+1,y, 1, tile);
  u8x8.drawTile(x+1,y+1, 1, tile);
}

void drawTile1x1(uint8_t x,uint8_t y,uint8_t *ptile)
{
  u8x8.drawTile(x,y, 1, ptile);
}

void drawTile1x2(uint8_t x,uint8_t y,uint8_t *ptile)
{
  uint8_t tile[16];
  for(int i=0;i<8 ;i++)
  {
    tile[2*i]=ptile[i];
    tile[2*i+1]=ptile[i];
  }
  u8x8.drawTile(x,y, 2, tile);
}

void drawTile2x1(uint8_t x,uint8_t y,uint8_t *ptile)
{
  uint8_t tile_up[8];
  uint8_t tile_down[8];
  for(int i=0;i<8;i++)
  {
    tile_up[i]=((ptile[i]&0x08)<<4)+((ptile[i]&0x08)<<3)+((ptile[i]&0x04)<<3)+((ptile[i]&0x04)<<2)+((ptile[i]&0x02)<<2)+((ptile[i]&0x02)<<1)+((ptile[i]&0x01)<<1)+(ptile[i]&0x01);
    tile_down[i]=(ptile[i]&0x80)+((ptile[i]&0x80)>>1)+((ptile[i]&0x40)>>1)+((ptile[i]&0x40)>>2)+((ptile[i]&0x20)>>2)+((ptile[i]&0x20)>>3)+((ptile[i]&0x10)>>3)+((ptile[i]&0x10)>>4);
  }
  u8x8.drawTile(x,y, 1, tile_up);
  u8x8.drawTile(x,y+1, 1, tile_down);
}

void drawTile2x2(uint8_t x,uint8_t y,uint8_t *ptile)
{
  uint8_t tile_up[8];
  uint8_t tile_down[8];
  uint8_t tile_up_out[16];
  uint8_t tile_down_out[16];
  
  for(int i=0;i<8;i++)
  {
    tile_up[i]=((ptile[i]&0x08)<<4)+((ptile[i]&0x08)<<3)+((ptile[i]&0x04)<<3)+((ptile[i]&0x04)<<2)+((ptile[i]&0x02)<<2)+((ptile[i]&0x02)<<1)+((ptile[i]&0x01)<<1)+(ptile[i]&0x01);
    tile_down[i]=(ptile[i]&0x80)+((ptile[i]&0x80)>>1)+((ptile[i]&0x40)>>1)+((ptile[i]&0x40)>>2)+((ptile[i]&0x20)>>2)+((ptile[i]&0x20)>>3)+((ptile[i]&0x10)>>3)+((ptile[i]&0x10)>>4);
  }

  for(int i=0;i<8 ;i++)
  {
    tile_up_out[2*i]=tile_up[i];
    tile_up_out[2*i+1]=tile_up[i];
    tile_down_out[2*i]=tile_down[i];
    tile_down_out[2*i+1]=tile_down[i];
  }
  u8x8.drawTile(x,y, 2, tile_up_out);
  u8x8.drawTile(x,y+1, 2, tile_down_out);
}
