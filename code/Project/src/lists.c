/*
 * lists.c
 *
 *  Created on: 18 Dec 2023
 *      Author: dmart
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "lists.h"

void LISTS_AddCard(Cards *cards, Uid number)
{
	int size = cards->size;
	Card new;
	for(int j = 0; j < number.size; j++){
		new.number[j] = number.uidByte[j];
	}
	Card newList[size + 1];
	for(int i = 0; i < size; i++){
		newList[i] = cards->list[i];
	}
	newList[size] = new;
	cards->list = newList;
	cards->size = size + 1;
}

void LISTS_RemoveCard(Card card, Cards *cards)
{
	int size = cards->size - 1;
	Card newList[size];
	int i = 0;
	int j = 0;
	while(i < size){
		if(!LISTS_cardIsEqual(card.number, cards->list[j].number)){
			newList[i] = cards->list[j];
			i++;
		}
		j++;
	}
	cards->list = newList;
	cards->size = size;
}

void LISTS_AddLog(Logs *logs, StateType state, uint8_t *depositCardNumber, uint8_t *collectCardNumber, struct tm *date)
{
	int size = logs->size;
	Log new;
	new.state = state;
	new.date = date;
	for(int j = 0; j < 10; j++){
		new.depositCardNumber[j] = depositCardNumber[j];
		new.collectCardNumber[j] = collectCardNumber[j];
	}
	Log newList[size + 1];
	for(int i = 0; i < size; i++){
		newList[i] = logs->list[i];
	}
	newList[size] = new;
	logs->list = newList;
	logs->size = size + 1;
}

bool LISTS_ConfirmCard(Log log, uint8_t *number)
{
	for(uint8_t i = 0; i < 10; i++){
		if (log.collectCardNumber[i] != number[i]){
			return false;
		}
	}
	return true;
}

bool LISTS_cardIsEqual(uint8_t *number1, uint8_t *number2){
	for(uint8_t i = 0; i < 10; i++){
		if (number1[i] != number2[i]){
			return false;
		}
	}
	return true;
}

void LISTS_CreateMaintenance(Maintenance *maintenance ,Operation *ops){
	Maintenance first = {
		.name = "calendar",
		.operation = ops[0]
	};
	maintenance[0] = first;

	Maintenance second = {
		.name = "Add Card",
		.operation = ops[1]
	};
	maintenance[1] = second;

	Maintenance third = {
		.name = "Remove Card",
		.operation = ops[2]
	};
	maintenance[2] = third;

	Maintenance fourth = {
		.name = "See Logs",
		.operation = ops[3]
	};
	maintenance[3] = fourth;
}

bool LISTS_CardExists(Cards *cards, uint8_t *number){
	for(int i = 0; i < cards->size; i++ ){
		if(LISTS_cardIsEqual(number, cards->list[i].number)){
			return true;
		}
	}
	return false;
}
