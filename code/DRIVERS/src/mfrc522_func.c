/*
 * MFRC522.c
 *
 *  Created on: 12 Dec 2023
 *      Author: dmart
 */

#include<stdio.h>
#include"spi.h"
#include "pin.h"
#include "timer.h"
#include "delay.h"

#define FREQUENCY 8000000
#define BIT_DATA 8
#define MODE 3
#define RESET_PIN 71
#define CHIP_SELECT_PIN 70


/* Realiza as iniciações necessárias para a biblioteca (Configuração barramento e pinos). */
void MFRC522_PreInit(void)
{
	PIN_dir(RESET_PIN);
	PIN_dir(CHIP_SELECT_PIN);
	SPI_Init();
	SPI_ConfigTransfer(BIT_DATA, FREQUENCY, MODE);

}

/* Manipula o pino de reset do RC522 de acordo com o parâmetro. */
void MFRC522_Reset( bool assert )
{
	if(assert)
	{
		PIN_clear(RESET_PIN);
	}else
	{
		PIN_set(RESET_PIN);

	}
}

/* Manipula o pino de chip select do RC522 de acordo com o parâmetro. */
void MFRC522_Select( bool assert )
{
	if(assert)
	{
		PIN_clear(CHIP_SELECT_PIN);
	}else
	{
		PIN_set(CHIP_SELECT_PIN);
	}
}

/* Realiza a transmissão/receção de byte. */
uint8_t MFRC522_Transfer( uint8_t value )
{
	return SPI_Transfer(value);
}

/* Espera, em milissegundos, o valor do parâmetro. */
void MFRC522_WaitMs( uint32_t millis )
{
	DELAY_Milliseconds(millis);
}
