//-------------------------------------------- Ardugame Definitions ----------------------------------------------//

//-------------------- Defines -------------------------------//
// Define buttons
#define LEFT_PIN 2
#define UP_PIN 4
#define RIGHT_PIN 5
#define DOWN_PIN 6
#define B_PIN 7
#define A_PIN 8
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

//--------------------- Classes ------------------------------//
class Buttons 
{
	private:
		uint8_t BTPressed=0;
		uint8_t BTMatrixOld=0; //00ABDRUPL
		uint8_t BTMatrixNew=0; //00ABDRUPL
		unsigned long LastDebounceTime = 0; 
		unsigned long DebounceDelay = 20; 
		uint8_t Left_Pin;
		uint8_t Up_Pin;
		uint8_t Right_Pin;
		uint8_t Down_Pin;
		uint8_t B_Pin;
		uint8_t A_Pin;
		uint8_t Left_State=1;
		uint8_t Up_State=1;
		uint8_t Right_State=1;
		uint8_t Down_State=1;
		uint8_t B_State=1;
		uint8_t A_State=1;
	public:
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
