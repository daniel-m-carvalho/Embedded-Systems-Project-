/*
 * res_handler.c
 *
 *  Created on: 7 Nov 2023
 *      Author: dmart
 */

#include <stdio.h>
#include <stdbool.h>
#include "rit.h"
#include "pin.h"
#include "delay.h"
#include "encoder.h"

#define ENCODER_SWITCH_MASK 0x180
#define ENCODER_SWITCH_STEP (1 << 0)
#define ENCODER_SWITCH_DIRECTION (1 << 1)
#define ENCODER_SWITCHES (ENCODER_SWITCH_STEP | ENCODER_SWITCH_DIRECTION)
#define ENCODER_BUTTON_BIT 9
#define ENCODER_BUTTONINTERVAL 1500 //1s
#define ENCODER_HOLD_TICKS 500	//0.5s
#define ENCODER_DCLICK_TICKS 1000  //1s

int keyDownTicks = 0;
int doubleClickTicks = 0;
ENCODER_ButtonValueType button = BUTTON_NOTPRESSED;
int lastButtonCheck = 0;
int delta =0;
int last = 0;

int ReadValues()
{
	int value = PIN_ReadValues(ENCODER_SWITCH_MASK, 7, ENCODER_BUTTON_BIT);
	switch(value)
	{
		case 1:
			return 1;
		case 2:
			return 3;
		default:
			return 2;
	}
}

void ENCODER_Handler()
{
	bool btn = !PIN_value(ENCODER_BUTTON_BIT);
	uint32_t now = DELAY_GetElapsedMillis(0);
	int current;
	uint32_t diff;
	RIT_Restart();
	current = ReadValues();
	diff = last - current;
	if (diff & ENCODER_SWITCH_STEP) {
		last = current;
		delta += (diff & ENCODER_SWITCH_DIRECTION) - 1;
	}
	if ((now - lastButtonCheck) >= ENCODER_BUTTONINTERVAL) {
		lastButtonCheck = now;
		if ((btn == true)) keyDownTicks++;
		else {
			if (keyDownTicks) {
				if (keyDownTicks > ENCODER_HOLD_TICKS)
					doubleClickTicks = 0;
				else {
					if (doubleClickTicks > 1) {
						if (doubleClickTicks < ENCODER_DCLICK_TICKS) {
							button = BUTTON_DCLICKED;
							doubleClickTicks = 0;
						}
					}
					else
						doubleClickTicks = ENCODER_DCLICK_TICKS;
				}
			}
			keyDownTicks = 0;
		}
		if (doubleClickTicks > 0) {
			doubleClickTicks -= 2;
			if (doubleClickTicks == 0) button = BUTTON_CLICKED;
		}
	}
}

void ENCODER_Init( int rate )
{
	RIT_SetHandler(rate, ENCODER_Handler);
	RIT_Start();
}



int ENCODER_GetValue()
{
	int value;
	value = delta;
	delta = 0;
	return value;
}
