/******************************************************************************
 *
 * Module: MCAL/GPIO
 *
 * File Name: gpio.h
 *
 * Description: Header file for the AVR GPIO driver
 *
 * Author: Mohamed Sayed
 *
 *******************************************************************************/

#ifndef ATMEGA32_DRIVERS_GPIO_H_
#define ATMEGA32_DRIVERS_GPIO_H_

#include "..\..\std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8
#define TOTAL_NUM_OF_PINS      31
#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

/*******************************************************************************
 *                               Sayed Definitions                             *
 *******************************************************************************/
#define A0                     0
#define A1                     1
#define A2                     2
#define A3                     3
#define A4                     4
#define A5                     5
#define A6                     6
#define A7                     7
#define B0                     8
#define B1                     9
#define B2                     10
#define B3                     11
#define B4                     12
#define B5                     13
#define B6                     14
#define B7                     15
#define C0                     16
#define C1                     17
#define C2                     18
#define C3                     19
#define C4                     20
#define C5                     21
#define C6                     22
#define C7                     23
#define D0                     24
#define D1                     25
#define D2                     26
#define D3                     27
#define D4                     28
#define D5                     29
#define D6                     30
#define D7                     31

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum {
    PIN_INPUT, PIN_OUTPUT
} GPIO_PinDirectionType;
typedef enum {
    LOW, HIGH
} GPIO_LogicType;


typedef enum {
    PORT_INPUT, PORT_OUTPUT = 0xFF
} GPIO_PortDirectionType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 pin_num, GPIO_PinDirectionType direction);

/*
 * Description :
 * Write the logic_level Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 pin_num, GPIO_LogicType logic_level);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 pin_num);

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num);

void GPIO_enablePullUp(uint8 pin_num);

void GPIO_disablePullUp(uint8 pin_num);

#endif /* ATMEGA32_DRIVERS_GPIO_H_ */
