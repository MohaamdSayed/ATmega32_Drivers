/**
 * @file timer_1.h
 * @brief Header file for Timer 1 driver module.
 * @version 1.0
 * @date 2024-06-16
 * @author Mohamed Sayed
 *
 * @details
 * This header file contains the definition of a structure and the prototypes
 * for functions that operate on this structure to be used by the Timer 1 driver module.
 * Timer 1 is a hardware timer in the AVR Microcontroller used for various timing and
 * counting operations. This module provides functionalities to initialize Timer 1,
 * set its mode of operation, configure interrupts, and control its behavior.
 */

#ifndef ATMEGA32_DRIVERS_TIMER_1_H_
#define ATMEGA32_DRIVERS_TIMER_1_H_

#include "../../../std_types.h"
#include "../../../common_macros.h"
#include "../../../../avr/io.h"

/**
 @brief Here you can find all the the information related to the Timer0
 hardware found in the official data sheet.

 REGISTERS:
 TCCR1A -> COM1A1 | COM1A0 | COM1B1 | COM1B0 | FOC1A | FOC1B | WGM11 | WGM10
 TCCR1B -> ICNC1 | ICES1 | R | WGM13 | WGM12 | CS12 | CS11 | CS10
 TCNT1 -> TCNT1L -> 0:7 -> TCNT1H -> 8:15
 OCR1A -> OCR1AL -> 0:7 -> OCR1AH -> 8:15
 OCR1B -> OCR1BL -> 0:7 -> OCR1BH -> 8:15
 ICR1  -> ICR1L -> 0:7 -> ICR1H -> 8:15
 TIMSK -> USED | USED | TICIE1 | OCIE1A | OCIE1B | TOIE1 | USED | USED
 TIFR -> USED | USED | ICF1 | OCF1A | OCF1B | TOV1 | USED | USED




 How to use Each register
 TIMER/COUNTER 1 CONTROL REGISTER
 TCCR1A -> COM1A1 | COM1A0 | COM1B1 | COM1B0 | FOC1A | FOC1B | WGM11 | WGM10

 COM1A1:0 -> Compare Output Mode for compare unit A
 COM1B1:0 -> Compare Output Mode for compare unit B
 // -> These bits control the behavior of the OC1A , OC1B pin it overrides the GPIO Settings
 // -> Note to set/drive Power using OC1 you need to set the DDR (data direction Register)

 this Table Work With mode NORMAL / CTC
  -----------------------------------------------------------------------------------
 COM1A1/COM1B1	|  COM1A0/COM1B0	|	Description									|
 ------------------------------------------------------------------------------------
 0		        |	  0	    	    |	Normal port operation OC0 disconnected		|
 0		        |	  1		        |	Toggle OC0 on compare match					|
 1		        |	  0		        |	Clear OC0 on compare match					|
 1		        |	  1	        	|	set OC0 on compare match					|
 ------------------------------------------------------------------------------------


 TCCR1A -> COM1A1 | COM1A0 | COM1B1 | COM1B0 | FOC1A | FOC1B | WGM11 | WGM10

 */
typedef enum {
    TIMER1_OC1A_DISCONNECTED = 0,
    TIMER1_OC1A_TOGGLE = 1,
    TIMER1_OC1A_CLEAR = 2,
    TIMER1_OC1A_SET = 3,
} TIMER1_OC1A_Control;
typedef enum {
    TIMER1_OC1B_DISCONNECTED = 0,
    TIMER1_OC1B_TOGGLE = 1,
    TIMER1_OC1B_CLEAR = 2,
    TIMER1_OC1B_SET = 3,
} TIMER1_OC1B_Control;

typedef enum {
    TIMER1_MODE_NORMAL = 0,
    TIMER1_MODE_CTC = 4
} TIMER1_MODE;


typedef enum {
    TIMER1_CLK_NO_CLOCK, /**< TIMER0_CLK_NO_CLOCK */
    TIMER1_CLK_SYSTEM, /**< TIMER0_CLK_SYSTEM */
    TIMER1_CLK_SYSTEM_8, /**< TIMER0_CLK_SYSTEM_8 */
    TIMER1_CLK_SYSTEM_64, /**< TIMER0_CLK_SYSTEM_64 */
    TIMER1_CLK_SYSTEM_265, /**< TIMER0_CLK_SYSTEM_265 */
    TIMER1_CLK_SYSTEM_1024, /**< TIMER0_CLK_SYSTEM_1024 */
    TIMER1_CLK_SYSTEM_EXTERNAL_FALING,/**< TIMER0_CLK_SYSTEM_EXTERNAL_FALING */
    TIMER1_CLK_SYSTEM_EXTERNAL_RISING, /**< TIMER0_CLK_SYSTEM_EXTERNAL_RISING */
} TIMER1_CLK;


typedef enum {
    TIMER1_INTERRUPT_OVERFLOW,
    TIMER1_INTERRUPT_OUTPUT_COMPARE_MATCH_A,
    TIMER1_INTERRUPT_OUTPUT_COMPARE_MATCH_B,

} TIMER1_interrupt_type;

typedef void (*Timer1Callback)(void);

void TIMER1_SetMode(TIMER1_MODE);

void TIMER1_set_Clock(TIMER1_CLK clk);

void TIMER1_start(void);

void TIMER1_OC1A_control(TIMER1_OC1A_Control OC1A);

void TIMER1_OC1B_control(TIMER1_OC1B_Control OC1B);

void TIMER1_stop(void);

uint16 TIMER1_getTicks(void);

void TIMER1_set_compare_value_A(uint16 compValue);

void TIMER1_set_compare_value_B(uint16 compValue);


void TIMER1_enableOverFlowInterrupt(void);

void TIMER1_enable_CTC_A_Interrupt(void);

void TIMER1_enable_CTC_B_Interrupt(void);

void TIMER1_disableOverFlowInterrupt(void);

void TIMER1_disable_CTC_A_Interrupt(void);

void TIMER1_disable_CTC_B_Interrupt(void);

uint8 TIMER1_get_OverFlow_Flag(void);

uint8 TIMER1_get_CTC_A_Flag(void);

uint8 TIMER1_get_CTC_B_Flag(void);

void TIMER1_set_OverFlow_Callback(Timer1Callback);

void TIMER1_set_CTC_A_Callback(Timer1Callback);

void TIMER1_set_CTC_B_Callback(Timer1Callback);


#endif /* ATMEGA32_DRIVERS_TIMER_1_H_ */
