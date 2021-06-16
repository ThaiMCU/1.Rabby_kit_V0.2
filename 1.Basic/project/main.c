#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/*
 *  
 *PIN LED: PC7, PC8, PC9, PA8
 *
*/

void delayMs(u16 _time);
void gpioConfig(void);
void blinkLed(void);

int main(){
	gpioConfig();
	while(1){
		blinkLed();
	}
}

void delayMs(u16 _time){
	u16 i,j;
	for(i = 0; i < _time; i++){
		for(j = 0; j < 0x2aff; j++){}
	}
}

void gpioConfig(void){
	
	RCC->APB2ENR = 0x14; // PORT A,C
	
	GPIOA->CRH = 0x00000003; // PA8
	GPIOC->CRL = 0x30000000; // PC7
	GPIOC->CRH = 0x00000033; // PC8, PC9
}

void blinkLed(void){
	GPIOA->ODR = 0x0100;
	GPIOC->ODR = 0x0380;
	delayMs(200);
	GPIOA->ODR = 0x0000;
	GPIOC->ODR = 0x0000;
	delayMs(200);
}

