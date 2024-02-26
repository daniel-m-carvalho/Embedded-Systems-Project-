/*
 * lcd.c
 *
 *  Created on: 25 Oct 2023
 *      Author: dmart
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include "lcd.h"
#include "pin.h"
#include "delay.h"

#define ARRAY_SIZE(array) sizeof(array)* sizeof(array[0])
#define GPIO_DATA 64
#define GPIO_RS 68
#define GPIO_EN 69
#define LCD_DATA_MASK 0xf
#define CMD_DISPLAY_LENGHT 0x28
#define CMD_DISPLAY_ENTRY_MODE 0x06
#define CMD_DISPLAY_OFF 0x08
#define CMD_DISPLAY_ON 0x0F
#define CMD_DISPLAY_CLEAR 0x01
#define INIT_TIME 15000000
int row = 0;
int col = 0;

/** utilitary Functions*/
void resetCursor()
{
	row = 0;
	col = 0;
}

bool reachEndOfRow(int col){
	return col == 15;
}

void LCDText_Init (void)
{
	PIN_dir(GPIO_DATA);
	PIN_dir(GPIO_DATA+1);
	PIN_dir(GPIO_DATA+2);
	PIN_dir(GPIO_DATA+3);
	PIN_dir(GPIO_RS);
	PIN_dir(GPIO_EN);
	DELAY_Stopwatch(55000);//17
	LCDText_WriteNibble(false, 0x03);
	DELAY_Stopwatch(4100);//5
	LCDText_WriteNibble(false, 0x03);
	DELAY_Stopwatch(100);//1
	LCDText_WriteNibble(false, 0x03);
	DELAY_Stopwatch(37);//1
	LCDText_WriteNibble(false, 0x02);
	DELAY_Stopwatch(37);//1
	LCDText_WriteCMD(CMD_DISPLAY_LENGHT);//CMD_DISPLAY_LENGHT
	DELAY_Stopwatch(37);//1
	LCDText_WriteCMD(CMD_DISPLAY_OFF);//CMD_DISPLAY_OFF
	DELAY_Stopwatch(37);//1
	LCDText_WriteCMD(CMD_DISPLAY_CLEAR);//CMD_DISPLAY_CLEAR
	DELAY_Stopwatch(5000);//5000
	LCDText_WriteCMD(CMD_DISPLAY_ENTRY_MODE);//CMD_DISPLAY_ENTRY_MODE
	DELAY_Stopwatch(37);//1
	LCDText_WriteCMD(CMD_DISPLAY_ON);//CMD_DISPLAY_ON
	DELAY_Stopwatch(37*16*2 + 1520);//1
}

void LCDText_WriteChar(char ch)
{
	LCDText_WriteData(ch);
	DELAY_Stopwatch(37);
	switch(row)
	{
		case 0:
			if(reachEndOfRow(col))
			{
				LCDText_SetCursor(1, 0);
			}
			break;
		default:
			if(reachEndOfRow(col))
			{
				resetCursor();
				LCDText_SetCursor(row, col);
			}
			break;
	}
	col++;
}

void LCDText_WriteString (char * str)
{
	while(*str != '\0')
	{
		LCDText_WriteChar(*str);
		str++;
	}
}

void LCDText_SetCursor (int line , int column)
{
	LCDText_WriteCMD((line * 0x40 + column) | 0x80);
	DELAY_Stopwatch(37);
	col = column;
	row = line;
}

void LCDText_Clear(void)
{
	LCDText_WriteCMD(CMD_DISPLAY_CLEAR);
	DELAY_Stopwatch(5000);
	resetCursor();
}

static void LCDText_WriteNibble(bool rs, uint8_t data)
{
	if(rs)
	{
		PIN_set(GPIO_RS);
	}else
	{
		PIN_clear(GPIO_RS);
	}
	PIN_set(GPIO_EN);

	int gpioPin = GPIO_DATA % 32;

	uint8_t value = (data & 0xf)<< gpioPin;

	PIN_write(value, LCD_DATA_MASK);

	PIN_clear(GPIO_EN);
}

static void LCDText_WriteByte(bool rs, uint8_t value)
{
	LCDText_WriteNibble(rs, value >> 4);
	LCDText_WriteNibble(rs, value);
}

static void LCDText_WriteCMD(uint8_t data)
{
	LCDText_WriteByte(false, data);
}

static void LCDText_WriteData(uint8_t data)
{
	LCDText_WriteByte(true, data);
}

void LCDText_Printf (char *fmt, ...)
{
	char data[100];
	va_list ap;
	va_start(ap, fmt);
	vsprintf(data, fmt, ap);
	LCDText_WriteString(data);
	va_end(ap);
}

