/******************************************************************************
 *
 * Module: HAL/KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source File for Keypad driver
 *
 * Author: Mohamed Sayed
 *
 *******************************************************************************/
#include "keypad.h"

#include "avr/delay.h"
uint8 rowsArray[] = ROWS;
uint8 colsArray[] = COLS;
static char charachters[] = CHARARRAY;

void KEYPAD_init() {
	int i;
	for (i = 0; i < NUM_OF_ROWS; i++) {
		GPIO_setupPinDirection(rowsArray[i], PIN_INPUT);
	}
	for (i = 0; i < NUM_OF_COLS; i++) {
		GPIO_setupPinDirection(colsArray[i], PIN_INPUT);
	}

}

uint8 KEYPAD_getKey() {
	uint8 row, col;
	KEYPAD_init();
	while (1) {
		for (row = 0; row < NUM_OF_ROWS; row++) {
			GPIO_setupPinDirection(rowsArray[row], PIN_OUTPUT);

			GPIO_writePin(rowsArray[row], LOGIC_LOW);
			for (col = 0; col < NUM_OF_COLS; col++) {

				if (GPIO_readPin(colsArray[col]) == LOGIC_LOW) {
					return charachters[NUM_OF_COLS * row + col];
				}

			}
			GPIO_setupPinDirection(rowsArray[row], PIN_INPUT);
			_delay_ms(5);
		}
	}
}

