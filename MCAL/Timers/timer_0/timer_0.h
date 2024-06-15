/******************************************************************************
 *
 * Module: MCAL/Timers/Timer_0
 *
 * File Name: timer_0.h
 *
 * Description: Header file for the AVR Timer_0 driver
 *
 * Author: Mohamed Sayed
 *
 *******************************************************************************/



#ifndef MYDRIVERS_MCAL_TIMERS_TIMER0_H_
#define MYDRIVERS_MCAL_TIMERS_TIMER0_H_

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
---------------------------------------------------------------------------------------------------------
 mode|  WGM01	|	WGM00	|	Timer/counter	   |	TOP VALUE	|	OCR0 update	|TOV0 Flag Set On	|
---------------------------------------------------|----------------|---------------|-----------------	|
	1|	  0		|	  0		|	Normal 			   |TOP = 0xFF(255) |	immediate	|	MAX				|
	2|	  0		|	  1		|	PWM Phase Correct  |TOP = 0xFF(255)	|	TOP			|	BOTTOM			|
	3|	  1		|	  0		|	CTC				   |TOP = OCR0		|	immediate	|	MAX				|
	4|	  1		|	  1		|	Fast PWM		   |TOP = 0xFF(255)	|	BOTTOM		|	MAX				|
---------------------------------------------------------------------------------------------------------





COM01:0 -> Compare Match Output Mode
COM01:0 -> These bits control the behavior of the OC0 pin it overrides the GPIO Settings
COM01:0 -> Note to set/drive Power using OC0 you need to set the DDR (data direction Register)

this Table Work With mode NORMAL / CTC
---------------------------------------------------------------------
 COM01	|  COM00	|	Description									|
---------------------------------------------------------------------
	0	|	  0		|	Normal port operation OC0 disconnected		|
	0	|	  1		|	Toggle OC0 on compare match					|
	1	|	  0		|	Clear OC0 on compare match					|
	1	|	  1		|	set OC0 on compare match					|
---------------------------------------------------------------------

this Table Work With mode Fast PWM
-----------------------------------------------------------------------------------------
 COM01	|  COM00	|	Description														|
-----------------------------------------------------------------------------------------
	0	|	  0		|	Normal port operation OC0 disconnected							|
	0	|	  1		|	Reserved														|
	1	|	  0		|	Clear OC0 on compare match set OC0 at BOTTOM (non-inverting)	|
	1	|	  1		|	set OC0 on compare match clear OC0 at BOTTOM (inverting)		|
-----------------------------------------------------------------------------------------

this Table Work With mode Phase Correct PWM
-----------------------------------------------------------------------------------------
 COM01	|  COM00	|	Description														|
-----------------------------------------------------------------------------------------
	0	|	  0		|	Normal port operation OC0 disconnected							|
	0	|	  1		|	Reserved														|
	1	|	  0		|	Clear OC0 on compare upCount set OC0 on Compare downCounting 	|
	1	|	  1		|	Set OC0 on compare upCount clear OC0 on Compare downCounting	|
-----------------------------------------------------------------------------------------



CS02:0 -> this three clock select bits are used to select clock source to be used by the timer
-------------------------------------------------------------------------------------
	CS02	|	 CS01	|	CS00   |	Description									|
------------------------------------------------------------------------------------|
	 0		|	  0		|	 0	   |	No Clock Source (Disable Clock)				|
	 0		|	  0		| 	 1	   |	No Prescaler Same as system Clock			|
	 0		|	  1		| 	 0	   |	CLk/8										|
	 0		|	  1		| 	 1     |	CLK/64										|
	 1		|	  0		| 	 0     |	CLK/256										|
	 1		|	  0		|	 1     |	CLK/1024									|
	 1		|	  1		|	 0     |	EXTERNAL CLOCk on T0 Clock on falling edge	|
	 1		|	  1		|	 1     |	EXTERNAL CLOCk on T0 Clock on rising edge	|
-------------------------------------------------------------------------------------


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





#endif /* MYDRIVERS_MCAL_TIMERS_TIMER0_H_ */
