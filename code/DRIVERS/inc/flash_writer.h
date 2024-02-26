/*
 * flash_writer.h
 *
 *  Created on: 6 Dec 2023
 *      Author: dmart
 */

#ifndef FLASH_WRITER_H_
#include <stdbool.h>
#define FLASH_WRITER_H_

#define SECTOR_ADDR 0x78000

bool FLASH_WRITER_ClearData();

bool FLASH_WRITER_WriteData(void *srcAddr, unsigned int size);

bool FLASH_WRITER_VerifyData(void *srcAddr, unsigned int size);

#endif /* FLASH_WRITER_H_ */
