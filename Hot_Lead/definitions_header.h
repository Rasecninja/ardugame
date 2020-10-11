//---------------------------------------------- General Definitions --------------------------------------------//
#ifndef DEFINITIONSHEADERFILE_H
#define DEFINITIONSHEADERFILE_H
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

#endif
