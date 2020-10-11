//-------------------------------------------- HOT LEAD ----------------------------------------------//

//-------------------- Includes -------------------------------//
//Library includes
#include <Arduino.h>
#include <U8x8lib.h>
//Game includes
#include "classes_header.h"
#include "definitions_header.h"
#include "tiles_header.h"
#include "functions_header.h"

//-------------------- Global Variables --------------------//
// Creating screen object type
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
// Creating the buttons object type
Buttons button;
// Tile
uint8_t tile[8]=MAIN_CHAR;
// Position
uint8_t x_pos,y_pos;

void setup(void)
{
  Serial.begin(9600); //172 milli to update screen (5fps)
  u8x8.begin();
  u8x8.setPowerSave(0);
  button.begin(LEFT_PIN,UP_PIN,RIGHT_PIN,DOWN_PIN,B_PIN,A_PIN);
}

void loop(void)
{
  static int BTStateOld;
  int BTState = button.check();
  if(BTState!=BTStateOld)
  {
    if(BTState==RIGHT)
    {
      if(x_pos<14){x_pos++;}
      tone(3, 1000, 50);
      u8x8.clear();
    }
    else if(BTState==LEFT)
    {
      if(x_pos>0){x_pos--;}
     tone(3, 1000, 50);
      u8x8.clear();
    }
    else if(BTState==DOWN)
    {
      if(y_pos<7){y_pos++;}
      tone(3, 1000, 50);
      u8x8.clear();
    }
    else if(BTState==UP)
    {
      if(y_pos>0){y_pos--;}
      tone(3, 1000, 50);
      u8x8.clear();
    }
    else if(BTState==A)
    {
      y_pos=3;
      tone(3, 1000, 50);
      u8x8.clear();
    }
     else if(BTState==B)
    {
      x_pos=7;
      tone(3, 1000, 50);
      u8x8.clear();
    }
    BTStateOld=BTState;
  }
  //u8x8.drawTile(x_pos,y_pos, 1, tile);
  
  static int counter_x,counter_y;
  static unsigned long init_time;
  static unsigned long final_time;
  u8x8.drawTile(counter_x,counter_y, 1, tile);
  if(counter_x==0 && counter_y==0) {init_time=millis();}
  if(counter_x<16) {counter_x++;}
  else
  {
    counter_x=0; 
    if(counter_y<8){counter_y++;}
    else{final_time=millis()-init_time;  Serial.println(final_time); delay(1000);counter_y=0; u8x8.clearDisplay(); delay(1000);}
  }
}
