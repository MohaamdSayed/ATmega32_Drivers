/**
 * @file UART.h
 * @brief Header file for UART driver module.
 * @version 1.0
 * @date 2024-07-25
 * @author Mohamed Sayed
 *
 * @details
 * This header file contains the definition of a structure and the prototypes
 * for functions that operate on this structure to be used by the UART driver module.
 * UART (Universal Asynchronous Receiver-Transmitter) is an asynchronous serial
 * communication protocol used by the AVR ATmega32 microcontroller for data
 * transmission and reception between the microcontroller and peripheral devices.
 * This module provides functionalities to initialize the UART interface, set its
 * baud rate, configure interrupts, and control its operation.
 */
#ifndef UART_H_
#define UART_H_

#include "../../../std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(uint32 baud_rate);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
