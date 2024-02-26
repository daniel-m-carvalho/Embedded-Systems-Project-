/*
 * lists.h
 *
 *  Created on: 18 Dec 2023
 *      Author: dmart
 */

#ifndef LISTS_H_
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <mfrc522.h>
#define LISTS_H_



typedef void (*Operation)(void);

typedef enum State{
	DEPOSIT,
	COLLECT,
	INVALID
}StateType;

typedef struct {
	uint8_t	number[10];
}Card;

typedef struct {
	int size;
	Card *list;
}Cards;

typedef struct {
	StateType state;
	uint8_t depositCardNumber[10];
	uint8_t collectCardNumber[10];
	struct tm *date;
}Log;

typedef struct {
	int size;
	Log *list;
}Logs;

typedef struct {
	char *name;
	Operation operation;
}Maintenance;

void LISTS_AddCard(Cards *cards, Uid number);

void LISTS_RemoveCard(Card card, Cards *cards);

void LISTS_AddLog(Logs *logs, StateType state, uint8_t *depositCardNumber, uint8_t *collectCardNumber, struct tm *date);

bool LISTS_ConfirmCard(Log log, uint8_t *number);

bool LISTS_cardIsEqual(uint8_t *number1, uint8_t *number2);

void LISTS_CreateMaintenance(Maintenance *maintenance ,Operation *ops);

bool LISTS_CardExists(Cards *cards, uint8_t *number);

#endif /* LISTS_H_ */
