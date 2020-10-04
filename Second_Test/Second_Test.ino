//-------------------------------------------- ARDUGAME ----------------------------------------------//

//-------------------- Includes -------------------------------//
//Library includes
#include <Arduino.h>
#include <U8x8lib.h>

//-------------------- Defines -------------------------------//
// Define screen type
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
// Define buttons
#define LEFT_PIN 2
#define UP_PIN 4
#define RIGHT_PIN 5
#define DOWN_PIN 6
#define B_PIN 7
#define A_PIN 8
// Define buzzer
#define BUZZER_PIN 3

//-------------------- Global Variables --------------------//
uint8_t x_pos=0;
uint8_t y_pos=0;
uint8_t tile[8]={0,B0010000,B11001000,B00111111,B00111111,B11001010,B0010000,0};

void setup(void)
{
  u8x8.begin();
  u8x8.setPowerSave(0);
  pinMode(LEFT_PIN,INPUT_PULLUP);
  pinMode(UP_PIN,INPUT_PULLUP);
  pinMode(RIGHT_PIN,INPUT_PULLUP);
  pinMode(DOWN_PIN,INPUT_PULLUP);
  pinMode(B_PIN,INPUT_PULLUP);
  pinMode(A_PIN,INPUT_PULLUP);
}

void loop(void)
{
  if(!digitalRead(RIGHT_PIN))
  {
    if(x_pos<14){x_pos++;}
    tone(3, 1000, 50);
    u8x8.clear();
  }
  else if(!digitalRead(LEFT_PIN))
  {
    if(x_pos>0){x_pos--;}
   tone(3, 1000, 50);
    u8x8.clear();
  }
  else if(!digitalRead(DOWN_PIN))
  {
    if(y_pos<7){y_pos++;}
    tone(3, 1000, 50);
    u8x8.clear();
  }
  else if(!digitalRead(UP_PIN))
  {
    if(y_pos>0){y_pos--;}
    tone(3, 1000, 50);
    u8x8.clear();
  }
  else if(!digitalRead(A_PIN))
  {
    y_pos=3;
    tone(3, 1000, 50);
    u8x8.clear();
  }
   else if(!digitalRead(B_PIN))
  {
    x_pos=7;
    tone(3, 1000, 50);
    u8x8.clear();
  }
  
  u8x8.drawTile(x_pos,y_pos, 1, tile);
  delay(10);
}
