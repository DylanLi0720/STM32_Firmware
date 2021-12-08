#include "stm32f10x.h"
#include "exit.h"
#include "delay.h"
#include "key.h"

EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

int FLAG = 1;
void exit_init(void)
{		delay_init();
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);//③设置IO口与中断线的映射关系
		
	/**
		*④初始化线上中断，设置触发条件等
		*/
		EXTI_InitStruct.EXTI_Line = EXTI_Line13;
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_Init(&EXTI_InitStruct);

	/**
		*⑤配置中断分组（NVIC），并使能中断
		*/
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级分组
	
		NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&NVIC_InitStruct);
	}

	void EXTI15_10_IRQHandler(void)//⑥中断函数在启动文件中声明
{
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == 0)
	{
		delay_init();
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == 0)
		{
			while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == 0);
			FLAG = !FLAG;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line13);
}
