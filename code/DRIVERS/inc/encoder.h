/*
 * res_handler.h
 *
 *  Created on: 22 Nov 2023
 *      Author: dmart
 */

#ifndef ENCODER_H_
#include <stdio.h>
#define ENCODER_H_

typedef enum ButtonEnum {
	BUTTON_NOTPRESSED, // Nao pressionado
	BUTTON_CLICKED, // Pressionado e libertado num intervalo de tempo curto
	BUTTON_DCLICKED // Pressionado e libertado num interval o de tempo curto duas vezes
} ENCODER_ButtonValueType;


/* Faz a iniciação do gestor . O parametro rate indica o ritmo a que gestor deve evoluir. */
void ENCODER_Init( int rate );

/* Devolve as variacoes do botao rotativo, de forma a detetar−se se a rotacao foi no sentid o horario (valores
	positivos) ou anti−horario ( valores negativos). */
int ENCODER_GetValue(void);

/* Devolve o estado do botão. */
ENCODER_ButtonValueType ENCODER_GetButton(void);

void ENCODER_Handler();

#endif /* ENCODER_H_ */
