//-------------------------------------------- Classes Definitions ----------------------------------------------//
#ifndef CLASSES_HEADERFILE_H
#define CLASSES_HEADERFILE_H
//---------------- Includes --------------------------//
#include "definitions_header.h"

//---------------- Button Class --------------------------//
class Buttons 
{
	private:
		uint8_t BTPressed=0;
		uint8_t BTMatrixOld=0; //00ABDRUPL
		uint8_t BTMatrixNew=0; //00ABDRUPL
		unsigned long LastDebounceTime = 0; 
		unsigned long DebounceDelay = 10; 
    bool MultiKey=0;
		uint8_t Left_Pin;
		uint8_t Up_Pin;
		uint8_t Right_Pin;
		uint8_t Down_Pin;
		uint8_t B_Pin;
		uint8_t A_Pin;
	public:
    // Initialize Arduino GPIO
		void begin(uint8_t Left_Pin,uint8_t Up_Pin,uint8_t Right_Pin,uint8_t Down_Pin,uint8_t B_Pin,uint8_t A_Pin,bool MultiKey=0)
		{
			this->Left_Pin=Left_Pin;
			this->Up_Pin=Up_Pin;
			this->Right_Pin=Right_Pin;
			this->Down_Pin=Down_Pin;
			this->B_Pin=B_Pin;
			this->A_Pin=A_Pin;
      this->MultiKey=MultiKey;
			pinMode(Left_Pin,INPUT_PULLUP);
			pinMode(Up_Pin,INPUT_PULLUP);
			pinMode(Right_Pin,INPUT_PULLUP);
			pinMode(Down_Pin,INPUT_PULLUP);
			pinMode(B_Pin,INPUT_PULLUP);
			pinMode(A_Pin,INPUT_PULLUP);
		}
    // Get user current press key matrix
    uint8_t check()
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
          if(MultiKey) return BTRead;
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
};

#endif
