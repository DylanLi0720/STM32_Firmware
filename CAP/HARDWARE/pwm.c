#include "sys.h"
#include "pwm.h"

void TIM2_CH2_pwm_init(u16 arr,u16 psc)
{
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_Struct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//��ʹ�����趨ʱ��2ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//��ʹ��GPIO�͸��ù��ܵ�ʱ��
	
/**
	*TIM2/3/4/5���� 	*					���� 			  *     GPIO����
	******************************************************************
	*									*		���벶��ͨ��x 			*			��������
	*TIM2/3/4/5_CHx   ************************************************			
	*									*		����Ƚ�ͨ��x 			*			���츴�����
	******************************************************************
	*TIM2/3/4/5_ETR 	*		�ⲿ����ʱ������ 	*			��������
	******************************************************************
	*������GPIO�������ʽλ�������������ͬʱѡ��ʱ��2��Ӧ��ͨ��2����PA1
	*/
	
	GPIO_Struct.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Struct.GPIO_Pin = GPIO_Pin_1;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
/**
	*�ܳ�ʼ����ʱ��������ARR,PSC
  *    TIM_TimeBaseInit();
	*���迪����ӳ�䣬����GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE)����
	*/
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//���ĸ���������������ʱ�ӷ�Ƶ���ӣ�1��2���ɣ���Ϊ���յ�ʱ��Ƶ����ͬ
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Down;//����Ϊ���ϼ��������¼�����ʽ����������������ʽ�� �Ƚϳ��õ������ϼ���ģʽ TIM_CounterMode_Up �����¼���ģʽ TIM_CounterMode_Down
	TIM_TimeBaseInitStruct.TIM_Period = arr;//װ������ĳ�ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;//����PSC�Ĵ�����CK_PSCԤ��ƵΪCK_CNT,��Ϊ��ʱ����ʱ��
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);

/**
	*OCΪ����ȽϺ�������ʼ������Ƚϲ�������TIMx_CCMRx�Ĵ����е�OCxMλд�롯110��(PWMģʽ1)��111��(PWMģʽ2)��
	*�ܹ�����������ÿ��OCx���ͨ������һ·PWM������ͨ������TIMx_CCMRx�Ĵ�����OCxPEλʹ����Ӧ��Ԥװ�ؼĴ��������
	*��Ҫ����TIMx_CR1�Ĵ�����ARPEλ�� (�����ϼ��������ĶԳ�ģʽ��)ʹ���Զ���װ�ص�Ԥװ�ؼĴ�����
	*******************************************************************************************************
	*PWMģʽ1��TIM_CNT < TIM_CRR1ʱ�����OCxREFΪ��Ч��ƽ�����ߵ�ƽ�������������Ч��ƽ�����͵�ƽ��
	*PWMģʽ2��TIM_CNT < TIM_CRR1ʱ�����OCxREFΪ��Ч��ƽ�����͵�ƽ�������������Ч��ƽ�����ߵ�ƽ��
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
	*���� TIM_OCMode ����ģʽ�� PWM ��������Ƚϣ����������� PWM ģʽ��
	*���� TIM_OutputState �������ñȽ����ʹ�ܣ�Ҳ����ʹ�� PWM ������˿ڡ�
	*���� TIM_OCPolarity �������ü����Ǹ߻��ǵ͡���������TIMx_CCER�Ĵ����ǵ͵�ƽ��Ч���Ǹߵ�ƽ��Ч��
	*�����Ĳ��� TIM_OutputNState�� TIM_OCNPolarity�� TIM_OCIdleState �� TIM_OCNIdleState ��
	*�߼���ʱ�� TIM1 �� TIM8 ���õ���
	*/
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;//����CCMR�Ĵ���������PWM�������ʽΪ�����ߣ�
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//����Ϊ�ߵ�ƽ��Ч
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM2,&TIM_OCInitStruct);
	
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);//������Ҫ��ѡ���ʹ��Ԥװ�ؼĴ�������TIMx_CCMR1�е�OC1PE=1��TIMx_CR1�Ĵ����е�ARPE
	
	TIM_Cmd(TIM2,ENABLE);//����TIM_CR�Ĵ��������ƼĴ�����

}

void TIM3_CH1_pwm_init(u16 arr,u16 psc)
{
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_Struct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//��ʹ�����趨ʱ��2ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);//��ʹ��GPIO�͸��ù��ܵ�ʱ��
	
/**
	*TIM2/3/4/5���� 	*					���� 			  *     GPIO����
	******************************************************************
	*									*		���벶��ͨ��x 			*			��������
	*TIM2/3/4/5_CHx   ************************************************			
	*									*		����Ƚ�ͨ��x 			*			���츴�����
	******************************************************************
	*TIM2/3/4/5_ETR 	*		�ⲿ����ʱ������ 	*			��������
	******************************************************************
	*������GPIO�������ʽλ�������������ͬʱѡ��ʱ��3��Ӧ��ͨ��1����PA1
	*/
	
	GPIO_Struct.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Struct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
/**
	*�ܳ�ʼ����ʱ��������ARR,PSC
  *    TIM_TimeBaseInit();
	*���迪����ӳ�䣬����GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE)����
	*/
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//���ĸ���������������ʱ�ӷ�Ƶ���ӣ�1��2���ɣ���Ϊ���յ�ʱ��Ƶ����ͬ
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Down;//����Ϊ���ϼ��������¼�����ʽ����������������ʽ�� �Ƚϳ��õ������ϼ���ģʽ TIM_CounterMode_Up �����¼���ģʽ TIM_CounterMode_Down
	TIM_TimeBaseInitStruct.TIM_Period = arr;//װ������ĳ�ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;//����PSC�Ĵ�����CK_PSCԤ��ƵΪCK_CNT,��Ϊ��ʱ����ʱ��
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);

/**
	*OCΪ����ȽϺ�������ʼ������Ƚϲ�������TIMx_CCMRx�Ĵ����е�OCxMλд�롯110��(PWMģʽ1)��111��(PWMģʽ2)��
	*�ܹ�����������ÿ��OCx���ͨ������һ·PWM������ͨ������TIMx_CCMRx�Ĵ�����OCxPEλʹ����Ӧ��Ԥװ�ؼĴ��������
	*��Ҫ����TIMx_CR1�Ĵ�����ARPEλ�� (�����ϼ��������ĶԳ�ģʽ��)ʹ���Զ���װ�ص�Ԥװ�ؼĴ�����
	*******************************************************************************************************
	*PWMģʽ1��TIM_CNT < TIM_CRR1ʱ�����OCxREFΪ��Ч��ƽ�����ߵ�ƽ�������������Ч��ƽ�����͵�ƽ��
	*PWMģʽ2��TIM_CNT < TIM_CRR1ʱ�����OCxREFΪ��Ч��ƽ�����͵�ƽ�������������Ч��ƽ�����ߵ�ƽ��
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
	*���� TIM_OCMode ����ģʽ�� PWM ��������Ƚϣ����������� PWM ģʽ��
	*���� TIM_OutputState �������ñȽ����ʹ�ܣ�Ҳ����ʹ�� PWM ������˿ڡ�
	*���� TIM_OCPolarity �������ü����Ǹ߻��ǵ͡���������TIMx_CCER�Ĵ����ǵ͵�ƽ��Ч���Ǹߵ�ƽ��Ч��
	*�����Ĳ��� TIM_OutputNState�� TIM_OCNPolarity�� TIM_OCIdleState �� TIM_OCNIdleState ��
	*�߼���ʱ�� TIM1 �� TIM8 ���õ���
	*/
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;//����CCMR�Ĵ���������PWM�������ʽΪ�����ߣ�
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//����Ϊ�ߵ�ƽ��Ч
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//������Ҫ��ѡ���ʹ��Ԥװ�ؼĴ�������TIMx_CCMR1�е�OC1PE=1��TIMx_CR1�Ĵ����е�ARPE
	
	TIM_Cmd(TIM3,ENABLE);//����TIM_CR�Ĵ��������ƼĴ�����

}
