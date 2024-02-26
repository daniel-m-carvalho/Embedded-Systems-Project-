/*
 * systic.h
 *
 *  Created on: 4 Oct 2023
 *      Author: dmart
 */

#ifndef SYSTICK_H_
#include <stdio.h>
#include <stdint.h>
#define SYSTICK_H_

/**
* @brief Initialises the systick API for 1 ms resolution.
* @return 0 if initialisation successed; -1 if fails.
* @note This function must be called prior to any other SYSTICK
* functions, and use the SYSTICK resource.
*/
int SYSTICK_Init ( uint32_t value );

/**
* @brief Get current value of ticks
* @return Returns the current tick value in milliseconds.
*/
uint32_t SYSTICK_GetValue ( void ) ;

#endif /* SYSTICK_H_ */
