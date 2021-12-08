#include "stm32f10x.h"
#include "led.h"

void LED_Init()
{
		RCC->APB2ENR|=1<<2;
		GPIOA->CRL &= 0XFFF0FFFFF;
		GPIOA->CRL |= 0X000300000;
		GPIOA->ODR |= 1<<5;
}
