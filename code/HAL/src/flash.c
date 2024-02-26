/*
 * flash.c
 *
 *  Created on: 5 Dec 2023
 *      Author: dmart
 */

#include <stdlib.h>
#include "LPC17xx.h"
#include "flash.h"

#define PREPARE_WRITE_CMD 50
#define COPY_CMD 51
#define ERASE_CMD 52
#define COMPARE_CMD 56
#define ARRAY_SIZE 5
#define DIV 1000
#define CPU_CCLK (SystemCoreClock/DIV)

int cmd[ARRAY_SIZE];
int result[ARRAY_SIZE];

FLASH_Function flash = 0x1FFF1FF1;

unsigned int FLASH_EraseSector (unsigned int sector )
{
	cmd[0] = PREPARE_WRITE_CMD;
	cmd[1] = sector;
	cmd[2] = sector;
	flash(cmd, result);
	if(result[0] == CMD_SUCCESS){
		cmd[0] = ERASE_CMD;
		cmd[1] = sector;
		cmd[2] = sector;
		cmd[3] = CPU_CCLK;
		flash(cmd, result);
	}
	return result[0];

}

unsigned int FLASH_WriteData(void *dstAddr , void *srcAddr , unsigned int size )
{
	cmd[0] = PREPARE_WRITE_CMD;
	cmd[1] = SECTOR;
	cmd[2] = SECTOR;
	flash(cmd, result);
	if(result[0] == CMD_SUCCESS){
		cmd[0] = COPY_CMD;
		cmd[1] = (int) dstAddr;
		cmd[2] = (int) srcAddr;
		cmd[3] = size;
		cmd[4] = CPU_CCLK;
		flash(cmd, result);
	}
	return result[0];

}
unsigned int FLASH_VerifyData(void *dstAddr , void *srcAddr , unsigned int size )
{
	cmd[0] = COMPARE_CMD;
	cmd[1] = (int)dstAddr;
	cmd[2] = (int)srcAddr;
	cmd[3] = size;
	flash(cmd, result);
	return result[0];
}
