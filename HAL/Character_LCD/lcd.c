/******************************************************************************
 *
 * Module: HAL/LCD
 *
 * File Name: lcd.c
 *
 * Description: Source File for LCD driver
 *
 * Author: Mohamed Sayed
 *
 *******************************************************************************/
#include "lcd.h"
#include "../../delay.h"
#include <stdlib.h>

#if defined  (PARALLEL_8_BITS_FULL_PORT)

static void send(uint8 command) {
    delay_ms(1);
    GPIO_writePin(E, LOGIC_HIGH);
    delay_ms(1);
    GPIO_writePort(DATA_PORT, command);
    delay_ms(1);
    GPIO_writePin(E, LOGIC_LOW);
    delay_ms(1);
}


void LCD_init(void) {
    GPIO_setupPinDirection(RS, PIN_OUTPUT);
    GPIO_setupPinDirection(E, PIN_OUTPUT);
    GPIO_setupPortDirection(DATA_PORT, PORT_OUTPUT);
    delay_ms(20);
    LCD_sendCommand(LCD_COMMAND_8BIT_2Line_F1);
    LCD_sendCommand(LCD_COMMAND_DISPLAY_ON);
    LCD_sendCommand(LCD_COMMAND_CLEAR);
}


#elif defined (PARALLEL_8_BITS_RANDOM)

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

#elif defined (PARALLEL_4_BITS)

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

#elif defined (I2C)


#endif

void LCD_sendCommand(uint8 command) {
    GPIO_writePin(RS, LOGIC_LOW);
    send(command);
}

void LCD_displayCharacter(uint8 char_data) {
    GPIO_writePin(RS, LOGIC_HIGH);
    send(char_data);
}

void LCD_displayString(char *string) {
    uint8 index = 0;
    while (string[index]) {
        LCD_displayCharacter(string[index]);
        index++;
    }
}

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

void LCD_intgerToString(uint64 data) {
    char buffer[10];
    ltoa(data, buffer, 10);
    LCD_displayString(buffer);
}

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

void LCD_clearScreen(void) {
    LCD_sendCommand(LCD_COMMAND_CLEAR);
}

void LCD_showCursor(void) {
    LCD_sendCommand(LCD_COMMAND_CURSOR_BLINKING);
}

void LCD_dispalyOff() {
    LCD_sendCommand(LCD_COMMAND_DISPLAY_OFF);
}

void LCD_dispalyOn() {
    LCD_sendCommand(LCD_COMMAND_DISPLAY_ON);
}
