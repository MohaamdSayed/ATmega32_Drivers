/**
 * @file TWI.c
 * @brief Source file for TWI (I2C) driver module.
 * @version 1.0
 * @date 2024-07-25
 * @author Mohamed Sayed
 *
 * @details
 * This source file contains the implementation of functions defined in the TWI (I2C) driver module header file.
 * TWI (Two Wire Interface) or I2C (Inter-Integrated Circuit) is a synchronous serial communication protocol
 * utilized by the AVR ATmega32 microcontroller for interfacing with peripheral devices such as EEPROMs, sensors,
 * and other microcontrollers.
 *
 * The module includes:
 * - Initialization of the TWI interface with the required settings.
 * - Functions to send start and stop conditions on the TWI bus.
 * - Functions to write and read data bytes.
 * - Function to get the status of the TWI operation.
 * - Function to write data to an external EEPROM.
 *
 * This implementation ensures that TWI communication is correctly managed and that data is accurately transmitted
 * and received according to the I2C protocol specifications.
 */

#include "twi.h"
#include "../../Atmega32_Registers.h"

void TWI_init(TWI_ConfigType *config) {

	/* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */

	TWBR = config->bit_rate;
	TWSR = 0x00;

	/* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
	 General Call Recognition: Off */
	TWAR = config->address; // my address = 0x01 :)

	TWCR = (1 << TWEN); /* enable TWI */
}

void TWI_start(void) {
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
}

void TWI_stop(void) {
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_writeByte(uint8 data) {
	/* Put data On TWI data Register */
	TWDR = data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
}

uint8 TWI_readByteWithACK(void) {
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
	/* Read Data */
	return TWDR;
}

uint8 TWI_readByteWithNACK(void) {
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
	/* Read Data */
	return TWDR;
}

uint8 TWI_getStatus(void) {
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}
