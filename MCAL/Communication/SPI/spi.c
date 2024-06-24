/**
 * @file SPI.c
 * @brief Source file for SPI driver module.
 * @version 1.0
 * @date 2024-06-16
 * @author Mohamed Sayed
 *
 * @details
 * This Source file contains functions to be used by the SPI driver module.
 * SPI (Serial Peripheral Interface) is a synchronous serial communication protocol
 * used by the AVR ATmega32 microcontroller for high-speed data transfer between the
 * microcontroller and peripheral devices. This module provides functionalities to
 * initialize the SPI interface, set its mode of operation, configure interrupts,
 * and control its behavior.
 */

#include "spi.h"
#include "avr/io.h"
#include "..\..\..\common_macros.h" /* To use the macros like SET_BIT */

void initMaster() {
    /**    SPCR -> SPIE | SPE  | DORD | MSTR  | CPOL  | CPHA  | SPR1  | SPR0
     *     SPCR -> 0    | 1    | 0    | 1     | 0     | 0     | SPR1  | SPR0
     *     SPSR -> SPIF | WCOL | R    | R     | R     | R     | R     | SPI2X
     * */

    SPCR = 0b01010000; /** Enable SPI in Master MODE */
    /** DORD    : 0 LSB first
     *  CPOL    : 0 Leading Edge Rising
     *  CPHA    : 0 Data Sample With Leading
     *  SPR1:0 & SPI2X  : 0 FCPU/4
     * */
    SPSR = 0;
}

void initSlave() {
    /**    SPCR -> SPIE | SPE  | DORD | MSTR  | CPOL  | CPHA  | SPR1  | SPR0
     *     SPCR -> 0    | 1    | 0    | 0     | 0     | 0     | SPR1  | SPR0
     *     SPSR -> SPIF | WCOL | R    | R     | R     | R     | R     | SPI2X
     * */
    SPCR = 0b01000000; /** Enable SPI in Master MODE */
    /** All settings are 0 to be handled by the Master Device*/

}

uint8 sendReceiveByte(uint8 byte) {
    SPDR = byte;
    while (BIT_IS_CLEAR(SPCR, SPIF));
    return SPDR;
}

void sendString(const uint8 *string) {
    uint8 i = 0;

    do {
        sendReceiveByte(string[i]);
        i++;
    } while (string[i] != '\0');

}

void receiveString(uint8 *string) {
    uint8 i = 0;
    uint8 data;
    do {
        data = sendReceiveByte(0xFF);
        string[i] = data;
    } while (data != '\0');

}
