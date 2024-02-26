/*
 * flash_writer.c
 *
 *  Created on: 13 Dec 2023
 *      Author: dmart
 */

#include <stdio.h>
#include <stdbool.h>
#include "flash.h"
#include "flash_writer.h"

bool FLASH_WRITER_ClearData()
{
	return FLASH_EraseSector(SECTOR) == CMD_SUCCESS;
}

bool FLASH_WRITER_WriteData(void *srcAddr, unsigned int size)
{
	return FLASH_WriteData(SECTOR_ADDR, srcAddr, size) == CMD_SUCCESS;
}

bool FLASH_WRITER_VerifyData(void *srcAddr, unsigned int size)
{
	return FLASH_VerifyData(SECTOR_ADDR, srcAddr, size) == CMD_SUCCESS;
}
