#include "stm32f10x.h"
#include "delay.h"

GPIO_InitTypeDef GPIO_InitStruct;

int main(void)
{
		delay_init();
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_Init(GPIOB,&GPIO_InitStruct);
		while(1)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
			delay_ms(500);
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
			delay_ms(500);
		}
}	

