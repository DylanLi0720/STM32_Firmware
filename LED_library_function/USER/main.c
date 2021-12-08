#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

int main(void)
{ 	delay_init();
	  LED_Init();
		while(1)
		{
				GPIO_SetBits(GPIOA,GPIO_Pin_5);
				delay_ms(500);
				GPIO_ResetBits(GPIOA,GPIO_Pin_5);
				delay_ms(500);
		}
}	

