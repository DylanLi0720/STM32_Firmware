#ifndef _KEY_H
#define _KEY_H
#include "stm32f10x.h"
#include "stdbool.h"

#define key  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)
void key_init(void);
bool key_scan(void);
#endif
