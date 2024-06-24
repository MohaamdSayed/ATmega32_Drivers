/**
 * @file SPI.h
 * @brief Header file for SPI driver module.
 * @version 1.0
 * @date 2024-06-16
 * @author Mohamed Sayed
 *
 * @details
 * This header file contains the definition of a structure and the prototypes
 * for functions that operate on this structure to be used by the SPI driver module.
 * SPI (Serial Peripheral Interface) is a synchronous serial communication protocol
 * used by the AVR ATmega32 microcontroller for high-speed data transfer between the
 * microcontroller and peripheral devices. This module provides functionalities to
 * initialize the SPI interface, set its mode of operation, configure interrupts,
 * and control its behavior.
 */

#ifndef ATMEGA32_DRIVERS_SPI_H
#define ATMEGA32_DRIVERS_SPI_H

#include "../../../std_types.h"
#include "../../../common_macros.h"

/**
 @brief Here you can find all the the information related to the Timer0
 hardware found in the official data sheet.

 REGISTERS:
 SPCR -> SPIE | SPE  | DORD | MSTR  | CPOL  | CPHA  | SPR1  | SPR0
 SPSR -> SPIF | WCOL | R    | R     | R     | R     | R     | SPI2X
 SPDR -> 8-bit value of the SPI data register used for read / write



 How to use Each register
 SPI Control Register
 SPCR -> SPIE | SPE  | DORD | MSTR  | CPOL  | CPHA  | SPR1  | SPR0

 SPIE -> spi Interrupt Enable.
 SPIE -> 1 to enable interrupt.
 SPIE -> you must enable the I-bit to allow system interrupts.

 SPE -> spi Enable
 SPE -> 1 to enable SPI Module.
 SPE -> you must enable this bit to enable any spi operation.

 DORD -> Data Order
 DORD -> 1 to transmit the LSB first.
 DORD -> 0 to transmit the MSB first.
 DORD -> you must enable this bit to enable any spi operation.

 MSTR -> Master/Slave Select
 MSTR -> 1 to Configure SPI as MASTER .
 MSTR -> 0 to Configure SPI as SLAVE .
 MSTR -> If SS is configured as an input and is driven low while MSTR is set, MSTR will be cleared,
 and SPIF in SPSR will become set,The user will then have to set MSTR to re-enable SPI Master mode.

 CPOL: -> Clock Polarity
 CPOL -> 0 to make the leading edge : RISING.
 CPOL -> 1 to make the leading edge : Falling.
 CPOL -> When this bit is written to one, SCK is high when idle. When CPOL is written to zero, SCK is low
 when idle.

 CPHA:: -> Clock Phase
 CPHA: -> 0 to make data sampled on : LEADING .
 CPHA: -> 1 to make data sampled on : TRAILING .
 CPHA: -> you must enable this bit to enable any spi operation.


 SPR1:0 -> SPI Clock Rate Select 1 and 0.
 SPR1:0 -> These two bits control the SCK rate of the device configured as a Master.
 SPR1:0 -> have no effect on the Slave.

 -----------------------------------------------
 SPI2X	|	 SPR1	|	SPR0   |	Description	|
 -----------------------------------------------
 0		|	  0		|	 0	   |	fosc/4 	    |
 0		|	  0		| 	 1	   |	fosc/16     |
 0		|	  1		| 	 0	   |	fosc/64     |
 0		|	  1		| 	 1     |	fosc/128    |
 1		|	  0		| 	 0     |	fosc/2 	    |
 1		|	  0		|	 1     |	fosc/8 	    |
 1		|	  1		|	 0     |	fosc/32	    |
 1		|	  1		|	 1     |	fosc/64	    |
 ----------------------------------------------




 How To Use SPSR
 SPI Status Register
 SPSR -> SPIF | WCOL | R    | R     | R     | R     | R     | SPI2X

 SPIF -> SPI Interrupt Flag
 SPIF -> If ss is an input and is driven low when the SPI is in Master mode, this will also set the SPIF Flag.
 SPIF -> is by hardware after finishing the ISR or
 SPIF -> is cleared by first reading the SPI Status Register with SPIF set then accessing the SPI Data Register (SPDR).

 WCOL -> Write Collision Flag
 WCOL -> is set if the SPI Data Register (SPDR) is written during a data transfer.
 WCOL -> Cleared with SPIF.

 SPI2X -> Double SPI Speed Bit
 SPI2X -> 1 to double the SCK speed of the SPI Master.
 SPI2X -> Cleared with SPIF.

 How To Use SPDR
 SPI Data Register
 SPDR -> 8-bit value of the SPI data register used for read / write
 writing value to the SPDR will initiate Transmit.

 */

//#define  SPCR (*(volatile uint8 *)((0x0D) + 0x20))
//#define  SPSR (*(volatile uint8 *)((0x0E) + 0x20))
//#define  SPDR (*(volatile uint8 *)((0x0F) + 0x20))

typedef enum {
    SPI_FCPU_4,
    SPI_FCPU_16,
    SPI_FCPU_64,
    SPI_FCPU_128,
    SPI_FCPU_2,
    SPI_FCPU_8,
    SPI_FCPU_32,
} SPI_Master_Freq;

typedef enum {
    SPI_MSB, SPI_LSB,
} SPI_Data_Order;

void initMaster();

void setMasterFrequency(SPI_Master_Freq);

void setDataOrder(SPI_Data_Order);

void initSlave();

uint8 sendReceiveByte(uint8);

void sendString(const uint8*);

void receiveString(uint8*);

#endif //ATMEGA32_DRIVERS_SPI_H
