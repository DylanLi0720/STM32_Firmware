/**
	*①取消寄存器写保护：
  *  IWDG_WriteAccessCmd();
	*②设置独立看门狗的预分频系数，确定时钟:
  *  IWDG_SetPrescaler();
	*③设置看门狗重装载值，确定溢出时间:
  *  IWDG_SetReload();
	*④使能看门狗
  *  IWDG_Enable();
	*⑤应用程序喂狗:
  *  IWDG_ReloadCounter();
	*****************************************
	*					溢出时间计算：
  *	Tout=((4×2^prer) ×rlr) /40 （M3)
	*/

/**
	*user_conduction:一秒中之内不按下按键，看门狗会复位，程序从主函数的第一行开始执行，就会有LED亮灭的现象。按下按键代表喂狗，程序在while(1)里面执行，LED常亮
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
	iwdg_init(4,625);//1s溢出一次，分频系数为4，rlr为625
	
	while(1)
	{
		if(key_scan())
		IWDG_ReloadCounter();
	}
}
