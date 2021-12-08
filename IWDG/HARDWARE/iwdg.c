#include "iwdg.h"
#include "stm32f10x.h"
#include "stdint.h"

void iwdg_init(uint8_t Prescaler,uint16_t Reload)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(Prescaler);
	IWDG_SetReload(Reload);
	IWDG_ReloadCounter();
	IWDG_Enable();
}

