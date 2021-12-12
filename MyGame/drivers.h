//------------------------------------ Drivers for HMI --------------------------------//
#ifndef DRIVERS_H
#define DRIVERS_H
//---------------- Includes --------------------------//
#include "globals.h"

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

#endif
