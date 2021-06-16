#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "sys.h"

/*
 *  
 *PIN BUTTON: PA15, PC10, PC11
 *PIN NAME	: KEY1, KEY2, KEY3
 *Value: button_value = 0 -> press button;
*/

#define MAXINPUT	(800) // time giu nut nhan vang

#define PORT_KEY1 GPIOA
#define PIN_KEY1 	GPIO_Pin_15

#define PORT_KEY23 GPIOC
#define PIN_KEY2 	GPIO_Pin_10
#define PIN_KEY3 	GPIO_Pin_11



typedef struct{
	unsigned char	vruc_DataOld;
	unsigned int 	vruc_CountAccess;
	unsigned char 	vruc_FlagChange;
  unsigned char   vruc_hold;
}	TS_TypeInput;

extern TS_TypeInput	vrts_Key1, vrts_Key2, vrts_Key3, vrts_ButtonScan;

void buttonInit(void);

void buttonCheck(void);

void Fn_INPUT_ReadInput (unsigned char _vruc_Input, TS_TypeInput *_vrts_DataInput);
void buttonOutput(void);
	
#endif

