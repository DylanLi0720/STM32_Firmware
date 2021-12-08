#include "key.h"
#include "delay.h"
#include "stm32f10x.h"
#include "stdbool.h"

void key_init()	
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode =  GPIO_Mode_IPU;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

//bool key_scan()
//{
//	static int flag = 0;
//	if(!key)
//	{
//		delay_ms(10); //去抖
//		if(!key)
//		{
//			while(!key);
//			flag = !flag;
//		}
//	}
// 	if(flag) return true;
//	else return false; // 无按键按下
//}
