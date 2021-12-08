#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

int main(void)
 { 
	 LED_Init ();
	 delay_init();
	 while(1)
	{
			delay_ms(500);
			GPIOA->ODR &= ~(1<<5);
			delay_ms(500);
			GPIOA->ODR |= 1<<5;
	}
					    
}	

