/**
	*①初始化IO口为输入。
  *    GPIO_Init();
	*②开启IO口复用时钟。
  *    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	*③设置IO口与中断线的映射关系。
  *    void GPIO_EXTILineConfig();
	*④初始化线上中断，设置触发条件等。
  *    EXTI_Init();
	*⑤配置中断分组（NVIC），并使能中断。
  *    NVIC_Init();
	*⑥编写中断服务函数。
  *    EXTIx_IRQHandler();
	*⑦清除中断标志位
  *    EXTI_ClearITPendingBit();
	*/
	
#include "stm32f10x.h"
#include "key.h"
#include "led.h"
#include "delay.h"
#include "exit.h"

int main(void)
{
	extern int FLAG;
	key_init();//①初始化IO口为输入
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//②开启IO口复用时钟
	LED_Init();
	exit_init();
	delay_init();
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	while(1)
	{
		if(FLAG)
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
		else
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	}
}	


