/*
 * rit_hal.h
 *
 *  Created on: 7 Nov 2023
 *      Author: dmart
 */

#ifndef RIT_H_
#include <stdio.h>
#include <stdbool.h>
#define RIT_H_

typedef void (*RIT_HandlerType)(void);

void RIT_SetHandler(int rateMillis, RIT_HandlerType handler);

bool RIT_Start();

void RIT_Stop();

void RIT_Restart();


#endif /* RIT_H_ */
