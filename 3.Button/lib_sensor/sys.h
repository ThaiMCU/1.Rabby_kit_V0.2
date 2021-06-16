#ifndef _SYS_H_
#define _SYS_H_

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "mcu-dht11.h"
#include "mcu-delay.h"
#include "button.h"
#include "stdio.h"



void sysInit(void);
void sysRun(void);

void uartInit(void);
void uartSend_Char(USART_TypeDef* USART_x, char c);
void uartSend_String(USART_TypeDef* USART_x, char* s);


#endif
