/*
 * project.c
 *
 *  Created on: 18 Dec 2023
 *      Author: dmart
 */


#include <stdio.h>
#include<stdbool.h>
#include "project.h"
#include "delay.h"
#include "encoder.h"
#include "lcd.h"
#include "led.h"
#include "rtc.h"
#include "mfrc522.h"
#include "lists.h"
#include "flash_writer.h"

struct tm date = {
      .tm_sec = 0,
      .tm_min = 33,
      .tm_hour = 22,
      .tm_mday = 20,
      .tm_mon = 12,
      .tm_year = 2023,
      .tm_wday = 4,
      .tm_yday = 354
};
struct tm *timePointer = &date;

Cards *cards;
int cardIndex = 0;

Logs *logs;
int logIndex = 0;

Operation ops[4] = {PROJECT_CalendarAndClock, PROJECT_AddCard, PROJECT_RemoveCard, PROJECT_SeeLogs};
Maintenance maintenance[4];
int maintenanceIndex = 0;

Uid puid;
int rotation = 0;
int pbutton = 0;
StateType state = DEPOSIT;

void PROJECT_Init()
{
	DELAY_Init();
	DELAY_StopwatchInit();
	LCDText_Init();
	ENCODER_Init(100);
	LED_Init(true);
	MFRC522_Init();
	RTC_Init(0);
	RTC_SetValue(timePointer);
	LISTS_CreateMaintenance(maintenance, ops);
}

void PROJECT_Start()
{
	while(1){
		LCDText_Clear();
		RTC_GetValue(timePointer);
		LCDText_Printf("%d/%d/%d %d:%d",timePointer->tm_mday, timePointer->tm_mon, timePointer->tm_year, timePointer->tm_hour, timePointer->tm_min);
		if(state == 0){
			PROJECT_Deposit();
		}else if(state == 1){
			PROJECT_Collect();
		}
		if(pbutton == 2){
			PROJECT_Maintenance();
		}
	}
}

void PROJECT_Deposit()
{
	Card current = cards->list[cardIndex];
	while(1){
		LCDText_Clear();
		RTC_GetValue(timePointer);
		LCDText_Printf("%d/%d/%d %d:%d",timePointer->tm_mday, timePointer->tm_mon, timePointer->tm_year, timePointer->tm_hour, timePointer->tm_min);
		pbutton = ENCODER_GetButton();
		if(pbutton == 2) break;
		if (PICC_IsNewCardPresent()) {
			if (PICC_ReadCardSerial(&puid)) {
				LED_Toggle();
				while(1){
					LCDText_Clear();
					RTC_GetValue(timePointer);
					LCDText_Printf("%d/%d/%d %d:%d",timePointer->tm_mday, timePointer->tm_mon, timePointer->tm_year, timePointer->tm_hour, timePointer->tm_min);
					pbutton = ENCODER_GetButton();
					if(pbutton == 1){
						while(1){
							LCDText_Clear();
							LCDText_Printf("Card: ");
							for (uint8_t i = 0; i < puid.size; i++) {
								LCDText_Printf("%02X", current.number[i]);
							}
							rotation = ENCODER_GetValue();
							pbutton = ENCODER_GetButton();
							if(rotation < 0)
							{
								if((cardIndex - 1) < 0){
									cardIndex = cards->size - 1;
								}else cardIndex--;

								current = cards->list[cardIndex];
							}else if(rotation > 0)
							{
								if((cardIndex + 1) >= cards->size){
									cardIndex = 0;
								}else cardIndex++;

								current = cards->list[cardIndex];
							}
							if(pbutton == 1)
							{
								LISTS_AddLog(logs, state, puid.uidByte, current.number, timePointer);
								PROJECT_UpdateFlash(logs, cards);
								state = COLLECT;
								cardIndex = 0;
								break;
							}
						}
						break;
					}
				}
				LED_Toggle();
			}else continue;
			break;
		}else continue;
	}
}

void PROJECT_Collect()
{
	Log log = logs->list[logs->size - 1];
	while(1){
		LCDText_Clear();
		pbutton = ENCODER_GetButton();
		if(pbutton == 2) break;
		LCDText_Clear();
		RTC_GetValue(timePointer);
		LCDText_Printf("%d/%d/%d %d:%d",timePointer->tm_mday, timePointer->tm_mon, timePointer->tm_year, timePointer->tm_hour, timePointer->tm_min);
		if (PICC_IsNewCardPresent()) {
			if (PICC_ReadCardSerial(&puid)) {
				while(1){
					if(LISTS_ConfirmCard(logs->list[logs->size - 1], puid.uidByte))
					{
						LED_Toggle();
						LCDText_Clear();
						for (uint8_t i = 0; i < puid.size; i++) {
							LCDText_Printf("%02X", puid.uidByte[i]);
						}
						LISTS_AddLog(logs, state, log.depositCardNumber, puid.uidByte, timePointer);
						PROJECT_UpdateFlash(logs, cards);
						state = DEPOSIT;
						DELAY_Stopwatch(5000000);
						LED_Toggle();
						break;
					}else{
						LCDText_Clear();
						LCDText_WriteString("Card: ");
						for (uint8_t i = 0; i < puid.size; i++) {
							LCDText_Printf("%02X", puid.uidByte[i]);
						}
						LCDText_SetCursor(1,0);
						LCDText_WriteString("Not authorized");
						DELAY_Stopwatch(5000000);
						break;
					}
				}
			}else continue;
			break;
		}else continue;
	}
}

void PROJECT_Maintenance()
{
	uint32_t start =  DELAY_GetElapsedMillis(0); //pega o tempo atual do contador
	Maintenance currentmaintenanceOp = maintenance[maintenanceIndex];
	while(1){
	       rotation = ENCODER_GetValue();
	       pbutton = ENCODER_GetButton();
	       if(rotation < 0){
	    	   if((maintenanceIndex - 1) < 0){
	    		   maintenanceIndex = 3;
	    	   }else maintenanceIndex--;

	           currentmaintenanceOp = maintenance[maintenanceIndex];
	           start += DELAY_GetElapsedMillis(start); //atualiza o start para o tempo atual
	       }else if(rotation > 0)
	       {
	    	   if((maintenanceIndex + 1) >= 4){
	    		   maintenanceIndex = 0;
	    	   }else maintenanceIndex++;

	           currentmaintenanceOp = maintenance[maintenanceIndex];
	           start += DELAY_GetElapsedMillis(start); //atualiza o start para o tempo atual
	       }
	       LCDText_Clear();
	       LCDText_WriteString(currentmaintenanceOp.name);
	       if(pbutton == 1){
	           currentmaintenanceOp.operation();
	           LCDText_Clear();
	           start += DELAY_GetElapsedMillis(start); //atualiza o start para o tempo atual
	       }
	       if(DELAY_GetElapsedMillis(start)>=5000) break; //se passar 5s sem se tocar no button a app volta para o modo normal
	}
}

void PROJECT_CalendarAndClock()
{
	int currentPositionInPointer =0;
	int endPositionInPointer = 8;
	LCDText_Printf("tm_sec:");
	LCDText_SetCursor(1,0);
	LCDText_Printf("  %d  ",date.tm_sec);
	int currentElement = date.tm_sec;
	while(1){
		rotation = ENCODER_GetValue();
		pbutton = ENCODER_GetButton();
		if(rotation > 0){
			LCDText_Clear();
			LCDText_Printf("press to proceed");
			switch(currentPositionInPointer){
				case 0:{
					if(currentElement>=59){currentElement = 0;}else {currentElement+=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_sec:%d  ",date.tm_sec);
				}
				case 1:{
					if(currentElement>=59){currentElement = 0;}else {currentElement+=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_min:%d  ",date.tm_min);
				}
				case 2:{
					if(currentElement>=23){currentElement = 0;}else {currentElement+=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_hour:%d  ",date.tm_hour);
				}
				case 3:{
					if(currentElement>=31){currentElement = 1;}else {currentElement+=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_mday:%d  ",date.tm_mday);
				}
				case 4:{
					if(currentElement>=11){currentElement = 0;}else {currentElement+=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_mon:%d  ",date.tm_mon);
				}
				case 5:{
					if(currentElement>=4091){currentElement = 0;}else {currentElement+=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_year:%d  ",date.tm_year);
				}
				case 6:{
					if(currentElement>=6){currentElement = 0;}else {currentElement+=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_wday:%d  ",date.tm_wday);
				}
				case 7:{
					if(currentElement>=365){currentElement = 0;}else {currentElement+=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_yday:%d  ",date.tm_yday);
				}
				case 8:{
					if(currentElement>=1){currentElement = -1;}else {currentElement+=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_isdst:%d  ",date.tm_isdst);
				}
				default:{
					LCDText_Printf("impossible Position");
				}

			}

		}else if(rotation < 0){
			LCDText_Clear();
			LCDText_Printf("press to proceed");
			switch(currentPositionInPointer){
				case 0:{
					if(currentElement<=0){currentElement = 59;}else {currentElement-=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_sec:%d  ",date.tm_sec);
				}
				case 1:{
					if(currentElement<=0){currentElement = 59;}else {currentElement-=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_min:%d  ",date.tm_min);
				}
				case 2:{
					if(currentElement<=0){currentElement = 23;}else {currentElement-=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_hour:%d  ",date.tm_hour);
				}
				case 3:{
					if(currentElement<=1){currentElement = 31;}else {currentElement-=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_mday:%d  ",date.tm_mday);
				}
				case 4:{
					if(currentElement<=0){currentElement = 11;}else {currentElement-=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_mon:%d  ",date.tm_mon);
				}
				case 5:{
					if(currentElement<=0){currentElement = 4091;}else {currentElement-=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_year:%d  ",date.tm_year);
				}
				case 6:{
					if(currentElement<=0){currentElement = 6;}else {currentElement-=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_wday:%d  ",date.tm_wday);
				}
				case 7:{
					if(currentElement<=0){currentElement = 365;}else {currentElement-=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_yday:%d  ",date.tm_yday);
				}
				case 8:{
					if(currentElement<=-1){currentElement = 1;}else {currentElement-=1; }
					LCDText_SetCursor(1,0);
					LCDText_Printf("tm_isdst:%d  ",date.tm_isdst);
				}
				default:{
					LCDText_Printf("impossible Position");
				}

			}
		}
		if(pbutton == 1){
			switch(currentPositionInPointer){
				case 0:{
					date.tm_sec = currentElement;
					currentElement = date.tm_min;
				}
				case 1:{
					date.tm_min = currentElement;
					currentElement = date.tm_hour;
				}
				case 2:{
					date.tm_hour = currentElement;
					currentElement = date.tm_mday;
				}
				case 3:{
					date.tm_mday = currentElement;
					currentElement = date.tm_mon;
				}
				case 4:{
					date.tm_mon = currentElement;
					currentElement = date.tm_year;
				}
				case 5:{
					date.tm_year = currentElement;
					currentElement = date.tm_wday;
				}
				case 6:{
					date.tm_wday = currentElement;
					currentElement = date.tm_yday;
				}
				case 7:{
					date.tm_yday = currentElement;
					currentElement = date.tm_isdst;
				}
				case 8:{
					date.tm_isdst = currentElement;
					RTC_SetValue(&date);
				}
				default:{
					LCDText_Printf("impossible Position");
				}

			}
			if(currentPositionInPointer >=endPositionInPointer) {break;} else {currentPositionInPointer += 1;}
		}
	}
}

void PROJECT_AddCard()
{
	while (1) {
		if (PICC_IsNewCardPresent()) {
			if (PICC_ReadCardSerial(&puid)) {
				while(1){
					if(!LISTS_CardExists(cards, puid.uidByte))
					{
						LCDText_Clear();
						for (uint8_t i = 0; i < puid.size; i++) {
							LCDText_Printf("%02X", puid.uidByte[i]);
						}
						DELAY_Stopwatch(1000000);
						LCDText_Clear();
						LCDText_WriteString("Press to confirm");
						pbutton = ENCODER_GetButton();
						DELAY_Stopwatch(1000000);
						LCDText_Clear();
						if(pbutton == 1){
							LISTS_AddCard(cards, puid);
							break;
						}
					}
					break;
				}
				if(pbutton == 1){break;}
			}else continue;
		}else continue;
	}
}

void PROJECT_RemoveCard()
{
	Card current = cards->list[cardIndex];
	while(1){
		LCDText_Clear();
		LCDText_Printf("Card: ");
		for (uint8_t i = 0; i < puid.size; i++) {
			LCDText_Printf("%02X", current.number[i]);
		}
		rotation = ENCODER_GetValue();
		pbutton = ENCODER_GetButton();
		if(rotation < 0)
		{
			if((cardIndex - 1) < 0){
				cardIndex = cards->size - 1;
			}else cardIndex--;

			current = cards->list[cardIndex];
		}else if(rotation > 0)
		{
			if((cardIndex + 1) >= cards->size){
				cardIndex = 0;
			}else cardIndex++;

			current = cards->list[cardIndex];
		}
		if(pbutton == 1)
		{
			LISTS_RemoveCard(current, cards);
			cardIndex = 0;
			break;
		}
	}
}


void PROJECT_SeeLogs()
{
	Log current = logs->list[logIndex];
	while(1){
		LCDText_Clear();
		LCDText_Printf("State: ");
		if(current.state == 0){
			LCDText_Printf("Deposite");
		}else LCDText_Printf("Collect");
		DELAY_Stopwatch(1000000);
		LCDText_Clear();
		LCDText_Printf("Deposit card: ");
		LCDText_SetCursor(1,0);
		for (uint8_t i = 0; i < 10; i++) {
			LCDText_Printf("%02X", current.depositCardNumber[i]);
		}
		DELAY_Stopwatch(1000000);
		LCDText_Clear();
		LCDText_Printf("Collect card: ");
		LCDText_SetCursor(1,0);
		for (uint8_t i = 0; i < 10; i++) {
			LCDText_Printf("%02X", current.collectCardNumber[i]);
		}
		DELAY_Stopwatch(1000000);
		LCDText_Clear();
		LCDText_Printf("%d/%d/%d %d:%d",current.date->tm_mday, current.date->tm_mon, current.date->tm_year, current.date->tm_hour, current.date->tm_min);
		rotation = ENCODER_GetValue();
		pbutton = ENCODER_GetButton();
		if(rotation < 0)
		{
			if((logIndex - 1) < 0){
				logIndex = logs->size - 1;
			}else logIndex--;

			current = logs->list[logIndex];
		}else if(rotation > 0)
		{
			if((logIndex + 1) >= logs->size){
				logIndex = 0;
			}else logIndex++;

			current = logs->list[logIndex];
		}
		if(pbutton == 1)
		{
			logIndex = 0;
			break;
		}
	}
}

void PROJECT_UpdateFlash(Logs *logs, Cards *cards)
{

}
