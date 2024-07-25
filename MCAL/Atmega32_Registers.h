/**
 * @file Atmega32_Registers
 * @brief [Brief description of the file]
 * @date 02-Jul-24
 * @author Mohamed Sayed
 */


#ifndef ATMEGA32_ETAMINI_ATMEGA32_REGISTERS_H
#define ATMEGA32_ETAMINI_ATMEGA32_REGISTERS_H

/*******************************************************
 * TIMER 0 / 1 / 2 Registers
 ******************************************************/
#define TIMSK (*(volatile uint8 *)((0x39) + 0x20))  /*Timer/Counter Interrupt Mask*/
#define TIFR (*(volatile uint8 *)((0x38) + 0x20))   /*Timer/Counter Interrupt Flag Register*/

/**
 * Timer 0
 */
#define TCCR0 (*(volatile uint8 *)((0x33) + 0x20))  /*Timer/Counter 0 Control Register*/
#define TCNT0 (*(volatile uint8 *)((0x32) + 0x20))  /*Timer/Counter 0  Register*/
#define OCR0 (*(volatile uint8 *)((0x3C) + 0x20))   /*Output Compare Register 0  Register*/


/**
 * Timer 1
 */
#define TCCR1A (*(volatile uint8 *)((0x2F) + 0x20)) /*Timer/Counter 1 Control Register  A*/
#define TCCR1B (*(volatile uint8 *)((0x2E) + 0x20)) /*Timer/Counter 1 Control Register  B*/
#define TCNT1 (*(volatile uint8 *)((0x2C) + 0x20))  /*Timer/Counter 1 Register*/
#define OCR1A (*(volatile uint8 *)((0x2A) + 0x20))  /*Output Compare Register 1A  Register*/
#define OCR1B (*(volatile uint8 *)((0x28) + 0x20))  /*Output Compare Register 1B  Register*/



#endif //ATMEGA32_ETAMINI_ATMEGA32_REGISTERS_H
