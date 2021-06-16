#include "button.h"

TS_TypeInput	vrts_Key1, vrts_Key2, vrts_Key3, vrts_ButtonScan;

void buttonInit(void){
	GPIO_InitTypeDef gpio;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Init(PORT_KEY23, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_15;
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(PORT_KEY1, &gpio);
}

void buttonCheck(void){
	printf("%d  ",GPIO_ReadInputDataBit(PORT_KEY1,PIN_KEY1));
	printf("%d  ",GPIO_ReadInputDataBit(PORT_KEY23,PIN_KEY2));
	printf("%d  \n",GPIO_ReadInputDataBit(PORT_KEY23,PIN_KEY3));
	Delay_ms(100);
}

void Fn_INPUT_ReadInput (unsigned char _vruc_Input, TS_TypeInput *_vrts_DataInput){
  _vrts_DataInput->vruc_DataOld = _vruc_Input;
  if(_vruc_Input){
    if(_vrts_DataInput->vruc_DataOld == _vruc_Input){
      if(_vrts_DataInput->vruc_CountAccess <= MAXINPUT){
        _vrts_DataInput->vruc_CountAccess++;
        if(_vrts_DataInput->vruc_CountAccess == 20){
          _vrts_DataInput->vruc_FlagChange = 1;
          _vrts_DataInput->vruc_hold = 0;
        }
      }
      else
      {
        _vrts_DataInput->vruc_hold = 1;
      }
    }
    else{
      _vrts_DataInput->vruc_CountAccess = 0;
    }
  }
  else{
    _vrts_DataInput->vruc_CountAccess = 0;
  }
}
u16 count = 0;
void buttonOutput(void){
	//printf("Hello Thai Salem.\n");
	Fn_INPUT_ReadInput(GPIO_ReadInputDataBit(PORT_KEY1,PIN_KEY1), (TS_TypeInput*)(&vrts_Key1));
//	printf("%d",vrts_Key1.vruc_FlagChange);
	
	if(vrts_Key1.vruc_FlagChange){
		vrts_Key1.vruc_FlagChange = 0;
		printf("LED ON");
//		GPIOA->ODR = 0x0100;
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		if(vrts_Key1.vruc_hold){
			count++;
			if(count >= 2000){
				vrts_Key1.vruc_hold = 0;
				GPIO_ResetBits(GPIOC, GPIO_Pin_7);
				count = 0;
				
			}
			else{
				GPIO_SetBits(GPIOC, GPIO_Pin_7);
				//printf("PC7 ON");

			}
		}
	}

	Delay_ms(1);
}

unsigned int counter = 0, STT = 0, start  = 0, counter_out = 0, i = 0, j = 0;
unsigned int arr[3];
unsigned int mode = 0;

void Button_even(void){
    if(vrts_ButtonScan.vruc_FlagChange == 1){    
      vrts_ButtonScan.vruc_FlagChange = 0;
      if(!start){
        mode = 1;
        counter = 0;
        counter_out = 0;
        for(j = 0; j<3; j++){
          arr[j] = 0;
        }
        i = 0;
      }
      else{
        arr[i] = counter;
        counter = 0;
        i++;
      }
      start = 1;
    }
    
    if(start){
      if(counter_out <= 1000){ //  counter_out >= 1000
        for(j = 0; j<3; j++){
          if((arr[j] > 150) && (arr[j] < 500)){
             mode++;
          }
        }      
        if(mode == 1){       
           vrts_Key1.vruc_FlagChange = 1;
        }
        else if(mode == 2){
           vrts_Key2.vruc_FlagChange = 1;
        }
        else if(mode == 3){
         
           vrts_Key3.vruc_FlagChange = 1;
        }

        start = 0;
      }
    counter_out++;
    counter++;
  }
}