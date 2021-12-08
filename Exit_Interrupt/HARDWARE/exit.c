#include "stm32f10x.h"
#include "exit.h"
#include "delay.h"
#include "key.h"

EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

int FLAG = 1;
void exit_init(void)
{		delay_init();
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);//������IO�����ж��ߵ�ӳ���ϵ
		
	/**
		*�ܳ�ʼ�������жϣ����ô���������
		*/
		EXTI_InitStruct.EXTI_Line = EXTI_Line13;
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_Init(&EXTI_InitStruct);

	/**
		*�������жϷ��飨NVIC������ʹ���ж�
		*/
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ȼ�����
	
		NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&NVIC_InitStruct);
	}

	void EXTI15_10_IRQHandler(void)//���жϺ����������ļ�������
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
