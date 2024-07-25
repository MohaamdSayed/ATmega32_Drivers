/**
 * @file lcd.c
 * @brief Source File for LCD driver
 * @details This file contains the implementation of the functions for the LCD driver.
 * @version 1.0
 * @date 2024-06-20
 * @author Mohamed Sayed
 */

#include "lcd.h"
#include "../../delay.h"
#include <stdlib.h>

/**
 * @defgroup Parallel8BitsFullPort Parallel 8 Bits Full Port Mode
 * @brief Functions and configurations for the parallel 8 bits full port mode
 * @{
 */

#if defined  (PARALLEL_8_BITS_FULL_PORT)

/**
 * @brief Send a command to the LCD in parallel 8 bits full port mode.
 *
 * @param command The command to be sent to the LCD.
 */
static void send(uint8 command) {
    delay_ms(1);
    GPIO_writePin(E, LOGIC_HIGH);
    delay_ms(1);
    GPIO_writePort(DATA_PORT, command);
    delay_ms(1);
    GPIO_writePin(E, LOGIC_LOW);
    delay_ms(1);
}

/**
 * @brief Initialize the LCD in parallel 8 bits full port mode.
 */
void LCD_init(void) {
    GPIO_setupPinDirection(RS, PIN_OUTPUT);
    GPIO_setupPinDirection(E, PIN_OUTPUT);
    GPIO_setupPortDirection(DATA_PORT, PORT_OUTPUT);
    delay_ms(20);
    LCD_sendCommand(LCD_COMMAND_8BIT_2Line_F1);
    LCD_sendCommand(LCD_COMMAND_DISPLAY_ON);
    LCD_sendCommand(LCD_COMMAND_CLEAR);
}

#endif
/** @} */ // End of Parallel8BitsFullPort group
/**
 * @defgroup Parallel8BitsRandom Parallel 8 Bits Random Mode
 * @brief Functions and configurations for the parallel 8 bits random mode
 * @{
 */

#if defined (PARALLEL_8_BITS_RANDOM)

/**
 * @brief Send a command to the LCD in parallel 8 bits random mode.
 *
 * @param command The command to be sent to the LCD.
 */
static void send(uint8 command) {
    delay_ms(1);
    GPIO_writePin(E, LOGIC_HIGH);
    delay_ms(1);

    GPIO_writePin(DATA0, GET_BIT(command, 0));
    GPIO_writePin(DATA1, GET_BIT(command, 1));
    GPIO_writePin(DATA2, GET_BIT(command, 2));
    GPIO_writePin(DATA3, GET_BIT(command, 3));
    GPIO_writePin(DATA4, GET_BIT(command, 4));
    GPIO_writePin(DATA5, GET_BIT(command, 5));
    GPIO_writePin(DATA6, GET_BIT(command, 6));
    GPIO_writePin(DATA7, GET_BIT(command, 7));

    delay_ms(1);
    GPIO_writePin(E, LOGIC_LOW);
    delay_ms(1);
}

/**
 * @brief Initialize the LCD in parallel 8 bits random mode.
 */
void LCD_init(void) {
    GPIO_setupPinDirection(RS, PIN_OUTPUT);
    GPIO_setupPinDirection(E, PIN_OUTPUT);

    GPIO_setupPinDirection(DATA0, PIN_OUTPUT);
    GPIO_setupPinDirection(DATA1, PIN_OUTPUT);
    GPIO_setupPinDirection(DATA2, PIN_OUTPUT);
    GPIO_setupPinDirection(DATA3, PIN_OUTPUT);
    GPIO_setupPinDirection(DATA4, PIN_OUTPUT);
    GPIO_setupPinDirection(DATA5, PIN_OUTPUT);
    GPIO_setupPinDirection(DATA6, PIN_OUTPUT);
    GPIO_setupPinDirection(DATA7, PIN_OUTPUT);

    delay_ms(20);
    LCD_sendCommand(LCD_COMMAND_8BIT_2Line_F1);
    LCD_sendCommand(LCD_COMMAND_DISPLAY_ON);
    LCD_sendCommand(LCD_COMMAND_CLEAR);
}

#endif
/** @} */ // End of Parallel8BitsRandom group
/**
 * @defgroup Parallel4Bits Parallel 4 Bits Mode
 * @brief Functions and configurations for the parallel 4 bits mode
 * @{
 */

#if defined (PARALLEL_4_BITS)

/**
 * @brief Send a command to the LCD in parallel 4 bits mode.
 *
 * @param command The command to be sent to the LCD.
 */
static void send(uint8 command) {
	delay_ms(1);
	GPIO_writePin(E, LOGIC_HIGH);
	delay_ms(1);
	GPIO_writePin(DATA4, GET_BIT(command, 4));
	GPIO_writePin(DATA5, GET_BIT(command, 5));
	GPIO_writePin(DATA6, GET_BIT(command, 6));
	GPIO_writePin(DATA7, GET_BIT(command, 7));

	delay_ms(1);
	GPIO_writePin(E, LOGIC_LOW);
	delay_ms(1);
	GPIO_writePin(E, LOGIC_HIGH);
	delay_ms(1);

	GPIO_writePin(DATA4, GET_BIT(command, 0));
	GPIO_writePin(DATA5, GET_BIT(command, 1));
	GPIO_writePin(DATA6, GET_BIT(command, 2));
	GPIO_writePin(DATA7, GET_BIT(command, 3));

	delay_ms(1);
	GPIO_writePin(E, LOGIC_LOW);
	delay_ms(1);
}

/**
 * @brief Initialize the LCD in parallel 4 bits mode.
 */
void LCD_init(void) {
	GPIO_setupPinDirection(RS, PIN_OUTPUT);
	GPIO_setupPinDirection(E, PIN_OUTPUT);
	delay_ms(20); /* LCD Power ON delay always > 15ms */
	GPIO_setupPinDirection(DATA4, PIN_OUTPUT);
	GPIO_setupPinDirection(DATA5, PIN_OUTPUT);
	GPIO_setupPinDirection(DATA6, PIN_OUTPUT);
	GPIO_setupPinDirection(DATA7, PIN_OUTPUT);
	delay_ms(20);
	LCD_sendCommand(LCD_COMMAND_RETURN_HOME);
	LCD_sendCommand(LCD_COMMAND_4BIT_2Line_F0);
	LCD_sendCommand(LCD_COMMAND_DISPLAY_ON); /* cursor off */
	LCD_sendCommand(LCD_COMMAND_CLEAR); /* clear LCD at the beginning */
}

#endif
/** @} */ // End of Parallel4Bits group
/**
 * @defgroup I2C I2C Mode
 * @brief Functions and configurations for the I2C mode
 * @{
 */

#if defined (I2C)
/* I2C specific implementations can be added here */
#endif
/** @} */ // End of I2C group
/**
 * @brief Send a command to the LCD.
 *
 * @param command The command to be sent to the LCD.
 */
void LCD_sendCommand(LCD_Commands command) {
	GPIO_writePin(RS, LOGIC_LOW);
	send(command);
}

/**
 * @brief Display a character on the LCD.
 *
 * @param character The character to be displayed.
 */
void LCD_displayCharacter(uint8 character) {
	GPIO_writePin(RS, LOGIC_HIGH);
	send(character);
}

/**
 * @brief Display a string on the LCD.
 *
 * @param string Pointer to the string to be displayed.
 */
void LCD_displayString(char *string) {

	uint8 index = 0;
	while (string[index]) {
		LCD_displayCharacter(string[index]);
		index++;
	}
}

/**
 * @brief Move the cursor to a specific position.
 *
 * @param row The row number (0 or 1).
 * @param col The column number.
 */
void LCD_moveCursor(uint8 row, uint8 col) {
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch (row) {
	case 0:
		lcd_memory_address = col;
		break;
	case 1:
		lcd_memory_address = col + 0x40;
		break;
	case 2:
		lcd_memory_address = col + 0x10;
		break;
	case 3:
		lcd_memory_address = col + 0x50;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_COMMAND_SET_CURSOR_LOCATION);
}

/**
 * @brief Convert an integer to a string and display it on the LCD.
 *
 * @param data The integer to be displayed.
 */
void LCD_intgerToString(uint64 data) {
	char buffer[10];
	ltoa(data, buffer, 10);
	LCD_displayString(buffer);
}

/**
 * @brief Convert a float to a string and display it on the LCD.
 *
 * @param data The float to be displayed.
 * @param percision The number of decimal places to display.
 */
void LCD_floatToString(float data, uint8 percision) {
	uint64 left, right, val;
	uint8 i = 1;
	val = 1;
	left = (uint64) data;
	for (i = 1; i <= percision; i++) {
		val *= 10;
	}
	right = (data - left) * val;
	LCD_intgerToString(left);
	LCD_displayCharacter('.');
	LCD_intgerToString(right);
}

/**
 * @brief Clear the LCD screen.
 */
void LCD_clearScreen(void) {
	LCD_sendCommand(LCD_COMMAND_CLEAR);
}

/**
 * @brief Show the cursor on the LCD.
 */
void LCD_showCursor(void) {
	LCD_sendCommand(LCD_COMMAND_CURSOR_BLINKING);
}

/**
 * @brief Turn off the LCD.
 */
void LCD_dispalyOff(void) {
	LCD_sendCommand(LCD_COMMAND_DISPLAY_OFF);
}

/**
 * @brief Turn on the LCD.
 */
void LCD_dispalyOn(void) {
	LCD_sendCommand(LCD_COMMAND_DISPLAY_ON);
}
