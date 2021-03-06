/**
	*OLED的IIC接法（使用stm32f103RBT6的IIC1）：
	*VCC->3.3V
	*GND->GND
	*SCL->PB6
	*SDA->PB7
	*********************************************************************************************
	*配置OLED用OLED_Init函数（调整亮度等等），但是GRAM里面依旧存在之前的数据，所以OLED_Clear可以清屏，
	*清屏之后OLED不亮
	*********************************************************************************************
	*OLED_CHinese:汉字是16*16的像素点组成，先显示完第一页（即从左到右显示完16个字节（OLED8位填满后会自增到第二列））再显示第二页
	*             前两个参数是坐标，后一个参数对应第几行的汉字。
	*OLED_ShowChar:字符有8*16和6*8两种规格，和汉字一样都是先显示第一页的8列再跳到第二页，6*8就不用跳
	*							 前两个是坐标，坐标中的x是0-127，y是0-7,如果是8*16的字符则是0-6.第三个参数是需要显示的字符的ASIIC值加上32
	*							 的一个整数常量，也可以直接输入字符，但必须加上单引号。第四个是字体规格，有16和6可以选，即对应8*16和6*8
	*OLED_DrawBMP：一维数组的形式，有起始点和终止点两个坐标参数
	*笔记：字符型就是整数
	*/

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "usart.h"


 int main(void)
  {	
		u8 t;
		delay_init();	    	 //延时函数初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始?
		OLED_Init();			//初始化OLED  
		OLED_Clear(); 
	while(1) 
	{		
		//OLED_Clear();
//		
//		OLED_ShowCHinese(108,0,6);//技
//		OLED_ShowString(72,0,"@EAGLE",16);
//		OLED_ShowString(6,3,"0.96' OLED TEST",16);
//		OLED_ShowString(8,2,"ZHONGJINGYUAN",16);  
//	 	OLED_ShowString(20,4,"2014/05/01",16);  
//		OLED_ShowString(0,6,"ASCII:",16);  
//		OLED_ShowString(63,6,"CODE:",16);  
//				OLED_ShowChar(48,0,'C',16);//前两个是坐标。第三个是输入的是ASIIC码加上空格的一个整型数，第四个是字体大小，有8*16和6*16的规格   
		OLED_DrawBMP(0,0,127,4,BMP1);
		OLED_ShowCHinese(0,6,0);  //我
		OLED_ShowCHinese(20,6,1);//爱
		OLED_ShowCHinese(40,6,2);//学
		OLED_ShowCHinese(60,6,3);//习
//		OLED_ShowCHinese(72,6,4);//子
//		OLED_ShowCHinese(90,6,5);//科
//		OLED_ShowChar(48,6,48,16);//前两个是坐标。第三个是输入的是ASIIC码加上空格的一个整型数，第四个是字体大小，有8*16和6*16的规格   
//		
//		if(t>'~')t=' ';
//		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
//			delay_ms(8000);
		delay_ms(10000);
	}	  
}

