/*
 * rit.c
 *
 *  Created on: 7 Nov 2023
 *      Author: dmart
 */


#include <stdio.h>
#include "LPC17xx.h"
#include "rit.h"

#define RIT_BIT 16
#define RIT_CTRL_ENABLE 3
#define RIT_CTRL_ENABLE_DEBUG 2
#define RIT_CTRL_ENABLE_CLEAR 1

static RIT_HandlerType ritHandler;

void RIT_SetHandler(int rateMillis, RIT_HandlerType handler)
{
	//LPC_SC->CCLKCFG = 249;			//divide o pllo por 250 para produzir o cclk (11111001)
	LPC_SC->PCLKSEL1 &= ~(3 << 26);		//coloca  Peripheral clock selection for Repetitive Interrupt Timer a 00(CCLK/4) assim o clk no RIT Ã© 1 em cada milisegundo

	LPC_SC->PCONP |= 1 << RIT_BIT;		//Repetitive Interrupt Timer power/clock control bit
	LPC_RIT->RIMASK = 0;				//A one written to any bit overrides the result of the comparison for the corresponding bit of the counter and compare register(causes the comparison of the register bits to be always true)
	LPC_RIT->RICOUNTER = 0;				//valor atual do contador
	LPC_RIT->RICTRL |= 1 << RIT_CTRL_ENABLE;
	LPC_RIT->RICTRL |= 1<< RIT_CTRL_ENABLE_DEBUG;
	LPC_RIT->RICOMPVAL = ((SystemCoreClock/1000) * rateMillis) -1;
	//LPC_SC->CLKSRCSEL = 0 << 2;
	ritHandler = handler;
}

void RIT_IRQHandler(void)
{
	if (ritHandler != 0) {
		ritHandler();
	}
	else {
		while(1) {}
	}
}

bool RIT_Start(void)
{
	if (ritHandler != 0) {
		NVIC_EnableIRQ(RIT_IRQn);
		LPC_RIT->RICTRL |= RIT_CTRL_ENABLE_CLEAR;
	}
	return ritHandler != 0;
}

void RIT_Stop(void)
{
	LPC_RIT->RICTRL &= ~RIT_CTRL_ENABLE_CLEAR;
	NVIC_DisableIRQ(RIT_IRQn);
}

void RIT_Restart(void)
{
	LPC_RIT->RICTRL |= RIT_CTRL_ENABLE_CLEAR;
}
