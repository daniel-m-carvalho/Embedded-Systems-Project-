/*
 * rtc_hal.h
 *
 *  Created on: 2 Nov 2023
 *      Author: dmart
 */

#ifndef RTC_HAL_H_
#include <stdio.h>
#include <time.h>
#define RTC_HAL_H_

void RTC_HAL_init();

void RTC_HAL_getvalue(struct tm *dateTime);

void RTC_HAL_setvalue(struct tm *dateTime);

#endif /* RTC_HAL_H_ */
