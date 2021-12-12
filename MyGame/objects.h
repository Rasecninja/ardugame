//------------------------------------ Objects in the game --------------------------------//
#ifndef OBJECTS_H
#define OBJECTS_H

#include "drivers.h"

//---------------- Player Class --------------------------//
class Player 
{
 public:
    Player(char *pBitmap,char BitmapSize,char BitmapDimX,char BitmapDimY);  // This is the constructor
    void update_pos(ButtonPressed Btn);
 private:
    char *pBitmap;
    char BitmapSize; // in bytes
    char BitmapDimX;
    char BitmapDimY;
    char PosX;
    char PosY;
};
 
// Member functions definitions including constructor
Player::Player(char *pBitmap,char BitmapSize,char BitmapDimX,char BitmapDimY) 
{
   
}

void Player::update_pos(ButtonPressed Btn)
{

}

#endif
