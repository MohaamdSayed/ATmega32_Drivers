/*
 * timer_1.c
 *
 *  Created on: Jun 24, 2024
 *      Author: devel
 */
#include "timer_1.h"

static uint8 selectedClk;
Timer1Callback TIMER1_overflow_callback = NULL_PTR;
Timer1Callback TIMER1_compare_match_A_callback = NULL_PTR;
Timer1Callback TIMER1_compare_match_B_callback = NULL_PTR;

void TIMER1_SetMode(TIMER1_MODE mode) {
	TCCR1A = TCCR1A & 0b11111100;
	switch (mode) {
	case TIMER1_MODE_NORMAL:
		TCCR1B = TCCR1B & 0b11100111;
		break;
	case TIMER1_MODE_CTC:
		TCCR1B = (TCCR1B & 0b11100111) | 1 << 3;
		break;

	default:
		break;
	}

}

void TIMER1_set_Clock(TIMER1_CLK clk) {
	selectedClk = clk;
}

void TIMER1_start(void) {
	TCCR1B = (TCCR1B & 0b11111000) | selectedClk;
//    set_Clock(selectedClk);
}

void TIMER1_OC1A_control(TIMER1_OC1A_Control OC1A) {
	TCCR1A = (TCCR1A & 0b00111111) | (OC1A << 6);
}

void TIMER1_OC1B_control(TIMER1_OC1B_Control OC1B) {
	TCCR1A = (TCCR1A & 0b11001111) | (OC1B << 4);
}

void TIMER1_stop(void) {
	TCCR1B = (TCCR1B & 0b11111000) | TIMER1_CLK_NO_CLOCK;
}

uint16 TIMER1_getTicks(void) {
	return TCNT1;
}

void TIMER1_set_compare_value_A(uint16 compValue) {
	OCR1A = compValue;
}

void TIMER1_set_compare_value_B(uint16 compValue) {
	OCR1B = compValue;
}

static void TIMER1_enable_interrupt(TIMER1_interrupt_type interrupt) {

	switch (interrupt) {
	case TIMER1_INTERRUPT_OVERFLOW:
		//TIMSK -> R | R | R | OCIE1A | OCIE1B | TOIE1 | R | R
		TIMSK = TIMSK | (1 << 2);
		break;
	case TIMER1_INTERRUPT_OUTPUT_COMPARE_MATCH_A:
		TIMSK = TIMSK | (1 << 4);
		break;
	case TIMER1_INTERRUPT_OUTPUT_COMPARE_MATCH_B:
		TIMSK = TIMSK | (1 << 3);
		break;
	default:
		break;
	}
}

static void TIMER1_disable_interrupt(TIMER1_interrupt_type interrupt) {

	switch (interrupt) {
	case TIMER1_INTERRUPT_OVERFLOW:
		//TIMSK -> R | R | R | OCIE1A | OCIE1B | TOIE1 | R | R
		TIMSK = TIMSK & ~(1 << 2);
		break;
	case TIMER1_INTERRUPT_OUTPUT_COMPARE_MATCH_A:
		TIMSK = TIMSK & ~(1 << 4);
		break;
	case TIMER1_INTERRUPT_OUTPUT_COMPARE_MATCH_B:
		TIMSK = TIMSK & ~(1 << 3);
		break;
	default:
		break;
	}
}

void TIMER1_enableOverFlowInterrupt(void) {
	TIMER1_enable_interrupt(TIMER1_INTERRUPT_OVERFLOW);
}

void TIMER1_disableOverFlowInterrupt(void) {
	TIMER1_disable_interrupt(TIMER1_INTERRUPT_OVERFLOW);
}

void TIMER1_enable_CTC_A_Interrupt(void) {
	TIMER1_enable_interrupt(TIMER1_INTERRUPT_OUTPUT_COMPARE_MATCH_A);

}

void TIMER1_disable_CTC_A_Interrupt(void) {
	TIMER1_disable_interrupt(TIMER1_INTERRUPT_OUTPUT_COMPARE_MATCH_A);

}

void TIMER1_enable_CTC_B_Interrupt(void) {
	TIMER1_enable_interrupt(TIMER1_INTERRUPT_OUTPUT_COMPARE_MATCH_B);

}

void TIMER1_disable_CTC_B_Interrupt(void) {
	TIMER1_disable_interrupt(TIMER1_INTERRUPT_OUTPUT_COMPARE_MATCH_B);

}

uint8 TIMER1_get_OverFlow_Flag(void) {
	return GET_BIT(TIFR, 2);
}

uint8 TIMER1_get_CTC_A_Flag(void) {
	return GET_BIT(TIFR, 4);
}

uint8 TIMER1_get_CTC_B_Flag(void) {
	return GET_BIT(TIFR, 3);

}

void TIMER1_set_OverFlow_Callback(Timer1Callback callback) {
	TIMER1_overflow_callback = callback;
}

void TIMER1_set_CTC_A_Callback(Timer1Callback callback) {
	TIMER1_compare_match_A_callback = callback;

}

void TIMER1_set_CTC_B_Callback(Timer1Callback callback) {
	TIMER1_compare_match_B_callback = callback;

}
