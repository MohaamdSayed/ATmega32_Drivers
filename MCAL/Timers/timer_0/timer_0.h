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
 * Timer 0 is a hardware timer in the AVR Microcontroller used for various timing and
 * counting operations. This module provides functionalities to initialize Timer 0,
 * set its mode of operation, configure interrupts, and control its behavior.
 */

#ifndef ATMEGA32_DRIVERS_TIMER0_H_
#define ATMEGA32_DRIVERS_TIMER0_H_

#include "../../../std_types.h"
#include "../../../common_macros.h"
#include "../../Atmega32_Registers.h"
/**
 * @brief THE REGISTERRS USED BY TIMER0 and there address
 *
 */


/**
 @brief Here you can find all the the information related to the Timer0
 hardware found in the official data sheet.

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
} TIMER0_MODE;

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
} TIMER0_CLK;

/**
 * @brief
 *
 */
typedef enum {
	TIMER0_OC0_DISCONNECTED = 0, /**< TIMER0_OC0_DISCONNECTED */
	TIMER0_OC0_TOGGLE = 1, /**< TIMER0_OC0_TOGGLE */
	TIMER0_OC0_CLEAR = 2, /**< TIMER0_OC0_CLEAR */
	TIMER0_OC0_SET = 3, /**< TIMER0_OC0_SET */

} TIMER0_OC0_Control;

/**
 * @brief this enum holds the available interrupt enable types.
 *
 */
typedef enum {
	TIMER0_INTERRUPT_OVERFLOW, TIMER0_INTERRUPT_OUTPUT_COMPARE_MATCH

} TIMER0_interrupt_type;

/**
 * @brief Represent The Settings used to initialize the Timer 0
 *
 */
typedef struct {
	TIMER0_MODE mode;
	TIMER0_CLK clock;
	TIMER0_OC0_Control OC0;
} TIMER0_Config;

/**
 * @brief used to define the type of the callback function
 *
 */
typedef void (*Timer0Callback)(void);

typedef void (*TimerFunction)(void);

typedef uint8 (*uint8TimerFunction)(void);

typedef void (*TimerFunctionUint8)(uint8);

typedef void (*TimerFunctionCallback)(Timer0Callback);

typedef void (*TimerFunctionMode)(TIMER0_MODE);

typedef void (*TimerFunctionCLK)(TIMER0_CLK);

typedef void (*TimerFunctionOC0)(TIMER0_OC0_Control);

typedef struct {
	TimerFunctionMode mode;
	TimerFunctionCLK clk;
	TimerFunctionOC0 OC0;

} Timer0_Config;

typedef struct {
	Timer0_Config init;
	TimerFunction stop;
	TimerFunction start;
	TimerFunctionUint8 setStart;
	uint8TimerFunction getTicks;
	TimerFunctionUint8 setCompare;
	TimerFunction enableOverFlowInterrupt;
	TimerFunction enableCTCInterrupt;
	TimerFunction disableOverFlowInterrupt;
	TimerFunction disableCTCInterrupt;
	uint8TimerFunction getOverFlowFlag;
	uint8TimerFunction getCTCFlag;
	TimerFunctionCallback setOverFlowCallback;
	TimerFunctionCallback setCTCCallback;

} TIMER0;

/**
 * @brief function prototypes for
 *
 */

void set_Clock(TIMER0_CLK clk);

void OC0_control(TIMER0_OC0_Control OC0);

void SetMode(TIMER0_MODE);

#define TIMER0SETTINGS() {SetMode,set_Clock,OC0_control}

//void TIMER0_init(TIMER0_Config *);

void TIMER0_stop(void);

void TIMER0_start(void);

void TIMER0_setStart(uint8);

uint8 TIMER0_getTicks(void);

void TIMER0_set_compare_value(uint8 compValue);

void enableOverFlowInterrupt(void);

void enableCTCInterrupt(void);

void disableOverFlowInterrupt(void);

void disableCTCInterrupt(void);

uint8 getOverFlowFlag(void);

uint8 getCTCFlag(void);

void setOverFlowCallback(Timer0Callback);

void setCTCCallback(Timer0Callback);

#define NEWTIMER0() {TIMER0SETTINGS(),TIMER0_stop,TIMER0_start,TIMER0_setStart,TIMER0_getTicks,TIMER0_set_compare_value,enableOverFlowInterrupt,enableCTCInterrupt,disableOverFlowInterrupt,disableCTCInterrupt,getOverFlowFlag,getCTCFlag,setOverFlowCallback,setCTCCallback}

#endif /* ATMEGA32_DRIVERS_TIMER0_H_ */
