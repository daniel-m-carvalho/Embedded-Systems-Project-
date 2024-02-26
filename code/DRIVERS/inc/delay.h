/*
 * delay.h
 *
 *  Created on: 4 Oct 2023
 *      Author: dmart
 */

#include <stdio.h>
#include <stdint.h>

#ifndef DELAY_H_
#define DELAY_H_

/*Faz a iniciação do temporizador para ter a resolução de 1ms */
int DELAY_Init ( void ) ;

/* Espera o número de milisegundos que são passados no pa râmetro millis */
void DELAY_Milliseconds ( uint32_t millis ) ;

/* Devolve, em milissegundos, adiferença do valor
 * passado em start para o tempo atual*/
uint32_t DELAY_GetElapsedMillis ( uint32_t start ) ;

/*Faz a iniciação do Timer0 para permitir uma resolução de microsegundos.*/
void DELAY_StopwatchInit ( void ) ;
/* Espera em microsegundos o valor passado no parâmetro.*/

void DELAY_Stopwatch ( uint32_t waitUs ) ;


#endif /* DELAY_H_ */
