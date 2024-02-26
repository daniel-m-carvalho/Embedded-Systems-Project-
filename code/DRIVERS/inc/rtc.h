/*
 * rtc.h
 *
 *  Created on: 1 Nov 2023
 *      Author: dmart
 */

#ifndef RTC_H_
#include <stdio.h>
#include <time.h>
#define RTC_H_

/* Faz a iniciação do RTC. O RTC é iniciado com o valor do parâmetro seconds, que representa os segundos desde 00:00:00 UTC de 1 janeiro 1970. */
void RTC_Init( time_t seconds ) ;

/* Devolve em dateTime o valor corrente do RTC. */
void RTC_GetValue( struct tm *dateTime ) ;

/* Realiza a atualização do RTC com os valores do parâmetro dateTime. */
void RTC_SetValue( struct tm * dateTime ) ;

/* Realiza a atualização do RTC com o valor do parâmetro seconds, que representa os segundos desde 00:00:00 UTC de 1 janeiro 1970. */
void RTC_SetSeconds( time_t seconds ) ;

/* Retorna o valor corrente do RTC, em segundos desde 00:00:00 UTC de 1 janeiro 1970. */
time_t RTC_GetSeconds() ;

char *RTC_WdayToDtring(int wday);

#endif /* RTC_H_ */
