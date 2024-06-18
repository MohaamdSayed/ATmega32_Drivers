/******************************************************************************
 *
 * Module: HAL/KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header File for Keypad driver
 *
 * Author: Mohamed Sayed
 *
 *******************************************************************************/
#ifndef ATMEGA32_DRIVERS_KEYBAD_H_
#define ATMEGA32_DRIVERS_KEYBAD_H_
#include "..\..\std_types.h"
#include "..\..\common_macros.h"
#include "..\..\MCAL\gpio\gpio.h"
/*******************************************************************************
 *                                CONFIGURATIONS                               *
 *******************************************************************************/

#define KEYBAD4x4

#if defined(KEYBAD4x4)
#define ROW0 B4
#define ROW1 B5
#define ROW2 B6
#define ROW3 B7
#define COL0 D2
#define COL1 D3
#define COL2 D4
#define COL3 D5
#define NUM_OF_ROWS 4
#define NUM_OF_COLS 4
#define KEYPAD_BUTTON_PRESSED LOGIC_LOW
#define ROWS { ROW0, ROW1, ROW2, ROW3 }
#define COLS { COL0, COL1, COL2, COL3 }

#endif /* ATMEGA32_DRIVERS_KEYBAD_H_ */

#define CHARARRAY { 7, 8, 9, '/', 4, 5, 6, '*', 1, 2, 3, '-', 'c', 0,'=', '+'}

void KEYPAD_init(void);
uint8 KEYPAD_getKey();
#endif
