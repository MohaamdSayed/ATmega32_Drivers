/**
 * @file timer_0.h
 * @brief Header file for Timer 0 driver module.
 * @version 1.0
 * @date 2024-06-16
 * @author Mohamed Sayed
 *
 * @details
 * This header file contains the definition of a structure and the prototypes
 * for functions that operate on this structure to be used by the Timer 0 driver module.
 * Timer 0 is a hardware timer in the AVR microcontroller used for various timing and
 * counting operations. This module provides functionalities to initialize Timer 0,
 * set its mode of operation, configure interrupts, and control its behavior.
 */

#ifndef MYDRIVERS_MCAL_TIMERS_TIMER0_H_
#define MYDRIVERS_MCAL_TIMERS_TIMER0_H_

#include "../../../std_types.h"
/*
 REGISTERS:
 TCCR0 -> FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00
 TCNT0 -> 8-bit value of the timer/counter reading
 OCR0  -> 8-bit value used to compare with the TCNT0
 TIMSK -> R | R | R | R | R | R | OCIE0 | TOIE0
 TIFR  -> R | R | R | R | R | R | OCF0  | TOV0


 How to use Each register
 TIMER/COUNTER CONTROL REGISTER
 TCCR0 -> FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00

 FOC0 -> FORCE OUTPUT COMPARE BIT
 FOC0 -> 1 (WGM00 non-PWM )  / 0 for PWM
 FOC0 -> always read as zero

 WGM01:0 -> Waveform Generation Mode
 -------------------------------------------------------------------------------------------------------
 mode|  WGM01	|	WGM00	|	Timer/counter	   |	TOP VALUE	|	OCR0 update	|TOV0 Flag Set On	|
 --------------------------------------------------|----------------|---------------|-------------------|
 1	 |	  0		|	  0		|	Normal 			   |TOP = 0xFF(255) |	immediate	|	MAX				|
 2	 |	  0		|	  1		|	PWM Phase Correct  |TOP = 0xFF(255)	|	TOP			|	BOTTOM			|
 3	 |	  1		|	  0		|	CTC				   |TOP = OCR0		|	immediate	|	MAX				|
 4	 |	  1		|	  1		|	Fast PWM		   |TOP = 0xFF(255)	|	BOTTOM		|	MAX				|
 -------------------------------------------------------------------------------------------------------





 COM01:0 -> Compare Match Output Mode
 COM01:0 -> These bits control the behavior of the OC0 pin it overrides the GPIO Settings
 COM01:0 -> Note to set/drive Power using OC0 you need to set the DDR (data direction Register)

 this Table Work With mode NORMAL / CTC
 -------------------------------------------------------------------
 COM01	|  COM00	|	Description									|
 -------------------------------------------------------------------
 0		|	  0		|	Normal port operation OC0 disconnected		|
 0		|	  1		|	Toggle OC0 on compare match					|
 1		|	  0		|	Clear OC0 on compare match					|
 1		|	  1		|	set OC0 on compare match					|
 -------------------------------------------------------------------

 this Table Work With mode Fast PWM
 ---------------------------------------------------------------------------------------
 COM01	|  COM00	|	Description														|
 ---------------------------------------------------------------------------------------
 0		|	  0		|	Normal port operation OC0 disconnected							|
 0		|	  1		|	Reserved														|
 1		|	  0		|	Clear OC0 on compare match set OC0 at BOTTOM (non-inverting)	|
 1		|	  1		|	set OC0 on compare match clear OC0 at BOTTOM (inverting)		|
 ---------------------------------------------------------------------------------------

 this Table Work With mode Phase Correct PWM
 ---------------------------------------------------------------------------------------
 COM01	|  COM00	|	Description														|
 ---------------------------------------------------------------------------------------
 0		|	  0		|	Normal port operation OC0 disconnected							|
 0		|	  1		|	Reserved														|
 1		|	  0		|	Clear OC0 on compare upCount set OC0 on Compare downCounting 	|
 1		|	  1		|	Set OC0 on compare upCount clear OC0 on Compare downCounting	|
 ---------------------------------------------------------------------------------------



 CS02:0 -> this three clock select bits are used to select clock source to be used by the timer
 -------------------------------------------------------------------------------
 CS02	|	 CS01	|	CS00   |	Description									|
 -------------------------------------------------------------------------------
 0		|	  0		|	 0	   |	No Clock Source (Disable Clock)				|
 0		|	  0		| 	 1	   |	No Prescaler Same as system Clock			|
 0		|	  1		| 	 0	   |	CLk/8										|
 0		|	  1		| 	 1     |	CLK/64										|
 1		|	  0		| 	 0     |	CLK/256										|
 1		|	  0		|	 1     |	CLK/1024									|
 1		|	  1		|	 0     |	EXTERNAL CLOCk on T0 Clock on falling edge	|
 1		|	  1		|	 1     |	EXTERNAL CLOCk on T0 Clock on rising edge	|
 -------------------------------------------------------------------------------


 How To Use TIMSK
 TIMER/COUNTER INTERRUPT MASK REGISTER

 TIMSK -> R | R | R | R | R | R | OCIE0 | TOIE0

 OCIE0 -> 1 to enable interrupt
 OCIE0 -> Output Compare Match Interrupt Enable
 OCIE0 -> you must enable the I-bit to allow system interrupts


 TOIE0 -> 1 to enable interrupt
 TOIE0 -> Overflow Interrupt Enable
 TOIE0 -> you must enable the I-bit to allow system interrupts

 How To Use TIFR
 TIMER/COUNTER INTERRUPT FLAG REGISTER

 TIFR  -> R | R | R | R | R | R | OCF0  | TOV0

 OCF0 -> Output Compare Match Interrupt FLAG
 TOV0 -> Overflow Interrupt FLAG

 */

/**
 * @brief this enum holds the available operation modes in timer 0
 *
 */
typedef enum {
	TIMER0_MODE_NORMAL, /**< TIMER0_MODE_NORMAL */
	TIMER0_MODE_PWM_PHASE_CORRECT,/**< TIMER0_MODE_PWM_PHASE_CORRECT */
	TIMER0_MODE_CTC, /**< TIMER0_MODE_CTC */
	TIMER0_MODE_FAST_PWM, /**< TIMER0_MODE_FAST_PWM */
} timer0_mode;

/**
 * @brief this enum hold the available clock settings available for timer 0
 *
 */
typedef enum {
	TIMER0_CLK_NO_CLOCK, /**< TIMER0_CLK_NO_CLOCK */
	TIMER0_CLK_SYSTEM, /**< TIMER0_CLK_SYSTEM */
	TIMER0_CLK_SYSTEM_8, /**< TIMER0_CLK_SYSTEM_8 */
	TIMER0_CLK_SYSTEM_64, /**< TIMER0_CLK_SYSTEM_64 */
	TIMER0_CLK_SYSTEM_265, /**< TIMER0_CLK_SYSTEM_265 */
	TIMER0_CLK_SYSTEM_1024, /**< TIMER0_CLK_SYSTEM_1024 */
	TIMER0_CLK_SYSTEM_EXTERNAL_FALING,/**< TIMER0_CLK_SYSTEM_EXTERNAL_FALING */
	TIMER0_CLK_SYSTEM_EXTERNAL_RISING, /**< TIMER0_CLK_SYSTEM_EXTERNAL_RISING */
} timer0_CLK;

typedef enum {
	TIMER0_NORMAL_CTC_OC0_DISCONNECTED = 0,
	TIMER0_NORMAL_CTC_OC0_TOGGLE = 1,
	TIMER0_NORMAL_CTC_OC0_CLEAR = 2,
	TIMER0_NORMAL_CTC_OC0_SET = 3,

	TIMER0_FAST_PWM_OC0_DISCONNECTED = 0,
	TIMER0_FAST_PWM_OC0_CLEAR = 2,
	TIMER0_FAST_PWM_OC0_SET = 3,

	TIMER0_PWM_PHASE_CORRECT_OC0_DISCONNECTED = 0,
	TIMER0_PWM_PHASE_CORRECT_OC0_CLEAR = 2,
	TIMER0_PWM_PHASE_CORRECT_OC0_SET = 3,

} timer0_OC0_Control;

typedef enum {
	TIMER0_INTERRUPT_OVERFLOW, TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH

} timer0_interrupt_type;

/**
 * @brief Represent The Settings used to initialize the Timer 0
 *
 */
typedef struct {
	timer0_mode mode;
	timer0_CLK clock;
	timer0_OC0_Control OC0;
} timer0_Config;

typedef void (*Timer0Callback)(void);

void timer0_init(timer0_Config*);
//static void set_Clock(timer0_CLK clk);
//static void OC0_control(timer0_OC0_Control OC0);
void timer0_stop(void);
void timer0_start(void);
void timer0_setStart(uint8);
uint8 timer0_getTicks(void);

void timer0_set_compare_value(uint8 compValue);

void timer0_enable_interrupt(timer0_interrupt_type);
void timer0_disable_interrupt(timer0_interrupt_type interrupt);

uint8 timer0_get_interrupt_flag(timer0_interrupt_type);
void timer0_set_ISR_callback(timer0_interrupt_type, Timer0Callback);

#endif /* MYDRIVERS_MCAL_TIMERS_TIMER0_H_ */
