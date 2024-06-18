/**
 * @file timer_0.c
 * @brief Source file for Timer 0 driver module.
 * @version 1.0
 * @date 2024-06-16
 * @author Mohamed Sayed
 *
 * @details
 * This source file contains the implementations of functions that operate on Timer 0,
 * a hardware timer in the AVR Microcontroller. Timer 0 is used for various timing and
 * counting operations. This module provides functionalities to initialize Timer 0,
 * set its mode of operation, configure interrupts, and control its behavior.
 */

#include "timer_0.h"
#include "avr/io.h"
#include "../../../common_macros.h"
#include <avr/interrupt.h>
#include "../../../HAL/Character_LCD/lcd.h"
//#include "avr/delay.h"

static uint8 selectedClk;
Timer0Callback overflow_callback = NULL_PTR;
Timer0Callback compare_match_callback = NULL_PTR;

/**
 * @briefs this function set the proper clock setting to the timer module.
 * the clock settings can be found in a enum TIMER0_CLK
 *
 * @param clk
 */
static void set_Clock(TIMER0_CLK clk) {
    selectedClk = clk;
    TCCR0 = (TCCR0 & 0b11111000) | clk;
}

/**
 * @brief this function control the behavior of OC0 pin
 * @param OC0
 */
static void OC0_control(TIMER0_OC0_Control OC0) {
    TCCR0 = (TCCR0 & 0b11001111) | (OC0 << 4);
}

/**
 * @brief This function is used to initialize the timer
 *
 * @param config  TIMER0_Config structure containing the configuration data for the timer
 */

void TIMER0_init(TIMER0_Config *config) {

    switch (config->mode) {
        /**initialize timer 0 in normal mode and disconnect OC0 by default*/
        case TIMER0_MODE_NORMAL:
            /** TCCR0 -> FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00 */
            /** TCCR0 -> 1 	  | 0 	  | 0 	  | 0 	  | 0 	  | CS02 | CS01 | CS00 */
            TCCR0 |= (1 << FOC0);
            break;
        case TIMER0_MODE_CTC:
            /** TCCR0 -> FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00 */
            /** TCCR0 -> 1 	  | 0 	  | 0 	  | 0 	  | 1 	  | CS02 | CS01 | CS00 */
            TCCR0 = 0b1000100;

            break;
        case TIMER0_MODE_FAST_PWM:
            /** TCCR0 -> FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00 */
            /** TCCR0 -> 0 	  | 1 	  | 0 	  |  0	  | 1 	  | CS02 | CS01 | CS00 */
            TCCR0 = 0b01001000;
            break;
        case TIMER0_MODE_PWM_PHASE_CORRECT:
            /**TCCR0 -> FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00 */
            /** TCCR0 -> 0 	 | 1 	 | 0 	 |  0	 | 0 	 | CS02 | CS01 | CS00 */
            TCCR0 = 0b01000000;
            break;
        default:
            break;
    }

    set_Clock(config->clock);
    OC0_control(config->OC0);
    TIFR |= 3; /** Clear interrupt Flags */

}

/**
 * @brief this function is used to stop the timer from counting without changing any settings.
 *
 */
void TIMER0_stop(void) {
    set_Clock(TIMER0_CLK_NO_CLOCK);
}

/**
 * @brief this function make the counter resume counting from it's previous state without changing any settings.
 *
 */
void TIMER0_start(void) {
    set_Clock(selectedClk);
}

/**
 * @brief this function modifiy TCNT0 Register to set initial counting value of the timer;
 *
 * @param startValue
 */
void TIMER0_setStart(uint8 startValue) {
    TCNT0 = startValue;
}

/**
 * @brief this function return the Current value of the Register TCNT0 which hold the currnt ticks.
 *
 * @return TCNT0 Value.
 */
uint8 TIMER0_getTicks(void) {
    return TCNT0;
}

/**
 * @brief this function modify the OCR0 register used as compare value.
 *
 * @param compValue
 */
void TIMER0_set_compare_value(uint8 compValue) {
    OCR0 = compValue;

}

/**
 * @brief this function modify TIMSK to enable the interrupt for the timer0.
 *
 * @param interrupt enum holds the two different interrupt types
 */
void TIMER0_enable_interrupt(TIMER0_interrupt_type interrupt) {

    switch (interrupt) {
        case TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH:
            //TIMSK -> R | R | R | R | R | R | OCIE0 | TOIE0
            TIMSK = TIMSK | 0b10;
            break;
        case TIMER0_INTERRUPT_OVERFLOW:
            TIMSK = TIMSK | 0b1;
            break;
        default:
            break;
    }
}

/**
 * @brief this function modify TIMSK to disable the interrupt for the timer0.
 *
 * @param interrupt enum holds the two different interrupt types
 */
void TIMER0_disable_interrupt(TIMER0_interrupt_type interrupt) {
    switch (interrupt) {
        case TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH:
            //TIMSK -> R | R | R | R | R | R | OCIE0 | TOIE0
            TIMSK = TIMSK & ~(0b00000010);
            break;
        case TIMER0_INTERRUPT_OVERFLOW:
            TIMSK = TIMSK & ~(0b00000001);

            break;
        default:
            break;
    }
}

/**
 * @brief this function return the current status of the interrupt flag
 *
 * @param interrupt enum holds the two different interrupt types
 * @return
 */
uint8 TIMER0_get_interrupt_flag(TIMER0_interrupt_type interrupt) {
    switch (interrupt) {
        case TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH:
            /**TIFR  -> R | R | R | R | R | R | OCF0  | TOV0*/
            return GET_BIT(TIFR, 1);
        case TIMER0_INTERRUPT_OVERFLOW:
            return GET_BIT(TIFR, 0);
    }
    return 0;
}

/**
 * @brief this function take a callback function from the user and save it's memory location to be used by the ISR later.
 *
 * @param interrupt
 * @param callback
 */
void TIMER0_set_ISR_callback(TIMER0_interrupt_type interrupt,
                             Timer0Callback callback) {
    switch (interrupt) {
        case TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH:
            compare_match_callback = callback;
            break;
        case TIMER0_INTERRUPT_OVERFLOW:
            overflow_callback = callback;
            break;
    }
}

/**
 * @brief call the ISR function with the given Callback.
 *
 */
ISR(TIMER0_COMP_vect) {
    if (compare_match_callback != NULL_PTR) {
        compare_match_callback();
    }

}
/**
 * @brief call the ISR function with the given Callback.
 *
 */
ISR(TIMER0_OVF_vect) {
    if (overflow_callback != NULL_PTR) {
        overflow_callback();
    }

}
