//-------------------------------------------- HOT LEAD ----------------------------------------------//

#include "globals.h"

//-------------------- Global Variables --------------------//
// Creating screen object type
Screens screen;
// Creating the buttons object type
Buttons button;
// Tile
uint8_t tile[8]=A_LETTER;
// Position
uint8_t x_pos,y_pos;
static uint8_t prev_x,prev_y;

void setup(void)
{

  button.begin(LEFT_PIN,UP_PIN,RIGHT_PIN,DOWN_PIN,B_PIN,A_PIN);
  screen.begin();
}

void loop(void)
{
  
  static int BTStateOld;
  int BTState = button.get_key();
  prev_x=x_pos;
  prev_y=y_pos;
  if(BTState!=BTStateOld)
  {
    if(BTState==RIGHT)
    {
      if(x_pos<14){x_pos++;}
      tone(3, 1000, 50);
    }
    else if(BTState==LEFT)
    {
      if(x_pos>0){x_pos--;}
     tone(3, 1000, 50);
    }
    else if(BTState==DOWN)
    {
      if(y_pos<7){y_pos++;}
      tone(3, 1000, 50);
    }
    else if(BTState==UP)
    {
      if(y_pos>0){y_pos--;}
      tone(3, 1000, 50);
    }
    else if(BTState==A)
    {
      y_pos=3;
      tone(3, 1000, 50);
    }
     else if(BTState==B)
    {
      x_pos=7;
      tone(3, 1000, 50);
    }
    BTStateOld=BTState;
  }
  //if(prev_x!=x_pos || prev_y!=y_pos) {cleanTile1x1(prev_x,prev_y); drawTile1x1(x_pos,y_pos,tile);}
  //if(prev_x!=x_pos || prev_y!=y_pos) {cleanTile2x2(prev_x,prev_y); drawTile2x2(x_pos,y_pos,tile);}
  //if(prev_x!=x_pos || prev_y!=y_pos) {cleanTile2x2(prev_x,prev_y); drawTile1x2(x_pos,y_pos,tile);}
  if(prev_x!=x_pos || prev_y!=y_pos) {screen.cleanTile2x2(prev_x,prev_y); screen.drawTile2x2(x_pos,y_pos,tile);}
}
