//
// Created by devel on 20-Jun-24.
//

#include "spi.h"
#include "..\..\..\common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */

void initMaster() {
	/**    SPCR -> SPIE | SPE  | DORD | MSTR  | CPOL  | CPHA  | SPR1  | SPR0
	 *     SPCR -> 0    | 1    | 1    | 1     | 0     | 0     | SPR1  | SPR0
	 *     SPSR -> SPIF | WCOL | R    | R     | R     | R     | R     | SPI2X
	 * */

	SPCR = 0b01010000; /** */
}

void initSlave();

uint8 sendReceiveByte(uint8);

void sendString(const uint8*);

void receiveString(uint8*);
