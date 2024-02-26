/*
 * lcd.h
 *
 *  Created on: 25 Oct 2023
 *      Author: dmart
 */

#ifndef LCD_H_
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#define LCD_H_

/* Faz a iniciação do sistema para permitir o acesso ao periférico LCD, utilizando 2 linhas de 16 colunas e
interface a 4 bits. */
void LCDText_Init () ;

/* Escreve um caracter na posição corrente do cursor. */
void LCDText_WriteChar(char ch);

/* Escreve uma string na posição corrente do cursor. */
void LCDText_WriteString (char * str);

/* Posiciona o cursor na linha row e coluna column do mostrador */
void LCDText_SetCursor (int line , int column);

/* Limpa o vi s o r , usando o comando dispon í vel na API do p e r i f é ri c o . */
void LCDText_Clear();

/* Opcional : Escreve na posição corrente do cursor a string fmt .
O formato da string fmt é idêntico à função printf da biblioteca standard da linguagem C. */
void LCDText_Printf (char *fmt , ...);

static void LCDText_WriteNibble(bool rs, uint8_t data);

static void LCDText_WriteByte(bool rs, uint8_t value);

static void LCDText_WriteCMD(uint8_t data);

static void LCDText_WriteData(uint8_t data);

#endif /* LCD_H_ */
