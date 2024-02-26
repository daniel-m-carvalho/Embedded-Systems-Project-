/*
 * rtc_hal.c
 *
 *  Created on: 2 Nov 2023
 *      Author: dmart
 */

#include <stdio.h>
#include <time.h>
#include "LPC17xx.h"
#include "rtc_hal.h"

#define SECONDS_MASK  0x3F
#define MINUTES_MASK  (SECONDS_MASK << 8)
#define HOURS_MASK	(0x1F << 16)
#define MDAYS_MASK	0x1F
#define MONTHS_MASK	(0xF << 8)
#define YEARS_MASK	(0xFFF << 16)
#define WDAYS_MASK	(0x7 << 24)
#define YDAYS_MASK	0xFFF

volatile uint32_t ctime0;
volatile uint32_t ctime1;
volatile uint32_t ctime2;

void RTC_HAL_init()
{
	LPC_RTC->CIIR = 1 << 7;
	LPC_RTC->RTC_AUXEN = 1 << 4;
	LPC_RTC->CCR = 1;
}

void RTC_HAL_getvalue(struct tm *dateTime)
{
	ctime0 = LPC_RTC->CTIME0;
	ctime1 = LPC_RTC->CTIME1;
	ctime2 = LPC_RTC->CTIME2;
	dateTime->tm_sec = ctime0 & SECONDS_MASK;
	dateTime->tm_min = (ctime0 & MINUTES_MASK)>>8;
	dateTime->tm_hour = (ctime0 & HOURS_MASK)>>16;
	dateTime->tm_wday = (ctime0 & WDAYS_MASK)>>24;
	dateTime->tm_mday = (ctime1 & MDAYS_MASK);
	dateTime->tm_mon = ((ctime1 & MONTHS_MASK)>>8) + 1;
	dateTime->tm_year = ((ctime1 & YEARS_MASK)>>16) - 1900;
	dateTime->tm_yday = (ctime2 & YDAYS_MASK) + 1;
}

void RTC_HAL_setvalue(struct tm *dateTime)
{
	LPC_RTC->CCR = 0;
	LPC_RTC->SEC = dateTime->tm_sec;
	LPC_RTC->MIN = dateTime->tm_min;
	LPC_RTC->HOUR = dateTime->tm_hour;
	LPC_RTC->DOM = dateTime->tm_mday;
	LPC_RTC->DOW = dateTime->tm_wday;
	LPC_RTC->DOY = dateTime->tm_yday - 1;
	LPC_RTC->MONTH = dateTime->tm_mon - 1;
	LPC_RTC->YEAR = dateTime->tm_year + 1900;
	LPC_RTC->CCR = 1;
}
