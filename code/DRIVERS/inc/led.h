/*
 * led.h
 *
 *  Created on: 4 Oct 2023
 *      Author: dmart
 */

#ifndef LED_H_
#include <stdio.h>
#include <stdbool.h>
#define LED_H_

/*Faz a iniciação do sistema para permitir a manipulação do estado LED disponível
 * na placa de prototipagem LPCXpresso LPC1769.
 * Com o parâmetro state igual a false o LED fica apagado após a iniciação .
 * Caso contrario está aceso.*/
void LED_Init ( bool state ) ;

/* Devolve true se o LED está aceso e false se o LED está apagado*/
bool LED_GetState ( void ) ;

/* Acende o LED.*/
void LED_On ( void ) ;

/* Apaga o LED.*/
void LED_Off ( void ) ;

/*Troca o estado do LED. Se estiver aceso apaga o LED, caso contrario acende o LED.*/
void LED_Toggle ( void ) ;

#endif /* LED_H_ */
