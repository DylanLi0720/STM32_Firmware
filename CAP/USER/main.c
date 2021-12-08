/**
	*①初始化定时器和通道对应IO的时钟。
	*②初始化IO口，模式为输入：GPIO_Init();
  *  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入
	*③初始化定时器ARR，PSC
	*	 TIM_TimeBaseInit();
	*④初始化输入捕获通道
  *  TIM_ICInit();
	*⑤如果要开启捕获中断，
  *  TIM_ITConfig();
  *  NVIC_Init();
	*⑥使能定时器：TIM_Cmd();
	*⑦编写中断服务函数：TIMx_IRQHandler();
	*⑧清除中断标志位。
	****************************************************************************************
	*CK_INT在APB1设置的分频因子为1和2的时候都是72MHz，计数器的时钟还要根据PSC分频而来（0-65536）
	*如果要改变PWM波的频率，有以下两种操作：
	*①更改预分频器的值，改变计数器的频率；
	*②计数器频率一定时，改变TIMx_ARR的值。
	****************************************************************************************
	*本实验为利用PA1口测量PA6口输出频率为1Hz的PWM波的脉冲长度
	*/
	
#include "sys.h"
#include "usart.h"
#include "pwm.h"
#include "cap.h"
 
u32 temp;
u8  TIM2CH2_CAPTURE_STA;		//输入捕获状态		    				
u16	TIM2CH2_CAPTURE_VAL;	//输入捕获值	

 int main(void)
{		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	TIM3_CH1_pwm_init(9999,7199);//TIM3时钟为10000Hz，结合ARR为10000，即PWM波的周期为1s
 	TIM2_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数，CRR寄存器没增加1所需的时间是1us
	TIM_SetCompare1(TIM3,4999);//CRR寄存器的位数也为16，比较值从0到65536（设置成4999，即占空比为50%，脉冲时间为0.5s）	
   	while(1)
	{	 		 
 		if(TIM2CH2_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
		{
			temp=TIM2CH2_CAPTURE_STA&0X3F;
			temp*=65536;//溢出时间总和
			temp+=TIM2CH2_CAPTURE_VAL;//得到总的高电平时间
			printf("The time of pression is %d us\r\n",temp);//在usart.c文件中查看printf的底层函数int fputc(int ch, FILE *f)和避免设置为半主机模式
			TIM2CH2_CAPTURE_STA=0;//开启下一次捕获
		}
	}
}

 
//定时器2中断服务程序	 
void TIM2_IRQHandler(void)
{ 

 	if((TIM2CH2_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	    
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM2CH2_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM2CH2_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM2CH2_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM2CH2_CAPTURE_VAL=0XFFFF;
				}
				else TIM2CH2_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//捕获1发生捕获事件
		{	
			if(TIM2CH2_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM2CH2_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM2CH2_CAPTURE_VAL=TIM_GetCapture2(TIM2);//此获取数值的寄存器一定不能错，很容易填成其他的通道，因为这是计数值的重要来源
		   	TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}
			else  								//还未开始,第一次捕获上升沿
			{
				TIM2CH2_CAPTURE_STA=0;			//清空
				TIM2CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM2CH2_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   	TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC2P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //清除中断标志位
}


