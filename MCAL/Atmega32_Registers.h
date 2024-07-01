/**
 * @file Atmega32_Registers
 * @brief [Brief description of the file]
 * @date 02-Jul-24
 * @author Mohamed Sayed
 */


#ifndef ATMEGA32_ETAMINI_ATMEGA32_REGISTERS_H
#define ATMEGA32_ETAMINI_ATMEGA32_REGISTERS_H


#define TCCR0 (*(volatile uint8 *)((0x33) + 0x20))
#define TCNT0 (*(volatile uint8 *)((0x32) + 0x20))
#define OCR0 (*(volatile uint8 *)((0x3C) + 0x20))
#define TIMSK (*(volatile uint8 *)((0x39) + 0x20))
#define TIFR (*(volatile uint8 *)((0x38) + 0x20))
#define TCCR1A (*(volatile uint8 *)((0x2F) + 0x20))
#define TCCR1B (*(volatile uint8 *)((0x2E) + 0x20))
#define TCNT1 (*(volatile uint8 *)((0x2C) + 0x20))
#define OCR1A (*(volatile uint8 *)((0x2A) + 0x20))
#define OCR1B (*(volatile uint8 *)((0x28) + 0x20))


#endif //ATMEGA32_ETAMINI_ATMEGA32_REGISTERS_H
