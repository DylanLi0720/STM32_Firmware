/**
	*��ʹ�ܶ�ʱ��3�����IO��ʱ�ӡ�
	*     ʹ�ܶ�ʱ��3ʱ�ӣ�RCC_APB1PeriphClockCmd();
	*     ʹ��GPIOBʱ�ӣ�RCC_APB2PeriphClockCmd();
	*�ڳ�ʼ��IO��Ϊ���ù��������������GPIO_Init();
  *     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      
	*������������Ҫ��PB5������ʱ����PWM������ţ�����Ҫ��ӳ�����ã�
  *    ������Ҫ����AFIOʱ�ӡ�ͬʱ������ӳ�䡣
  *     RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
  *     GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); 
	*�ܳ�ʼ����ʱ����ARR,PSC�ȣ�TIM_TimeBaseInit();
	*�ݳ�ʼ������Ƚϲ���:TIM_OC2Init();
	*��ʹ��Ԥװ�ؼĴ����� TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	*��ʹ�ܶ�ʱ����TIM_Cmd();
	*�಻�ϸı�Ƚ�ֵCCRx���ﵽ��ͬ��ռ�ձ�Ч��:TIM_SetCompare2();
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
	*������PWM����Ƶ�ʣ����õþ����ܵĴ������㹻�ϲ������ԽϺ�
	*ARR��PSC�Ĵ�����Ϊ16λ�Ĵ�����������ֵΪ0-65536
	*/
	TIM2_CH2_pwm_init(899,0);
	 while(1)
	{
		delay_ms(1);//�ڴ˴���ʱ��������ȳ��ֽ�����ʽ�ı仯
	  if(pwm_val > 898) pwm_dir = 0;
		if(pwm_val < 1) pwm_dir = 1;
		if(pwm_dir) pwm_val ++;
		else pwm_val --;
		TIM_SetCompare2(TIM2,pwm_val);//CRR�Ĵ�����λ��ҲΪ16���Ƚ�ֵ��0��65536
	}
					    
}	

