/**
 * @file TWI.h
 * @brief Header file for TWI (I2C) driver module.
 * @version 1.0
 * @date 2024-07-25
 * @author Mohamed Sayed
 *
 * @details
 * This header file contains the prototypes for functions used by the TWI (I2C) driver module.
 * TWI (Two Wire Interface) or I2C (Inter-Integrated Circuit) is a synchronous serial
 * communication protocol used by the AVR ATmega32 microcontroller for communication
 * between the microcontroller and peripheral devices such as EEPROMs, sensors, and other microcontrollers.
 * This module provides functionalities to initialize the TWI interface, send start and stop conditions,
 * write and read data, and get the status of the TWI operation.
 */
#ifndef TWI_H_
#define TWI_H_

#include "../../../std_types.h"
#include "../../../common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

typedef enum {
	SCL_400kbit = 2,
} TWI_BaudRate;
typedef struct {
	uint8 address;
	TWI_BaudRate bit_rate;
} TWI_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(TWI_ConfigType*);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
