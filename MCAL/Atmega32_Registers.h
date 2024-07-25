/**
 * @file Atmega32_Registers
 * @brief [Brief description of the file]
 * @date 02-Jul-24
 * @author Mohamed Sayed
 */

#ifndef ATMEGA32_ETAMINI_ATMEGA32_REGISTERS_H
#define ATMEGA32_ETAMINI_ATMEGA32_REGISTERS_H

#define SREG (*(volatile uint8 *)((0x3F) + 0x20))

#define SP (*(volatile uint16 *)((0x3D) + 0x20))
#define SPH (*(volatile uint8 *)((0x3E) + 0x20))
#define SPL (*(volatile uint8 *)((0x3D) + 0x20))

#define OCR0 (*(volatile uint8 *)((0x3C) + 0x20))
#define GICR (*(volatile uint8 *)((0x3B) + 0x20))
#define GIFR (*(volatile uint8 *)((0x3A) + 0x20))
#define TIMSK (*(volatile uint8 *)((0x39) + 0x20))
#define TIFR (*(volatile uint8 *)((0x38) + 0x20))
#define SPMCR (*(volatile uint8 *)((0x37) + 0x20))
#define TWCR (*(volatile uint8 *)((0x36) + 0x20))
#define MCUCR (*(volatile uint8 *)((0x35) + 0x20))
#define MCUCSR (*(volatile uint8 *)((0x34) + 0x20))
#define TCCR0 (*(volatile uint8 *)((0x33) + 0x20))
#define TCNT0 (*(volatile uint8 *)((0x32) + 0x20))
#define OSCCAL (*(volatile uint8 *)((0x31) + 0x20))
#define OCDR (*(volatile uint8 *)((0x31) + 0x20))
#define SFIOR (*(volatile uint8 *)((0x30) + 0x20))
#define TCCR1A (*(volatile uint8 *)((0x2F) + 0x20))
#define TCCR1B (*(volatile uint8 *)((0x2E) + 0x20))

#define TCNT1 (*(volatile uint16 *)((0x2C) + 0x20))
#define TCNT1H (*(volatile uint8 *)((0x2D) + 0x20))
#define TCNT1L (*(volatile uint8 *)((0x2C) + 0x20))

#define OCR1A   (*(volatile uint16 *)((0x2A) + 0x20))
#define OCR1AH (*(volatile uint8 *)((0x2B) + 0x20))
#define OCR1AL (*(volatile uint8 *)((0x2A) + 0x20))

#define OCR1B (*(volatile uint16 *)((0x28) + 0x20))
#define OCR1BH (*(volatile uint8 *)((0x29) + 0x20))
#define OCR1BL (*(volatile uint8 *)((0x28) + 0x20))

#define  ICR1 (*(volatile uint16 *)((0x26) + 0x20))
#define ICR1H (*(volatile uint8 *)((0x27) + 0x20))
#define ICR1L (*(volatile uint8 *)((0x26) + 0x20))

#define TCCR2 (*(volatile uint8 *)((0x25) + 0x20))
#define TCNT2 (*(volatile uint8 *)((0x24) + 0x20))
#define OCR2 (*(volatile uint8 *)((0x23) + 0x20))
#define ASSR (*(volatile uint8 *)((0x22) + 0x20))
#define WDTCR (*(volatile uint8 *)((0x21) + 0x20))
#define UBRRH (*(volatile uint8 *)((0x20) + 0x20))
#define UCSRC (*(volatile uint8 *)((0x20) + 0x20))

#define EEAR  (*(volatile uint16 *)((0x1E) + 0x20))
#define EEARH (*(volatile uint8 *)((0x1F) + 0x20))
#define EEARL (*(volatile uint8 *)((0x1E) + 0x20))

#define EEDR (*(volatile uint8 *)((0x1D) + 0x20))
#define EECR (*(volatile uint8 *)((0x1C) + 0x20))
#define PORTA (*(volatile uint8 *)((0x1B) + 0x20))
#define DDRA (*(volatile uint8 *)((0x1A) + 0x20))
#define PINA (*(volatile uint8 *)((0x19) + 0x20))
#define PORTB (*(volatile uint8 *)((0x18) + 0x20))
#define DDRB (*(volatile uint8 *)((0x17) + 0x20))
#define PINB (*(volatile uint8 *)((0x16) + 0x20))
#define PORTC (*(volatile uint8 *)((0x15) + 0x20))
#define DDRC (*(volatile uint8 *)((0x14) + 0x20))
#define PINC (*(volatile uint8 *)((0x13) + 0x20))
#define PORTD (*(volatile uint8 *)((0x12) + 0x20))
#define DDRD (*(volatile uint8 *)((0x11) + 0x20))
#define PIND (*(volatile uint8 *)((0x10) + 0x20))
#define SPDR (*(volatile uint8 *)((0x0F) + 0x20))
#define SPCR (*(volatile uint8 *)((0x0D) + 0x20))

#define SPSR (*(volatile uint8 *)((0x0E) + 0x20))
#define UDR (*(volatile uint8 *)((0x0C) + 0x20))
#define UCSRA (*(volatile uint8 *)((0x0B) + 0x20))
#define UCSRB (*(volatile uint8 *)((0x0A) + 0x20))
#define UBRRL (*(volatile uint8 *)((0x09) + 0x20))
#define ACSR (*(volatile uint8 *)((0x08) + 0x20))
#define ADMUX (*(volatile uint8 *)((0x07) + 0x20))
#define ADCSRA (*(volatile uint8 *)((0x06) + 0x20))

#define ADC (*(volatile uint16 *)((0x04) + 0x20))
#define ADCH (*(volatile uint8 *)((0x05) + 0x20))
#define ADCL (*(volatile uint8 *)((0x04) + 0x20))

#define TWDR (*(volatile uint8 *)((0x03) + 0x20))
#define TWAR (*(volatile uint8 *)((0x02) + 0x20))
#define TWSR (*(volatile uint8 *)((0x01) + 0x20))
#define TWBR (*(volatile uint8 *)((0x00) + 0x20))
/****************************************PINS***************************************/

//UCSRA
#define MPCM 0
#define U2X 1
#define PE 2
#define DOR 3
#define FE 4
#define UDRE 5
#define TXC 6
#define RXC 7

//UCSRB
#define TXB8 0
#define RXB8 1
#define UCSZ2 2
#define TXEN 3
#define RXEN 4
#define UDRIE 5
#define TXCIE 6
#define RXCIE 7

//UCSRC
#define UCPOL 0
#define UCSZ0 1
#define UCSZ1 2
#define USBS 3
#define UPM0 4
#define UPM1 5
#define UMSEL 6
#define URSEL 7


//TWCR
#define TWIE 0
//#define UCSZ0 1
#define TWEN 2
#define TWWC 3
#define TWSTO 4
#define TWSTA 5
#define TWEA 6
#define TWINT 7
#endif //ATMEGA32_ETAMINI_ATMEGA32_REGISTERS_H
