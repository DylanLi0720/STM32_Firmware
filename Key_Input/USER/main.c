#include "delay.h"
#include "stm32f10x.h"
#include "key.h"
#include "led.h"

int main(void)
 { 
	 bool is_key = FALSE;
	 delay_init();
	 key_init();
	 LED_Init();
	 while(1)
	 {
		 is_key = key_scan ();
		 if(is_key)
		 {
			 GPIO_SetBits(GPIOA,GPIO_Pin_5);
		 }
		 else
		 {
			 GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		 }
	 }		    
}	

