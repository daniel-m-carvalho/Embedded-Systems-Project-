/*
 * timer.h
 *
 *  Created on: 11 Oct 2023
 *      Author: dmart
 */

#ifndef TIMER_H_
#include <stdio.h>
#define TIMER_H_

void TIMER_Init();

void TIMER_WaitMicros(uint32_t waitUs);

#endif /* TIMER_H_ */
