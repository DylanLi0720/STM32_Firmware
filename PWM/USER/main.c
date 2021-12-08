/**
	*①使能定时器3和相关IO口时钟。
	*     使能定时器3时钟：RCC_APB1PeriphClockCmd();
	*     使能GPIOB时钟：RCC_APB2PeriphClockCmd();
	*②初始化IO口为复用功能输出。函数：GPIO_Init();
  *     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      
	*③这里我们是要把PB5用作定时器的PWM输出引脚，所以要重映射配置，
  *    所以需要开启AFIO时钟。同时设置重映射。
  *     RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
  *     GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); 
	*④初始化定时器：ARR,PSC等：TIM_TimeBaseInit();
	*⑤初始化输出比较参数:TIM_OC2Init();
	*⑥使能预装载寄存器： TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	*⑦使能定时器。TIM_Cmd();
	*⑧不断改变比较值CCRx，达到不同的占空比效果:TIM_SetCompare2();
	*/




#include "delay.h"
#include "sys.h"
#include "pwm.h"

int main(void)
 { 
	 int pwm_val = 1;
	 int pwm_dir = 1;
	 delay_init();
	 
/**
	*可设置PWM波的频率，设置得尽可能的大即周期足够断才连续性较好
	*ARR和PSC寄存器均为16位寄存器，可设置值为0-65536
	*/
	TIM2_CH2_pwm_init(899,0);
	 while(1)
	{
		delay_ms(1);//在此处延时会出现亮度呈现阶梯形式的变化
	  if(pwm_val > 898) pwm_dir = 0;
		if(pwm_val < 1) pwm_dir = 1;
		if(pwm_dir) pwm_val ++;
		else pwm_val --;
		TIM_SetCompare2(TIM2,pwm_val);//CRR寄存器的位数也为16，比较值从0到65536
	}
					    
}	

