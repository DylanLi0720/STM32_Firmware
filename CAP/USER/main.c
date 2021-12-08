/**
	*�ٳ�ʼ����ʱ����ͨ����ӦIO��ʱ�ӡ�
	*�ڳ�ʼ��IO�ڣ�ģʽΪ���룺GPIO_Init();
  *  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����
	*�۳�ʼ����ʱ��ARR��PSC
	*	 TIM_TimeBaseInit();
	*�ܳ�ʼ�����벶��ͨ��
  *  TIM_ICInit();
	*�����Ҫ���������жϣ�
  *  TIM_ITConfig();
  *  NVIC_Init();
	*��ʹ�ܶ�ʱ����TIM_Cmd();
	*�߱�д�жϷ�������TIMx_IRQHandler();
	*������жϱ�־λ��
	****************************************************************************************
	*CK_INT��APB1���õķ�Ƶ����Ϊ1��2��ʱ����72MHz����������ʱ�ӻ�Ҫ����PSC��Ƶ������0-65536��
	*���Ҫ�ı�PWM����Ƶ�ʣ����������ֲ�����
	*�ٸ���Ԥ��Ƶ����ֵ���ı��������Ƶ�ʣ�
	*�ڼ�����Ƶ��һ��ʱ���ı�TIMx_ARR��ֵ��
	****************************************************************************************
	*��ʵ��Ϊ����PA1�ڲ���PA6�����Ƶ��Ϊ1Hz��PWM�������峤��
	*/
	
#include "sys.h"
#include "usart.h"
#include "pwm.h"
#include "cap.h"
 
u32 temp;
u8  TIM2CH2_CAPTURE_STA;		//���벶��״̬		    				
u16	TIM2CH2_CAPTURE_VAL;	//���벶��ֵ	

 int main(void)
{		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	TIM3_CH1_pwm_init(9999,7199);//TIM3ʱ��Ϊ10000Hz�����ARRΪ10000����PWM��������Ϊ1s
 	TIM2_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ�����CRR�Ĵ���û����1�����ʱ����1us
	TIM_SetCompare1(TIM3,4999);//CRR�Ĵ�����λ��ҲΪ16���Ƚ�ֵ��0��65536�����ó�4999����ռ�ձ�Ϊ50%������ʱ��Ϊ0.5s��	
   	while(1)
	{	 		 
 		if(TIM2CH2_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp=TIM2CH2_CAPTURE_STA&0X3F;
			temp*=65536;//���ʱ���ܺ�
			temp+=TIM2CH2_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			printf("The time of pression is %d us\r\n",temp);//��usart.c�ļ��в鿴printf�ĵײ㺯��int fputc(int ch, FILE *f)�ͱ�������Ϊ������ģʽ
			TIM2CH2_CAPTURE_STA=0;//������һ�β���
		}
	}
}

 
//��ʱ��2�жϷ������	 
void TIM2_IRQHandler(void)
{ 

 	if((TIM2CH2_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	    
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM2CH2_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM2CH2_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM2CH2_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM2CH2_CAPTURE_VAL=0XFFFF;
				}
				else TIM2CH2_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//����1���������¼�
		{	
			if(TIM2CH2_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM2CH2_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				TIM2CH2_CAPTURE_VAL=TIM_GetCapture2(TIM2);//�˻�ȡ��ֵ�ļĴ���һ�����ܴ����������������ͨ������Ϊ���Ǽ���ֵ����Ҫ��Դ
		   	TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}
			else  								//��δ��ʼ,��һ�β���������
			{
				TIM2CH2_CAPTURE_STA=0;			//���
				TIM2CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM2CH2_CAPTURE_STA|=0X40;		//��ǲ�����������
		   	TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC2P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //����жϱ�־λ
}


