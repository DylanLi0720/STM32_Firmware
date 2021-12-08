/**
	*��ȡ���Ĵ���д������
  *  IWDG_WriteAccessCmd();
	*�����ö������Ź���Ԥ��Ƶϵ����ȷ��ʱ��:
  *  IWDG_SetPrescaler();
	*�����ÿ��Ź���װ��ֵ��ȷ�����ʱ��:
  *  IWDG_SetReload();
	*��ʹ�ܿ��Ź�
  *  IWDG_Enable();
	*��Ӧ�ó���ι��:
  *  IWDG_ReloadCounter();
	*****************************************
	*					���ʱ����㣺
  *	Tout=((4��2^prer) ��rlr) /40 ��M3)
	*/

/**
	*user_conduction:һ����֮�ڲ����°��������Ź��Ḵλ��������������ĵ�һ�п�ʼִ�У��ͻ���LED��������󡣰��°�������ι����������while(1)����ִ�У�LED����
	*/
#include "stm32f10x.h"
#include "key.h"
#include "iwdg.h"
#include "led.h"
#include "delay.h"

int main()
{
	key_init ();
	LED_Init ();
	delay_init();
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	delay_ms(1000);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	iwdg_init(4,625);//1s���һ�Σ���Ƶϵ��Ϊ4��rlrΪ625
	
	while(1)
	{
		if(key_scan())
		IWDG_ReloadCounter();
	}
}
