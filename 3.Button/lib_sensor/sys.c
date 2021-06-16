#include "sys.h"

struct __FILE {
    int dummy;
};
 
/* You need this if you want use printf */
/* Struct FILE is implemented in stdio.h */
FILE __stdout;
 
int fputc(int ch, FILE *f) {
    /* Do your stuff here */
    /* Send your custom byte */
    /* Send byte to USART */
    /*neu su dung usart1 thi bo comment; tuong tu voi cac usart2,3*/
    uartSend_Char(USART1, ch);
//    USARTx_Sendc(USART2, ch);
//    USARTx_Sendc(USART3, ch);
    /* If everything is OK, you have to return character written */
    return ch;
    /* If character is not correct, you can return EOF (-1) to stop writing */
    //return -1;
}



void uartInit(void){
	GPIO_InitTypeDef gpio_typedef;
	USART_InitTypeDef usart_typedef;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_USART1, ENABLE);
	
	gpio_typedef.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_typedef.GPIO_Pin = GPIO_Pin_9;
	gpio_typedef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_typedef);
	
	gpio_typedef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_typedef.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &gpio_typedef);
	
	usart_typedef.USART_BaudRate = 9600;
	usart_typedef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_typedef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
	usart_typedef.USART_Parity = USART_Parity_No;
	usart_typedef.USART_StopBits = USART_StopBits_1;
	usart_typedef.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usart_typedef);
	/*----------------------------------------------------------------------------------------*/		
	/*if use usart interrup */
	//  Enable RXNE interrupt 
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	 /* Enable USART1 global interrupt */
//	NVIC_EnableIRQ(USART1_IRQn);
	/*----------------------------------------------------------------------------------------*/		
	USART_Cmd(USART1, ENABLE);
}

void uartSend_Char(USART_TypeDef* USART_x, char c){
	USART_SendData(USART_x,c);
	while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE)==RESET);
}

void uartSend_String(USART_TypeDef* USART_x, char* s){
	while(*s!='\0'){
		uartSend_Char(USART_x,*s++);
		while(USART_GetFlagStatus(USART_x, USART_FLAG_TXE)==RESET);
	}
}

void ledInit(void){
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOC, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_8;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &gpio);
}

void sysInit(void){
	uartInit();
	ledInit();
	buttonInit();

}

void sysRun(void){
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		//buttonCheck();
		//Delay_ms(1000);	
		buttonOutput();
}




