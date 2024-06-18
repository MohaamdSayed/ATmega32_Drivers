/**
 * @file delay.h
 * @brief Functions for creating precise delays in microseconds and milliseconds.
 *
 * This header file declares functions for generating precise delays using inline
 * assembly based on the clock frequency of the AVR microcontroller.
 *
 * @date 2024-06-18
 * @author Mohamed Sayed
 */

#ifndef ATMEGA32_DRIVERS_DELAY_H_
#define ATMEGA32_DRIVERS_DELAY_H_

#include "std_types.h"

/**
 * @brief Creates a delay for a specified number of microseconds.
 *
 * This function generates a delay using a busy-wait loop, where each iteration
 * of the loop takes 4 clock cycles. The total number of iterations is calculated
 * based on the specified delay in microseconds and the clock frequency.
 *
 * @param us The number of microseconds to delay.
 */
void delay_us(uint16 us);

/**
 * @brief Creates a delay for a specified number of milliseconds.
 *
 * This function generates a delay by calling delay_us() repeatedly.
 *
 * @param ms The number of milliseconds to delay.
 */
void delay_ms(uint16 ms);

#endif /* ATMEGA32_DRIVERS_DELAY_H_ */
