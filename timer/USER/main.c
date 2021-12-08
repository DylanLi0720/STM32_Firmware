/**
	*①使能定时器时钟。
  *    RCC_APB1PeriphClockCmd();
	*②初始化定时器，配置ARR,PSC。
  *    TIM_TimeBaseInit();
	*③开启定时器中断，配置NVIC。
  *    void TIM_ITConfig();
  *    NVIC_Init();
	*④使能定时器。
  *    TIM_Cmd();
	*⑥编写中断服务函数。
  *    TIMx_IRQHandler();
	*⑦更新中断标志位置零
	*********************************************************
	*(内部时钟CK_INT一般是为72M，因为由AHP分频到APB2再倍频为CK_PSC,再由PSC预分频器分频得到CK_CNT,即定时的Tclk为72M)
	*********************************************************
	*Tout（溢出时间）=（ARR+1)(PSC+1)/Tclk
	*(预分频寄存器TIM_PSC为16位，所以PSC的值可以位0-65536.自动重装载寄存器TIMx_ARR也是16位，故而装载的值为0-65536)
	*/
	
#include "stm32f10x.h"
#include "timer.h"
#include "led.h"
#include "stdbool.h"

bool flag = true;

int main()
{
	LED_Init();
	timer2_init(9999,7199);//设置1s中进入一次中断
	while(1)
	{
		if(flag)
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
		else
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	}
}

/**
	*⑥中断服务函数
	*/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)//更新中断时SR寄存器的第0位被硬件置为1，必须软件清零(也可以不用判断标志位)
	{
		flag = !flag;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//⑦更新中断标志位，SR寄存器第0位取反

	}
}
