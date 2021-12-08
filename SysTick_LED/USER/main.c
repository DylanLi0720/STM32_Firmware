#include "delay.h"
#include "stm32f10x.h"
#include "gpio_config.h"

uint32_t TimingDelay;

void Init_SysTick(void);
 
void delay_ms(uint32_t Time);


int main(void)
{ 
	 LED_GPIOD_Config();
	 Init_SysTick();
	 while(1)
	{
	 GPIO_SetBits(GPIOA,GPIO_Pin_5);
	 delay_ms(1000);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	 delay_ms(1000);
	}    
}	
 
 void Init_SysTick(void)
{
	while(SysTick_Config(SystemCoreClock/1000));
}

void delay_ms(uint32_t Time)
{
	TimingDelay = Time;
	while(TimingDelay != 0);
}
//TimingDelay在stm32f10x_it.h的中断函数中改变值

