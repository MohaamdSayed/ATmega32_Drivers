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


static uint8 selectedClk;
Timer0Callback TIMER0_overflow_callback = NULL_PTR;
Timer0Callback TIMER0_compare_match_callback = NULL_PTR;

/**
 * @briefs this function set the proper clock setting to the timer module.
 * the clock settings can be found in a enum TIMER0_CLK
 *
 * @param clk
 */
void set_Clock(TIMER0_CLK clk) {
    selectedClk = clk;
//    TCCR0 = (TCCR0 & 0b11111000) | clk;
}

/**
 * @brief this function control the behavior of OC0 pin
 * @param OC0
 */
void OC0_control(TIMER0_OC0_Control OC0) {
    TCCR0 = (TCCR0 & 0b11001111) | (OC0 << 4);
}

/**
 * @brief This function is used to control the mode of the timer
 *
 * @param mode  TIMER0_MODE enum containing the available modes  for the timer
 */

void SetMode(TIMER0_MODE mode) {
    switch (mode) {
        /**initialize timer 0 in normal mode and disconnect OC0 by default*/
        case TIMER0_MODE_NORMAL:
            /** TCCR0 -> FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00 */
            /** TCCR0 -> 1 	  | 0 	  | 0 	  | 0 	  | 0 	  | CS02 | CS01 | CS00 */
            TCCR0 |= (1 << 7);
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
    TIFR |= 3; /** Clear interrupt Flags */
}

/**
 * @brief this function is used to stop the timer from counting without changing any settings.
 *
 */
void TIMER0_stop(void) {
    TCCR0 = (TCCR0 & 0b11111000) | TIMER0_CLK_NO_CLOCK;
//    set_Clock(TIMER0_CLK_NO_CLOCK);
}

/**
 * @brief this function make the counter resume counting from it's previous state without changing any settings.
 *
 */
void TIMER0_start(void) {
    TCCR0 = (TCCR0 & 0b11111000) | selectedClk;
//    set_Clock(selectedClk);
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
static void TIMER0_enable_interrupt(TIMER0_interrupt_type interrupt) {

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

void enableCTCInterrupt() {
    TIMER0_enable_interrupt(TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH);
}

void enableOverFlowInterrupt() {
    TIMER0_enable_interrupt(TIMER0_INTERRUPT_OVERFLOW);
}

/**
 * @brief this function modify TIMSK to disable the interrupt for the timer0.
 *
 * @param interrupt enum holds the two different interrupt types
 */
static void TIMER0_disable_interrupt(TIMER0_interrupt_type interrupt) {
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

void disableCTCInterrupt() {
    TIMER0_disable_interrupt(TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH);
}

void disableOverFlowInterrupt() {
    TIMER0_disable_interrupt(TIMER0_INTERRUPT_OVERFLOW);
}


/**
 * @brief this function return the current status of the interrupt flag
 *
 * @param interrupt enum holds the two different interrupt types
 * @return
 */
static uint8 TIMER0_get_interrupt_flag(TIMER0_interrupt_type interrupt) {
    switch (interrupt) {
        case TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH:
            /**TIFR  -> R | R | R | R | R | R | OCF0  | TOV0*/
            return GET_BIT(TIFR, 1);
        case TIMER0_INTERRUPT_OVERFLOW:
            return GET_BIT(TIFR, 0);
    }
    return 0;
}

uint8 getOverFlowFlag(void) {
    return TIMER0_get_interrupt_flag(TIMER0_INTERRUPT_OVERFLOW);
}

uint8 getCTCFlag(void) {
    return TIMER0_get_interrupt_flag(TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH);
}


/**
 * @brief this function take a callback function from the user and save it's memory location to be used by the ISR later.
 *
 * @param interrupt
 * @param callback
 */
static void TIMER0_set_ISR_callback(TIMER0_interrupt_type interrupt,
                                    Timer0Callback callback) {
    switch (interrupt) {
        case TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH:
        	TIMER0_overflow_callback = callback;
            break;
        case TIMER0_INTERRUPT_OVERFLOW:
            TIMER0_overflow_callback = callback;
            break;
    }
}

void setOverFlowCallback(Timer0Callback callback) {
    TIMER0_set_ISR_callback(TIMER0_INTERRUPT_OVERFLOW, callback);
}

void setCTCCallback(Timer0Callback callback) {
    TIMER0_set_ISR_callback(TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH, callback);
}


/**
 * @brief call the ISR function with the given Callback.
 *
 */

#define TIMER0_COMP_ISR __vector_10

void TIMER0_COMP_ISR(void)__attribute__((signal, used, externally_visible));

void TIMER0_COMP_ISR(void) {
    if (TIMER0_overflow_callback != NULL_PTR) {
    	TIMER0_overflow_callback();
    }
}

/**
 * @brief call the ISR function with the given Callback.
 *
 */
#define TIMER0_OVF_ISR __vector_11

void TIMER0_OVF_ISR(void)__attribute__((signal, used, externally_visible));

void TIMER0_OVF_ISR(void) {
    if (TIMER0_overflow_callback != NULL_PTR) {
        TIMER0_overflow_callback();
    }
}


