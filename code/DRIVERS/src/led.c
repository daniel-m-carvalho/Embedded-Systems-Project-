/*
 * led.c
 *
 *  Created on: 4 Oct 2023
 *      Author: dmart
 */

#include <stdio.h>
#include <stdbool.h>
#include "pin.h"
#include "led.h"

#define PIN_0_22  22

void LED_Init ( bool state )
{
	PIN_dir(PIN_0_22);
	if(state)
	{
		LED_On();
	}else
	{
		LED_Off();
	}
}

bool LED_GetState ()
{
	return PIN_isOn(PIN_0_22) != 0;
}

void LED_On()
{
	PIN_set(PIN_0_22);
}

void LED_Off()
{
	PIN_clear(PIN_0_22);
}

void LED_Toggle ()
{
	if(LED_GetState())
	{
		LED_Off();
	}else
	{
		LED_On();
	}
}
