/*
 * project.h
 *
 *  Created on: 18 Dec 2023
 *      Author: dmart
 */

#ifndef PROJECT_H_
#include "lists.h"
#define PROJECT_H_

typedef struct{
	Card cards[128];
	Log logs[128];
}DataMem;

void PROJECT_Init();

void PROJECT_Start();

void PROJECT_Deposit();

void PROJECT_Collect();

void PROJECT_Maintenance();

void PROJECT_CalendarAndClock();

void PROJECT_AddCard();

void PROJECT_RemoveCard();

void PROJECT_SeeLogs();

void PROJECT_UpdateFlash(Logs *logs, Cards *cards);
#endif /* PROJECT_H_ */
