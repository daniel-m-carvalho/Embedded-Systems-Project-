/*
 * delay.c
 *
 *  Created on: 4 Oct 2023
 */

#include <stdio.h>
#include <stdint.h>
#include "systick.h"
#include "LPC17xx.h"
#include "delay.h"
#include "timer.h"

#define SYSTICK_FREQ (SystemCoreClock / 1000)

int DELAY_Init(void)
{
	return SYSTICK_Init(SYSTICK_FREQ);
}

void DELAY_Milliseconds(uint32_t millis)
{
	uint32_t start = SYSTICK_GetValue();
	while ((SYSTICK_GetValue() - start) < millis)
	{
		__WFI();
	}
}

uint32_t DELAY_GetElapsedMillis(uint32_t start)
{
	return SYSTICK_GetValue() - start;
}

void DELAY_StopwatchInit ( void )
{
	TIMER_Init();
}

void DELAY_Stopwatch ( uint32_t waitUs )
{
	TIMER_WaitMicros(waitUs);
}
