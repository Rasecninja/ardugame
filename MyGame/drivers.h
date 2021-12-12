//------------------------------------ Drivers for HMI --------------------------------//
#ifndef DRIVERS_H
#define DRIVERS_H

//-------------------- Includes -------------------------------//
//Library includes
#include <U8x8lib.h>

//-------------------- Defines -------------------------------//
// Define buttons
#define LEFT_PIN 2
#define UP_PIN 4
#define RIGHT_PIN 5
#define DOWN_PIN 6
#define B_PIN 7
#define A_PIN 8
#define SUPPORT_MULTI_KEY_PRESS 0
// Define buzzer
#define BUZZER_PIN 3

//---------------- Strucs and Enums --------------------------//
typedef enum 
{
  NONE=0,
  LEFT=0x01,
  UP=0x02,
  RIGHT=0x04,
  DOWN=0x08,
  B=0x10,
  A=0x20
}ButtonPressed;

//---------------- Button Class --------------------------//
class Buttons 
{
	private:
		uint8_t BTPressed=0;
		uint8_t BTMatrixOld=0; //00ABDRUPL
		uint8_t BTMatrixNew=0; //00ABDRUPL
		unsigned long LastDebounceTime = 0; 
		unsigned long DebounceDelay = 10; 
		uint8_t Left_Pin;
		uint8_t Up_Pin;
		uint8_t Right_Pin;
		uint8_t Down_Pin;
		uint8_t B_Pin;
		uint8_t A_Pin;
    // Get user current press key matrix
    uint8_t get_raw_press()
    {
      int BTRead=((!digitalRead(A_Pin))<<5)+((!digitalRead(B_Pin))<<4)+((!digitalRead(Down_Pin))<<3)+((!digitalRead(Right_Pin))<<2)+((!digitalRead(Up_Pin))<<1)+(!digitalRead(Left_Pin));
      if (BTRead != BTMatrixOld) 
      {
        LastDebounceTime = millis();
      }
         
      if ((millis() - LastDebounceTime) > DebounceDelay) 
      {
        BTMatrixOld=BTRead;
        return BTRead;
      }
    }
    // Checks for new status only and returns just one key value
    uint8_t get_filter_press()
    {
      int BTRead=((!digitalRead(A_Pin))<<5)+((!digitalRead(B_Pin))<<4)+((!digitalRead(Down_Pin))<<3)+((!digitalRead(Right_Pin))<<2)+((!digitalRead(Up_Pin))<<1)+(!digitalRead(Left_Pin));
      if (BTRead != BTMatrixOld) 
      {
          LastDebounceTime = millis();
      }
         
        if ((millis() - LastDebounceTime) > DebounceDelay) 
        {
        if (BTRead != BTMatrixNew) 
        {
          BTMatrixNew = BTRead;

          switch(BTMatrixNew)
          {
            case LEFT: 
              BTPressed=LEFT;
              break;
            case UP: 
              BTPressed=UP;
              break;
            case RIGHT: 
              BTPressed=RIGHT;
              break;
            case DOWN: 
              BTPressed=DOWN;
              break;
            case B: 
              BTPressed=B;
              break;
            case A: 
              BTPressed=A;
              break;
            default:
              BTPressed=NONE;
              break;
          }
        }
      }
      BTMatrixOld=BTRead;
      return BTPressed;
    }
	public:
    // Initialize Arduino GPIO
		void begin(uint8_t Left_Pin,uint8_t Up_Pin,uint8_t Right_Pin,uint8_t Down_Pin,uint8_t B_Pin,uint8_t A_Pin)
		{
			this->Left_Pin=Left_Pin;
			this->Up_Pin=Up_Pin;
			this->Right_Pin=Right_Pin;
			this->Down_Pin=Down_Pin;
			this->B_Pin=B_Pin;
			this->A_Pin=A_Pin;
			pinMode(Left_Pin,INPUT_PULLUP);
			pinMode(Up_Pin,INPUT_PULLUP);
			pinMode(Right_Pin,INPUT_PULLUP);
			pinMode(Down_Pin,INPUT_PULLUP);
			pinMode(B_Pin,INPUT_PULLUP);
			pinMode(A_Pin,INPUT_PULLUP);
		}

    uint8_t get_key()
    {
      if(SUPPORT_MULTI_KEY_PRESS) return get_raw_press();
      else return get_filter_press();
    }

};


//---------------- Screen Class --------------------------//
class Screens
{
  private:
    U8X8_SH1106_128X64_NONAME_HW_I2C u8x8;
  public:
    //Class constructor with object initalizer
    Screens() : u8x8(U8X8_PIN_NONE){}
    //Initialize the u8x8 lib
    void begin()
    {
      u8x8.begin();
      u8x8.setPowerSave(0);
    }

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
};

#endif
