/**
 * @file lcd.h
 * @brief Header File for LCD driver
 * @details This file contains the declarations and macros for the LCD driver.
 * @version 1.0
 * @date 2024-06-20
 * @author Mohamed Sayed
 */
#ifndef ATMEGA32_DRIVERS_LCD_H_
#define ATMEGA32_DRIVERS_LCD_H_

#include "..\..\std_types.h"
#include "..\..\common_macros.h"
#include "..\..\MCAL\gpio\gpio.h"

/*******************************************************************************
 *                                CONFIGURATIONS                               *
 *******************************************************************************/

/**
 * @brief Select the communication mode for the LCD.
 *
 * Uncomment only one of the following definitions:
 * - `PARALLEL_8_BITS_FULL_PORT`
 * - `PARALLEL_8_BITS_RANDOM`
 * - `PARALLEL_4_BITS`
 * - `I2C`
 */
//#define PARALLEL_8_BITS_FULL_PORT
//#define PARALLEL_8_BITS_RANDOM
#define PARALLEL_4_BITS
//#define I2C

#if defined  (PARALLEL_8_BITS_FULL_PORT)

#define RS D0 /**< Register Select pin for full port mode */
#define E  D1 /**< Enable pin for full port mode */
#define DATA_PORT PORTC_ID /**< Data port for full port mode */

#elif defined (PARALLEL_8_BITS_RANDOM)
#define RS A1 /**< Register Select pin for random mode */
#define E  A2 /**< Enable pin for random mode */
#define DATA0 B2 /**< Data bit 0 pin for random mode */
#define DATA1 B1 /**< Data bit 1 pin for random mode */
#define DATA2 B0 /**< Data bit 2 pin for random mode */
#define DATA3 A7 /**< Data bit 3 pin for random mode */
#define DATA4 A3 /**< Data bit 4 pin for random mode */
#define DATA5 A4 /**< Data bit 5 pin for random mode */
#define DATA6 A5 /**< Data bit 6 pin for random mode */
#define DATA7 A6 /**< Data bit 7 pin for random mode */

#elif defined (PARALLEL_4_BITS)
#define RS A1 /**< Register Select pin for 4-bit mode */
#define E  A2 /**< Enable pin for 4-bit mode */
#define DATA4 A3 /**< Data bit 4 pin for 4-bit mode */
#define DATA5 A4 /**< Data bit 5 pin for 4-bit mode */
#define DATA6 A5 /**< Data bit 6 pin for 4-bit mode */
#define DATA7 A6 /**< Data bit 7 pin for 4-bit mode */

#elif defined (I2C)
/* I2C specific configurations can be added here */

#endif

/*******************************************************************************
 *                                COMMANDS                                     *
 *******************************************************************************/

/**
 * @brief Enum for LCD commands.
 */
typedef enum {
    LCD_COMMAND_CLEAR = 0x01, /**< Clear display command */
    LCD_COMMAND_RETURN_HOME = 0x02, /**< Return cursor to home position command */
    LCD_COMMAND_NO_SHIFT_RTL = 0b00000100, /**< Set cursor move direction to right-to-left without shifting display */
    LCD_COMMAND_NO_SHIFT_LTR = 0b00000110, /**< Set cursor move direction to left-to-right without shifting display */
    LCD_COMMAND_SHIFT_RTL = 0b00000101, /**< Set cursor move direction to right-to-left with shifting display */
    LCD_COMMAND_SHIFT_LTR = 0b00000111, /**< Set cursor move direction to left-to-right with shifting display */
    LCD_COMMAND_DISPLAY_ON = 0x0c, /**< Turn display on command */
    LCD_COMMAND_DISPLAY_OFF = 0x08, /**< Turn display off command */
    LCD_COMMAND_CURSOR_BLINKING = 0x0f, /**< Enable cursor blinking command */
    LCD_COMMAND_CURSOR_NO_BLINKING = 0x0E, /**< Disable cursor blinking command */
    LCD_COMMAND_SHIFT_SCREEN_LEFT = 0b00011000, /**< Shift entire display to the left command */
    LCD_COMMAND_SHIFT_SCREEN_RIGHT = 0b00011100, /**< Shift entire display to the right command */
    LCD_COMMAND_MOVE_CURSOR_LEFT = 0b00010000, /**< Move cursor one position to the left command */
    LCD_COMMAND_MOVE_CURSOR_RIGHT = 0b00010100, /**< Move cursor one position to the right command */
    LCD_COMMAND_8BIT_2Line_F0 = 0b00111000, /**< 8-bit mode, 2-line display, 5x8 dots */
    LCD_COMMAND_8BIT_1Line_F0 = 0b00110000, /**< 8-bit mode, 1-line display, 5x8 dots */
    LCD_COMMAND_8BIT_2Line_F1 = 0b00111100, /**< 8-bit mode, 2-line display, 5x10 dots */
    LCD_COMMAND_8BIT_1Line_F1 = 0b00110100, /**< 8-bit mode, 1-line display, 5x10 dots */
    LCD_COMMAND_4BIT_2Line_F0 = 0b00101000, /**< 4-bit mode, 2-line display, 5x8 dots */
    LCD_COMMAND_4BIT_1Line_F0 = 0b00100000, /**< 4-bit mode, 1-line display, 5x8 dots */
    LCD_COMMAND_4BIT_2Line_F1 = 0b00101100, /**< 4-bit mode, 2-line display, 5x10 dots */
    LCD_COMMAND_4BIT_1Line_F1 = 0b00100100, /**< 4-bit mode, 1-line display, 5x10 dots */
    LCD_COMMAND_4_BITS_MODE_INIT = 0x02, /**< Initialize 4-bit mode */
    LCD_COMMAND_SET_CURSOR_LOCATION = 0x80 /**< Set cursor location command */
} LCD_Commands;

/*******************************************************************************
 *                                FUNCTIONS PROTOTYPE                          *
 *******************************************************************************/

/**
 * @brief Struct for LCD operations.
 */
typedef struct {
    void (*init)(); /**< Pointer to the LCD initialization function */
    void (*sendCommand)(LCD_Commands); /**< Pointer to the function to send a command to the LCD */
    void (*displayCharacter)(uint8); /**< Pointer to the function to display a character on the LCD */
    void (*displayString)(char *); /**< Pointer to the function to display a string on the LCD */
    void (*moveCursor)(uint8, uint8); /**< Pointer to the function to move the cursor to a specific position */
    void (*displayInteger)(uint64); /**< Pointer to the function to display an integer on the LCD */
    void (*displayFloat)(float, uint8); /**< Pointer to the function to display a float on the LCD */
    void (*clear)(); /**< Pointer to the function to clear the LCD screen */
    void (*showCursor)(); /**< Pointer to the function to show the cursor */
    void (*on)(); /**< Pointer to the function to turn on the LCD */
    void (*off)(); /**< Pointer to the function to turn off the LCD */
} LCD;

/**
 * @brief Initialize the LCD.
 */
void LCD_init(void);

/**
 * @brief Send a command to the LCD.
 *
 * @param command The command to be sent to the LCD.
 */
void LCD_sendCommand(LCD_Commands command);

/**
 * @brief Display a character on the LCD.
 *
 * @param character The character to be displayed.
 */
void LCD_displayCharacter(uint8 character);

/**
 * @brief Display a string on the LCD.
 *
 * @param string Pointer to the string to be displayed.
 */
void LCD_displayString(char *string);

/**
 * @brief Move the cursor to a specific position.
 *
 * @param row The row number (0 or 1).
 * @param col The column number.
 */
void LCD_moveCursor(uint8 row, uint8 col);

/**
 * @brief Convert an integer to a string and display it on the LCD.
 *
 * @param data The integer to be displayed.
 */
void LCD_intgerToString(uint64 data);

/**
 * @brief Convert a float to a string and display it on the LCD.
 *
 * @param data The float to be displayed.
 * @param precision The number of decimal places to display.
 */
void LCD_floatToString(float data, uint8 percision);

/**
 * @brief Clear the LCD screen.
 */
void LCD_clearScreen(void);

/**
 * @brief Show the cursor on the LCD.
 */
void LCD_showCursor(void);

/**
 * @brief Turn on the LCD.
 */
void LCD_dispalyOn(void);

/**
 * @brief Turn off the LCD.
 */
void LCD_dispalyOff(void);

/**
 * @brief Macro to create a new LCD object with function pointers.
 */
#define NEWLCD() {LCD_init, LCD_sendCommand, LCD_displayCharacter, LCD_displayString, LCD_moveCursor, LCD_intgerToString, LCD_floatToString, LCD_clearScreen, LCD_showCursor, LCD_dispalyOn, LCD_dispalyOff}

#endif /* ATMEGA32_DRIVERS_LCD_H_ */
