/*
 * spi.h
 *
 *  Created on: 12 Dec 2023
 *      Author: dmart
 */

#ifndef SPI_H_
#include <stdio.h>
#define SPI_H_

/* Faz a iniciação do control adore configura os respetivos pinos. */
void SPI_Init (void);

/* Configura o numero de bits de dados, o ritmo de envio/receção e o modo ( 0 , 1 , 2 ou 3). */
void SPI_ConfigTransfer ( int bitData , int frequency , int mode);

/* Realiza uma transferência , envia uma palavra e devolve a palavra recebida. */
unsigned short SPI_Transfer (unsigned short value );


#endif /* SPI_H_ */
