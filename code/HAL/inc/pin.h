/*
 * pin.h
 *
 *  Created on: 4 Oct 2023
 *      Author: dmart
 */

#ifndef PIN_H_
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define PIN_H_

void PIN_dir(int pin);

void PIN_set(int pin);

void PIN_clear(int pin);

int PIN_isOn(int pin);

void PIN_write(uint8_t value, uint8_t mask);

bool PIN_value(int pin);

int PIN_ReadValues(uint16_t mask, int nrOfShifts, int pin);

#endif /* PIN_H_ */
