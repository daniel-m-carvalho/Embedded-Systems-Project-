/*
 * timer.c
 *
 *  Created on: 11 Oct 2023
 *      Author: dmart
 */
#include "LPC17xx.h"
#include "timer.h"

//LPC_TIM_TypeDef *LPC_TIM_MAP[] = { LPC_TIM0, LPC_TIM1, LPC_TIM2, LPC_TIM3};
#define TIMER0 LPC_TIM0
#define DIV 1000000
#define CLCK_DIV 4
#define TCR_RESET_BIT_POS 1
#define TCR_ENABLE_BIT_POS 0
#define IR_RESET_BIT_POS 0
#define IR_RESET_BIT_POS 0
#define MCR_INTERRUPT_BIT_POS 0
#define MCR_STOP_COUNTER_BIT_POS 2


void TIMER_Init()
{
	TIMER0->TCR = 1 << TCR_RESET_BIT_POS;
	LPC_SC->PCLKSEL0 &= ~(3 << 2);
	TIMER0->PR = ((SystemCoreClock/CLCK_DIV)/DIV) - 1;
	TIMER0->MCR = 1 << MCR_INTERRUPT_BIT_POS | 1 << MCR_STOP_COUNTER_BIT_POS;
}

void TIMER_WaitMicros(uint32_t waitUs)
{
	TIMER0->MR0 = waitUs;
	TIMER0->TCR = 1 << TCR_ENABLE_BIT_POS;
	while(TIMER0->IR != 1){}
	TIMER0->IR = 1 << IR_RESET_BIT_POS;
	TIMER0->TCR = 1 << TCR_RESET_BIT_POS;
}
