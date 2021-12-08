#include "sys.h"
#include "pwm.h"

void TIM2_CH2_pwm_init(u16 arr,u16 psc)
{
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_Struct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//①使能外设定时器2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//②使能GPIO和复用功能的时钟
	
/**
	*TIM2/3/4/5引脚 	*					配置 			  *     GPIO配置
	******************************************************************
	*									*		输入捕获通道x 			*			浮空输入
	*TIM2/3/4/5_CHx   ************************************************			
	*									*		输出比较通道x 			*			推挽复用输出
	******************************************************************
	*TIM2/3/4/5_ETR 	*		外部触发时钟输入 	*			浮空输入
	******************************************************************
	*③配置GPIO的输出方式位复用推挽输出，同时选择定时器2对应的通道2引脚PA1
	*/
	
	GPIO_Struct.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Struct.GPIO_Pin = GPIO_Pin_1;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
/**
	*④初始化定时器，配置ARR,PSC
  *    TIM_TimeBaseInit();
	*若需开启重映射，还需GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE)函数
	*/
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//第四个参数是用来设置时钟分频因子，1和2均可，因为最终的时钟频率相同
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Down;//设置为向上计数，向下计数方式还有中央对齐计数方式， 比较常用的是向上计数模式 TIM_CounterMode_Up 和向下计数模式 TIM_CounterMode_Down
	TIM_TimeBaseInitStruct.TIM_Period = arr;//装载溢出的初值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;//利用PSC寄存器将CK_PSC预分频为CK_CNT,即为定时器的时钟
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);

/**
	*OC为输出比较函数，初始化输出比较参数。在TIMx_CCMRx寄存器中的OCxM位写入’110’(PWM模式1)或’111’(PWM模式2)，
	*能够独立地设置每个OCx输出通道产生一路PWM。必须通过设置TIMx_CCMRx寄存器的OCxPE位使能相应的预装载寄存器，最后
	*还要设置TIMx_CR1寄存器的ARPE位， (在向上计数或中心对称模式中)使能自动重装载的预装载寄存器。
	*******************************************************************************************************
	*PWM模式1：TIM_CNT < TIM_CRR1时输出的OCxREF为有效电平（即高电平）；否则输出无效电平（即低电平）
	*PWM模式2：TIM_CNT < TIM_CRR1时输出的OCxREF为无效电平（即低电平）；否则输出有效电平（即高电平）
	*******************************************************************************************************
	*typedef struct
	*{
	* uint16_t TIM_OCMode;
	* uint16_t TIM_OutputState;
	* uint16_t TIM_OutputNState;
	* uint16_t TIM_Pulse;
	* uint16_t TIM_OCPolarity;
	* uint16_t TIM_OCNPolarity;
	* uint16_t TIM_OCIdleState;
	* uint16_t TIM_OCNIdleState;
	*} TIM_OCInitTypeDef;
	********************************************************************************************************
	*参数 TIM_OCMode 设置模式是 PWM 还是输出比较，这里我们是 PWM 模式。
	*参数 TIM_OutputState 用来设置比较输出使能，也就是使能 PWM 输出到端口。
	*参数 TIM_OCPolarity 用来设置极性是高还是低。（即设置TIMx_CCER寄存器是低电平有效还是高电平有效）
	*其他的参数 TIM_OutputNState， TIM_OCNPolarity， TIM_OCIdleState 和 TIM_OCNIdleState 是
	*高级定时器 TIM1 和 TIM8 才用到的
	*/
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;//操作CCMR寄存器，设置PWM的输出方式为１或者２
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//设置为高电平有效
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM2,&TIM_OCInitStruct);
	
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);//根据需要有选择地使能预装载寄存器：置TIMx_CCMR1中的OC1PE=1和TIMx_CR1寄存器中的ARPE
	
	TIM_Cmd(TIM2,ENABLE);//操作TIM_CR寄存器（控制寄存器）

}

void TIM3_CH1_pwm_init(u16 arr,u16 psc)
{
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_Struct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//①使能外设定时器2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//②使能GPIO和复用功能的时钟
	
/**
	*TIM2/3/4/5引脚 	*					配置 			  *     GPIO配置
	******************************************************************
	*									*		输入捕获通道x 			*			浮空输入
	*TIM2/3/4/5_CHx   ************************************************			
	*									*		输出比较通道x 			*			推挽复用输出
	******************************************************************
	*TIM2/3/4/5_ETR 	*		外部触发时钟输入 	*			浮空输入
	******************************************************************
	*③配置GPIO的输出方式位复用推挽输出，同时选择定时器3对应的通道1引脚PA1
	*/
	
	GPIO_Struct.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Struct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
/**
	*④初始化定时器，配置ARR,PSC
  *    TIM_TimeBaseInit();
	*若需开启重映射，还需GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE)函数
	*/
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//第四个参数是用来设置时钟分频因子，1和2均可，因为最终的时钟频率相同
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Down;//设置为向上计数，向下计数方式还有中央对齐计数方式， 比较常用的是向上计数模式 TIM_CounterMode_Up 和向下计数模式 TIM_CounterMode_Down
	TIM_TimeBaseInitStruct.TIM_Period = arr;//装载溢出的初值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;//利用PSC寄存器将CK_PSC预分频为CK_CNT,即为定时器的时钟
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);

/**
	*OC为输出比较函数，初始化输出比较参数。在TIMx_CCMRx寄存器中的OCxM位写入’110’(PWM模式1)或’111’(PWM模式2)，
	*能够独立地设置每个OCx输出通道产生一路PWM。必须通过设置TIMx_CCMRx寄存器的OCxPE位使能相应的预装载寄存器，最后
	*还要设置TIMx_CR1寄存器的ARPE位， (在向上计数或中心对称模式中)使能自动重装载的预装载寄存器。
	*******************************************************************************************************
	*PWM模式1：TIM_CNT < TIM_CRR1时输出的OCxREF为有效电平（即高电平）；否则输出无效电平（即低电平）
	*PWM模式2：TIM_CNT < TIM_CRR1时输出的OCxREF为无效电平（即低电平）；否则输出有效电平（即高电平）
	*******************************************************************************************************
	*typedef struct
	*{
	* uint16_t TIM_OCMode;
	* uint16_t TIM_OutputState;
	* uint16_t TIM_OutputNState;
	* uint16_t TIM_Pulse;
	* uint16_t TIM_OCPolarity;
	* uint16_t TIM_OCNPolarity;
	* uint16_t TIM_OCIdleState;
	* uint16_t TIM_OCNIdleState;
	*} TIM_OCInitTypeDef;
	********************************************************************************************************
	*参数 TIM_OCMode 设置模式是 PWM 还是输出比较，这里我们是 PWM 模式。
	*参数 TIM_OutputState 用来设置比较输出使能，也就是使能 PWM 输出到端口。
	*参数 TIM_OCPolarity 用来设置极性是高还是低。（即设置TIMx_CCER寄存器是低电平有效还是高电平有效）
	*其他的参数 TIM_OutputNState， TIM_OCNPolarity， TIM_OCIdleState 和 TIM_OCNIdleState 是
	*高级定时器 TIM1 和 TIM8 才用到的
	*/
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;//操作CCMR寄存器，设置PWM的输出方式为１或者２
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//设置为高电平有效
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//根据需要有选择地使能预装载寄存器：置TIMx_CCMR1中的OC1PE=1和TIMx_CR1寄存器中的ARPE
	
	TIM_Cmd(TIM3,ENABLE);//操作TIM_CR寄存器（控制寄存器）

}
