/**
	*�ٳ�ʼ��IO��Ϊ���롣
  *    GPIO_Init();
	*�ڿ���IO�ڸ���ʱ�ӡ�
  *    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	*������IO�����ж��ߵ�ӳ���ϵ��
  *    void GPIO_EXTILineConfig();
	*�ܳ�ʼ�������жϣ����ô��������ȡ�
  *    EXTI_Init();
	*�������жϷ��飨NVIC������ʹ���жϡ�
  *    NVIC_Init();
	*�ޱ�д�жϷ�������
  *    EXTIx_IRQHandler();
	*������жϱ�־λ
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
	key_init();//�ٳ�ʼ��IO��Ϊ����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ڿ���IO�ڸ���ʱ��
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


