/*
 * spi.c
 *
 *  Created on: 12 Dec 2023
 *      Author: dmart
 */


#include<stdio.h>
#include "LPC17xx.h"

#define PINSEL0_CONFIG_VALUE 0x3 << 30
#define PINSEL1_CONFIG_VALUE 0x3C
#define SPI_BIT 8
#define SPI_CONFIG_VALUE 0x20
#define BIT_DATA_AND_MODE_MASK 0xE7
#define BITDATA_BIT 8
#define MODE_BIT 0
#define SPI_STATUS_OK 0x80

void SPI_Init (void)
{
	LPC_PINCON->PINSEL0 |= PINSEL0_CONFIG_VALUE;
	LPC_PINCON->PINSEL1 |= PINSEL1_CONFIG_VALUE;
	LPC_SC->PCLKSEL1 &= ~(3 << 26);		//coloca  Peripheral clock selection for Repetitive Interrupt Timer a 00(CCLK/4) assim o clk no RIT Ã© 1 em cada milisegundo
	LPC_SC->PCONP |= 1 << SPI_BIT;
	LPC_SPI->SPCR = SPI_CONFIG_VALUE;
}


void SPI_ConfigTransfer ( int bitData , int frequency , int mode)
{
	LPC_SPI->SPCR &= BIT_DATA_AND_MODE_MASK;
	LPC_SPI->SPCR |= mode << MODE_BIT;
	LPC_SPI->SPCR |= bitData << BITDATA_BIT;
	LPC_SPI->SPCCR = (SystemCoreClock/frequency);
}

unsigned short SPI_Transfer (unsigned short value)
{
	LPC_SPI->SPDR = value;
	while((LPC_SPI->SPSR & SPI_STATUS_OK) == 0);
	return LPC_SPI->SPDR;
}
