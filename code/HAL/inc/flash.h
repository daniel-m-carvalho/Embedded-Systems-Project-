/*
 * flash.h
 *
 *  Created on: 2 Dec 2023
 *      Author: dmart
 */

#ifndef FLASH_H_
#include <stdio.h>
#define FLASH_H_

#define SECTOR 29

typedef void (*FLASH_Function)(int*, int*);
typedef enum StatusCode{
	CMD_SUCCESS,
	INVALID_COMMAND,
	SRC_ADDR_ERROR,
	DST_ADDR_ERROR,
	SRC_ADDR_NOT_MAPPED,
	DST_ADDR_NOT_MAPPED,
	COUNT_ERROR,
	INVALID_SECTOR,
	SECTOR_NOT_BLANK,
	SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION,
	COMPARE_ERROR,
	BUSY,
	PARAM_ERROR,
	ADDR_ERROR,
	ADDR_NOT_MAPPED,
	CMD_LOCKED,
	INVALID_CODE,
	INVALID_BAUD_RATE,
	INVALID_STOP_BIT,
	CODE_READ_PROTECTION_ENABLED
}FLASH_Status_Code;


/**
 *  Apaga o conteúdo de um sector.
 * */
unsigned int FLASH_EraseSector (unsigned int sector) ;

/**
 * Escreve o bloco de dados referenciado por srcAddr, de dimensão size bytes,
 * no endereço da flash referenciado por dstAddr.
 * */
unsigned int FLASH_WriteData(void *dstAddr , void *srcAddr , unsigned int size) ;

/**
 * Compara o conteúdo do bloco de dados referenciado por srcAddr, de dimensão size bytes , com o conteúdo do bloco
 * de dados referenciado por dstAddr .
 * */
unsigned int FLASH_VerifyData(void *dstAddr , void *srcAddr , unsigned int size) ;

#endif /* FLASH_H_ */
