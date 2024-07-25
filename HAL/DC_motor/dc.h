/**
 * @file DCMotor.h
 * @brief Header file for DC Motor driver module.
 * @version 1.0
 * @date 2024-07-25
 *
 * @details
 * This header file contains the prototypes for functions that operate on the
 * DC Motor driver module. The DC Motor driver module provides functionalities to
 * control the speed and direction of a DC motor using the AVR ATmega32 microcontroller.
 * It includes initialization routines, speed control using PWM, and direction control.
 */

#ifndef ATMEGA32_DRIVERS_HAL_DC_MOTOR_DC_H_
#define ATMEGA32_DRIVERS_HAL_DC_MOTOR_DC_H_

#include "..\..\std_types.h"
#include "..\..\common_macros.h"
#include "..\..\MCAL\gpio\gpio.h"

#define MOTOR1B B0
#define MOTOR1A B1
#define ENABLE1 B2

typedef enum rotateState {
	STOP, CW, CCW
}DcMOTOR_State;


void DcMOTOR_init(void);
void DcMOTOR_Rotate(DcMOTOR_State state);

#endif /* ATMEGA32_DRIVERS_HAL_DC_MOTOR_DC_H_ */
