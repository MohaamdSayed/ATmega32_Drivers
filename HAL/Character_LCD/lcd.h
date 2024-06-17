/******************************************************************************
 *
 * Module: HAL/LCD
 *
 * File Name: lcd.h
 *
 * Description: Header File for LCD driver
 *
 * Author: Mohamed Sayed
 *
 *******************************************************************************/

#ifndef MYDRIVERS_LCD_H_
#define MYDRIVERS_LCD_H_
#include "..\..\std_types.h"
#include "..\..\common_macros.h"
#include "..\..\MCAL\gpio\gpio.h"
/*******************************************************************************
 *                                CONFIGURATIONS                               *
 *******************************************************************************/

/*UNCOMMENT ONLY ON OF THE NEXT 3 DFINATIONS*/
//#define PARALLEL_8_BITS_FULL_PORT
//#define PARALLEL_8_BITS_RANDOM
#define PARALLEL_4_BITS
//#define I2C

#if defined  (PARALLEL_8_BITS_FULL_PORT)

/*Select the pins where you connected the lcd */
#define RS D0
#define E  D1
#define DATA_PORT PORTC_ID

#elif defined (PARALLEL_8_BITS_RANDOM)
#define RS A1
#define E  A2
#define DATA0 B2
#define DATA1 B1
#define DATA2 B0
#define DATA3 A7
#define DATA4 A3
#define DATA5 A4
#define DATA6 A5
#define DATA7 A6

#elif defined (PARALLEL_4_BITS)
#define RS A1
#define E  A2

#define DATA4 A3
#define DATA5 A4
#define DATA6 A5
#define DATA7 A6

#elif defined (I2C)




#endif

/*******************************************************************************
 *                                COMMANDS                                     *
 *******************************************************************************/

#define LCD_COMMAND_CLEAR               0x01
#define LCD_COMMAND_RETURN_HOME         0x02

/*ENTERY MODE COMMANDS	                0b000001DS */
#define LCD_COMMAND_NO_SHIFT_RTL        0b00000100
#define LCD_COMMAND_NO_SHIFT_LTR		0b00000110
#define LCD_COMMAND_SHIFT_RTL           0b00000101  //NOT WORKING
#define LCD_COMMAND_SHIFT_LTR           0b00000111

/*DISPLAY ON OFF           	            0b00001DCB */
#define LCD_COMMAND_DISPLAY_ON          0x0c /*DISPALY ON CURSOR OFF*/
#define LCD_COMMAND_DISPLAY_OFF		    0x08 /*DISPALY OFF CURSOR OFF*/
#define LCD_COMMAND_CURSOR_BLINKING     0x0f /*DISPALY ON CURSOR ON BLINKING ON*/
#define LCD_COMMAND_CURSOR_NO_BLINKING  0x0E /*DISPALY ON CURSOR ON  BLINKING OFF*/
#define LCD_COMMAND_CURSOR_OFF          0x0c

/*Cursor or dispaly Shift	            0b0001SRxx */
#define LCD_COMMAND_SHIFT_SCREEN_LEFT   0b00011000  /*SHIFT THE SCREEN TO THE LEFT*/
#define LCD_COMMAND_SHIFT_SCREEN_RIGHT  0b00011100  /*SHIFT THE SCREEN TO THE RIGHT*/
#define LCD_COMMAND_MOVE_CURSOR_LEFT    0b00010000   /*MOVE THE SCREEN TO THE LEFT*/
#define LCD_COMMAND_MOVE_CURSOR_RIGHT   0b00010100   /*MOVE THE SCREEN TO THE LEFT*/

/*FUNCTION SET           	            0b001DNFxx */
#define LCD_COMMAND_8BIT_2Line_F0       0b00111000  /* INITIALIZE THE SCREEN AS Parallel 8 BIT 2 line Font 5x8  */
#define LCD_COMMAND_8BIT_1Line_F0       0b00110000	/* INITIALIZE THE SCREEN AS Parallel 8 BIT 1 line Font 5x8  */
#define LCD_COMMAND_8BIT_2Line_F1       0b00111100	/* INITIALIZE THE SCREEN AS Parallel 8 BIT 2 line Font 5x11 */
#define LCD_COMMAND_8BIT_1Line_F1       0b00110100  /* INITIALIZE THE SCREEN AS Parallel 8 BIT 1 line Font 5x11 */
#define LCD_COMMAND_4BIT_2Line_F0       0b00101000	/* INITIALIZE THE SCREEN AS Parallel 4 BIT 2 line Font 5x8  */
#define LCD_COMMAND_4BIT_1Line_F0       0b00100000	/* INITIALIZE THE SCREEN AS Parallel 4 BIT 2 line Font 5x8  */
#define LCD_COMMAND_4BIT_2Line_F1       0b00101100	/* INITIALIZE THE SCREEN AS Parallel 4 BIT 2 line Font 5x11 */
#define LCD_COMMAND_4BIT_1Line_F1       0b00100100	/* INITIALIZE THE SCREEN AS Parallel 4 BIT 2 line Font 5x11 */

#define LCD_COMMAND_4_BITS_MODE_INIT   0x02

#define LCD_COMMAND_SET_CURSOR_LOCATION 0x80

/*******************************************************************************
 *                                FUNCTIONS PROTOTYPE                          *
 *******************************************************************************/
void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);

void LCD_displayString(char *string);
void LCD_moveCursor(uint8 row, uint8 col);
void LCD_intgerToString(uint64 data);

void LCD_floatToString(float data, uint8 percision);
void LCD_clearScreen(void);
void LCD_showCursor(void);
void LCD_dispalyOn();
void LCD_dispalyOff();
#endif /* MYDRIVERS_LCD_H_ */
