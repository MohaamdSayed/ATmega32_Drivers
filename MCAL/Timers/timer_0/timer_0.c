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
#include "avr/io.h" /* To use the IO Ports Registers */
#include "../../../common_macros.h"
#include <avr/interrupt.h>
#include "../../../HAL/Character_LCD/lcd.h"
#include "avr/delay.h"

static uint8 selectedClk;
Timer0Callback overflow_callback = NULL_PTR;
Timer0Callback compare_match_callback = NULL_PTR;

/**
 * @briefs
 *
 * @param clk
 */
static void set_Clock(timer0_CLK clk) {
	selectedClk = clk;
	TCCR0 = (TCCR0 & 0b11111000) | clk;
}

/**
 * @brief This function is used to initialize the timer
 *
 * @param config  timer0_Config structure containing the configuration data for the timer
 */

static void OC0_control(timer0_OC0_Control OC0) {
	TCCR0 = (TCCR0 & 0b11001111) | (OC0 << 4);
}

void timer0_init(timer0_Config *config) {

	switch (config->mode) {
	/*initialize timer 0 in normal mode and disconnect OC0 by default*/
	case TIMER0_MODE_NORMAL:
		//TCCR0 -> FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00
		// TCCR0 -> 1 	| 0 	| 0 	| 0 	| 0 	| CS02 | CS01 | CS00
		TCCR0 |= (1 << FOC0);
		break;
	case TIMER0_MODE_CTC:
		//TCCR0 -> FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00
		// TCCR0 -> 1 	| 0 	| 0 	| 0 	| 1 	| CS02 | CS01 | CS00
		TCCR0 = 0b1000100;
		//TODO handle Compare Value

		break;
	case TIMER0_MODE_FAST_PWM:
		//TCCR0 -> FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00
		// TCCR0 -> 0 	| 1 	| 0 	|  0	| 1 	| CS02 | CS01 | CS00
		TCCR0 = 0b01001000;
		//TODO
		break;
	case TIMER0_MODE_PWM_PHASE_CORRECT:
		//TCCR0 -> FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00
		// TCCR0 -> 0 	| 1 	| 0 	|  0	| 0 	| CS02 | CS01 | CS00
		TCCR0 = 0b01000000;
		//TODO
		break;
	default:
		break;
	}

	set_Clock(config->clock);
	OC0_control(config->OC0);
	TIFR |= 3;

}

void timer0_stop(void) {
	set_Clock(TIMER0_CLK_NO_CLOCK);
}
void timer0_start(void) {
	set_Clock(selectedClk);
}
void timer0_setStart(uint8 startValue) {
	TCNT0 = startValue;
	_delay_ms(1000);
	TCNT0 = startValue;
}
uint8 timer0_getTicks(void) {
	uint8 reg = TCNT0;
	return TCNT0;
}
void timer0_set_compare_value(uint8 compValue) {
	OCR0 = compValue;

}

void timer0_enable_interrupt(timer0_interrupt_type interrupt) {

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

void timer0_disable_interrupt(timer0_interrupt_type interrupt) {
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
uint8 timer0_get_interrupt_flag(timer0_interrupt_type interrupt) {
	switch (interrupt) {
	case TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH:
//		 TIFR  -> R | R | R | R | R | R | OCF0  | TOV0
		return GET_BIT(TIFR, 1);
	case TIMER0_INTERRUPT_OVERFLOW:
		return GET_BIT(TIFR, 0);
	}
	return 0;
}
void timer0_set_ISR_callback(timer0_interrupt_type interrupt,
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
ISR(TIMER0_COMP_vect) {
	if (compare_match_callback != NULL_PTR) {
		compare_match_callback();
	}

}
ISR(TIMER0_OVF_vect) {
	if (overflow_callback != NULL_PTR) {
		overflow_callback();
	}

}
