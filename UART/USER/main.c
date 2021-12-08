/**①串口时钟使能，GPIO时钟使能:RCC_APB2PeriphClockCmd();
  *②串口复位:USART_DeInit(); 这一步不是必须的
  *③GPIO端口模式设置:GPIO_Init(); 模式设置为GPIO_Mode_AF_PP
  *④串口参数初始化：USART_Init();
  *⑤开启中断并且初始化NVIC（如果需要开启中断才需要这个步骤）
  *   NVIC_Init();
  *   USART_ITConfig();
	*⑥使能串口:USART_Cmd();
	*⑦编写中断处理函数：USARTx_IRQHandler();
	*⑧串口数据收发：
	*	void USART_SendData();//发送数据到串口，DR
	* uint16_t USART_ReceiveData();//接受数据，从DR读取接受到的数据
	*⑨串口传输状态获取：
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
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);//①GPIO时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//串口时钟使能
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;//复用推挽输出（全双工模式）
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//②GPIO端口模式初始化
	
	GPIO_InitStruct.GPIO_Mode =  GPIO_Mode_IN_FLOATING;//（浮空输入或者上拉输入：全双工模式）
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
/**
	*③串口参数初始化
	*/
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART1,&USART_InitStruct);
	
/**
  *④开启中断并且初始化NVIC（如果需要开启中断才需要这个步骤）
  */
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//配置串口中断类型(接收到数据进入中断)
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//子优先级
	NVIC_Init(&NVIC_InitStruct);
	
	USART_Cmd(USART1,ENABLE);//⑤使能串口
}

/**
  *⑥中断处理函数
  */
void USART1_IRQHandler()//此时因为在usart.c的文件已经定义中断函数，编译时会报错重复定义。所以将SYSTEM文件夹包含的usart.c文件删去
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE))//返回值为1表明已接收到数据
	{
		temp = USART_ReceiveData(USART1);//读取接收到的数据
		USART_SendData(USART1,temp);//发送temp里面的数据
	}

}

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组（第二组为两位抢占优先级和两位响应优先级），必须在中断位置之前使用
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


