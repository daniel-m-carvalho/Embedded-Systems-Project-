/*
 * systic.c
 *
 *  Created on: 4 Oct 2023
 *      Author: dmart
 */

#include <stdlib.h>
#include "LPC17xx.h"
#include "systick.h"


static volatile uint32_t __tick;

void SysTick_Handler(void)
{
	__tick++;
}

int SYSTICK_Init(uint32_t value)
{
	SystemCoreClockUpdate();
	if (SysTick_Config(value) == 1) return -1;
	return 0;
}

uint32_t SYSTICK_GetValue(void)
{
	return __tick;
}
