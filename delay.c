/**
 * @file delay.c
 * @brief Functions for creating precise delays in microseconds and milliseconds.
 *
 * These functions use inline assembly to generate precise delays based on the
 * clock frequency of the AVR microcontroller.
 *
 * @date 2024-06-18
 * @author Mohamed Sayed
 */

#include "delay.h"

/**
 * @brief Creates a delay for a specified number of microseconds.
 *
 * This function generates a delay using a busy-wait loop, where each iteration
 * of the loop takes 4 clock cycles. The total number of iterations is calculated
 * based on the specified delay in microseconds and the clock frequency.
 *
 * @param us The number of microseconds to delay.
 */
void delay_us(uint16 us) {
    /**
     * Calculate the number of loop iterations needed for the given delay
     * Assuming a 16 MHz clock, 1 instruction cycle takes 1 / 16,000,000 seconds or 62.5 ns
     * We want to delay for 'us' microseconds, so we need (us * 16) iterations
     */

    /**
     * Check if the delay is too short to be effective
     */
    if (us == 0)
        return;

    /**
     * 16 cycles per microsecond (for 16 MHz clock)
     */
    uint16 loops = (us * (F_CPU / 1000000UL)) / 4;

    /**
     * Inline assembly to create the delay
     */
    __asm__ volatile (
        "1: sbiw %0, 1" "\n\t" /** Subtract 1 from loops (2 cycles) */
        "brne 1b" "\n\t"       /** Branch if not zero (2 cycles) */
        : "=w" (loops)         /** Output operand */
        : "0" (loops)          /** Input operand */
    );
}

/**
 * @brief Creates a delay for a specified number of milliseconds.
 *
 * This function generates a delay by calling delay_us() repeatedly.
 *
 * @param ms The number of milliseconds to delay.
 */
void delay_ms(uint16 ms) {
    /**
     * Loop to create the delay
     */
    while (ms--) {
        delay_us(1000); /** 1 millisecond = 1000 microseconds */
    }
}
