/**
 * @file EEPROM.h
 * @brief Header file for EEPROM driver module.
 * @version 1.0
 * @date 2024-07-25
 *
 * @details
 * This header file contains the prototypes for functions that operate on the
 * EEPROM driver module. EEPROM (Electrically Erasable Programmable Read-Only Memory)
 * is used by the AVR ATmega32 microcontroller for non-volatile data storage.
 * This module provides functionalities to initialize the EEPROM, read from it,
 * and write data to it.
 */

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "..\..\std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data);

#endif /* EXTERNAL_EEPROM_H_ */
