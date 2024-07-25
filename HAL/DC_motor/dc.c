/**
 * @file DCMotor.c
 * @brief Source file for DC Motor driver module.
 * @version 1.0
 * @date 2024-07-25
 *
 * @details
 * This source file contains functions to be used by the DC Motor driver module.
 * The DC Motor driver module provides functionalities to control the speed and
 * direction of a DC motor using the AVR ATmega32 microcontroller. It includes
 * initialization routines, speed control using PWM, and direction control.
 */
#include "dc.h"

void DcMOTOR_init(void) {
	GPIO_setupPinDirection(MOTOR1A, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR1B, PIN_OUTPUT);
	GPIO_setupPinDirection(ENABLE1, PIN_OUTPUT);
	GPIO_writePin(MOTOR1A, LOGIC_LOW);
	GPIO_writePin(MOTOR1B, LOGIC_LOW);

}

void DcMOTOR_Rotate(DcMOTOR_State rotateDirection) {

	switch (rotateDirection) {
	case STOP:
		GPIO_writePin(MOTOR1A, LOGIC_LOW);
		GPIO_writePin(MOTOR1B, LOGIC_LOW);
		GPIO_writePin(ENABLE1, LOGIC_LOW);
		break;
	case CW:
		GPIO_writePin(MOTOR1A, LOGIC_HIGH);
		GPIO_writePin(MOTOR1B, LOGIC_LOW);
		GPIO_writePin(ENABLE1, LOGIC_HIGH);
		break;
	case CCW:
		GPIO_writePin(MOTOR1A, LOGIC_LOW);
		GPIO_writePin(MOTOR1B, LOGIC_HIGH);
		GPIO_writePin(ENABLE1, LOGIC_HIGH);
		break;

	default:
		GPIO_writePin(MOTOR1A, LOGIC_LOW);
		GPIO_writePin(MOTOR1B, LOGIC_LOW);
		break;
	}
}
