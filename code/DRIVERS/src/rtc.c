/*
 * rtc.c
 *
 *  Created on: 2 Nov 2023
 *      Author: dmart
 */

#include <stdio.h>
#include <time.h>
#include "rtc.h"
#include "rtc_hal.h"

void RTC_Init( time_t seconds )
{
	RTC_HAL_init();
	RTC_SetSeconds(seconds);
}

void RTC_GetValue( struct tm *dateTime )
{
	RTC_HAL_getvalue(dateTime);
}

void RTC_SetValue( struct tm *dateTime )
{
	RTC_HAL_setvalue(dateTime);
}

void RTC_SetSeconds( time_t seconds )
{
	struct tm *dateTime = localtime(&seconds);
	RTC_SetValue(dateTime);

}

time_t RTC_GetSeconds()
{
	struct tm *dateTime;
	RTC_GetValue(dateTime);
	return mktime(dateTime);
}

char *RTC_WdayToDtring(int wday)
{
	switch(wday)
	{
		case 0:
			return "DOMINGO";
		case 1:
			return "SEGUNDA";
		case 2:
			return "TERCA";
		case 3:
			return "QUARTA";
		case 4:
			return "QUINTA";
		case 5:
			return "SEXTA";
		case 6:
			return "SABADO";
	}
}
