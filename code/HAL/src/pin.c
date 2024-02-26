/*
 * pin.c
 *
 *  Created on: 4 Oct 2023
 *      Author: dmart
 */

#include <stdio.h>
#include <stdbool.h>
#include "LPC17xx.h"
#include "pin.h"

LPC_GPIO_TypeDef *LPC_GPIO_MAP[] = { LPC_GPIO0, LPC_GPIO1, LPC_GPIO2, LPC_GPIO3, LPC_GPIO4 };


void PIN_dir(int pin)
{
	int index = pin / 32;
	int gpioPin = pin % 32;

	LPC_GPIO_MAP[index]->FIODIR |= 1 << gpioPin;
}

void PIN_set(int pin)
{
	int index = pin / 32;
	int gpioPin = pin % 32;

	LPC_GPIO_MAP[index]->FIOSET = 1 << gpioPin;
}

void PIN_clear(int pin)
{
	int index = pin / 32;
	int gpioPin = pin % 32;

	LPC_GPIO_MAP[index]->FIOCLR = 1 << gpioPin;
}

int PIN_isOn(int pin)
{
	int index = pin / 32;
	int gpioPin = pin % 32;

	return LPC_GPIO_MAP[index]->FIOSET & (1 << gpioPin);
}

void PIN_write(uint8_t value, uint8_t mask)
{
	LPC_GPIO2->FIOCLR = mask;
	LPC_GPIO2->FIOSET = value & mask;
}

bool PIN_value(int pin)
{
	return PIN_isOn(pin) != 0;
}

int PIN_ReadValues(uint16_t mask, int nrOfShifts, int pin)
{
	int index = pin / 32;
	return (LPC_GPIO_MAP[index]->FIOPIN &~ mask) >> nrOfShifts;
}
