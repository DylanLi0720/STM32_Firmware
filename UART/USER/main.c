/**�ٴ���ʱ��ʹ�ܣ�GPIOʱ��ʹ��:RCC_APB2PeriphClockCmd();
  *�ڴ��ڸ�λ:USART_DeInit(); ��һ�����Ǳ����
  *��GPIO�˿�ģʽ����:GPIO_Init(); ģʽ����ΪGPIO_Mode_AF_PP
  *�ܴ��ڲ�����ʼ����USART_Init();
  *�ݿ����жϲ��ҳ�ʼ��NVIC�������Ҫ�����жϲ���Ҫ������裩
  *   NVIC_Init();
  *   USART_ITConfig();
	*��ʹ�ܴ���:USART_Cmd();
	*�߱�д�жϴ�������USARTx_IRQHandler();
	*�മ�������շ���
	*	void USART_SendData();//�������ݵ����ڣ�DR
	* uint16_t USART_ReceiveData();//�������ݣ���DR��ȡ���ܵ�������
	*�ᴮ�ڴ���״̬��ȡ��
	*	FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);
	*	void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);
	*/


#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

uint16_t  temp = 0;

void USART1_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);//��GPIOʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//����ʱ��ʹ��
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;//�������������ȫ˫��ģʽ��
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//��GPIO�˿�ģʽ��ʼ��
	
	GPIO_InitStruct.GPIO_Mode =  GPIO_Mode_IN_FLOATING;//��������������������룺ȫ˫��ģʽ��
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
/**
	*�۴��ڲ�����ʼ��
	*/
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART1,&USART_InitStruct);
	
/**
  *�ܿ����жϲ��ҳ�ʼ��NVIC�������Ҫ�����жϲ���Ҫ������裩
  */
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//���ô����ж�����(���յ����ݽ����ж�)
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//�����ȼ�
	NVIC_Init(&NVIC_InitStruct);
	
	USART_Cmd(USART1,ENABLE);//��ʹ�ܴ���
}

/**
  *���жϴ�����
  */
void USART1_IRQHandler()//��ʱ��Ϊ��usart.c���ļ��Ѿ������жϺ���������ʱ�ᱨ���ظ����塣���Խ�SYSTEM�ļ��а�����usart.c�ļ�ɾȥ
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE))//����ֵΪ1�����ѽ��յ�����
	{
		temp = USART_ReceiveData(USART1);//��ȡ���յ�������
		USART_SendData(USART1,temp);//����temp���������
	}

}

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ����飨�ڶ���Ϊ��λ��ռ���ȼ�����λ��Ӧ���ȼ������������ж�λ��֮ǰʹ��
	USART1_Init();
	LED_Init();
	delay_init();
	while(1)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		delay_ms(1000);
	}
}


