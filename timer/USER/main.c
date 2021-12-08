/**
	*��ʹ�ܶ�ʱ��ʱ�ӡ�
  *    RCC_APB1PeriphClockCmd();
	*�ڳ�ʼ����ʱ��������ARR,PSC��
  *    TIM_TimeBaseInit();
	*�ۿ�����ʱ���жϣ�����NVIC��
  *    void TIM_ITConfig();
  *    NVIC_Init();
	*��ʹ�ܶ�ʱ����
  *    TIM_Cmd();
	*�ޱ�д�жϷ�������
  *    TIMx_IRQHandler();
	*�߸����жϱ�־λ����
	*********************************************************
	*(�ڲ�ʱ��CK_INTһ����Ϊ72M����Ϊ��AHP��Ƶ��APB2�ٱ�ƵΪCK_PSC,����PSCԤ��Ƶ����Ƶ�õ�CK_CNT,����ʱ��TclkΪ72M)
	*********************************************************
	*Tout�����ʱ�䣩=��ARR+1)(PSC+1)/Tclk
	*(Ԥ��Ƶ�Ĵ���TIM_PSCΪ16λ������PSC��ֵ����λ0-65536.�Զ���װ�ؼĴ���TIMx_ARRҲ��16λ���ʶ�װ�ص�ֵΪ0-65536)
	*/
	
#include "stm32f10x.h"
#include "timer.h"
#include "led.h"
#include "stdbool.h"

bool flag = true;

int main()
{
	LED_Init();
	timer2_init(9999,7199);//����1s�н���һ���ж�
	while(1)
	{
		if(flag)
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
		else
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	}
}

/**
	*���жϷ�����
	*/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)//�����ж�ʱSR�Ĵ����ĵ�0λ��Ӳ����Ϊ1�������������(Ҳ���Բ����жϱ�־λ)
	{
		flag = !flag;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//�߸����жϱ�־λ��SR�Ĵ�����0λȡ��

	}
}
