 #include "gpio_config.h" 
 #include "sys.h"

void LED_GPIOD_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PC端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//选择对应的引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}
