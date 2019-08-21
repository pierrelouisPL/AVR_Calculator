#ifndef _8SEG_H_
#define _8SEG_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

// const. description in pdf documentation
#define PORTB_MASK 0x3E
#define PORTD_MASK 0x19
#define B0_MASK 0x41
#define D0_MASK 0xC6
#define B1_MASK 0
#define D1_MASK 0x42
#define B2_MASK 0x81
#define D2_MASK 0x86
#define B3_MASK 0x80
#define D3_MASK 0xC6
#define B4_MASK 0xC0
#define D4_MASK 0x42
#define B5_MASK 0xC0
#define D5_MASK 0xC4
#define B6_MASK 0xC1
#define D6_MASK 0xC4
#define B7_MASK 0
#define D7_MASK 0x46
#define B8_MASK 0xC1
#define D8_MASK 0xC6
#define B9_MASK 0xC0
#define D9_MASK 0xC6

// precise PORTB and PORTD register description is provided in documentation
void displayPinSetup() {
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB6) | (1 << PB7);
	DDRD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
}

// turns on segments defined for a digit given as an argument
// (a chosen display has to be turned on separately)
void displayDigit(int n) {
	switch(n) {
		case 0:
			PORTB &= PORTB_MASK;
			PORTB |= B0_MASK;
			PORTD &= PORTD_MASK;
			PORTD |= D0_MASK;
			break;
		case 1:
			PORTB &= PORTB_MASK;
			PORTB |= B1_MASK;
			PORTD &= PORTD_MASK;
			PORTD |= D1_MASK;
			break;
		case 2:
			PORTB &= PORTB_MASK;
			PORTB |= B2_MASK;
			PORTD &= PORTD_MASK;
			PORTD |= D2_MASK;
			break;
		case 3:		
			PORTB &= PORTB_MASK;
			PORTB |= B3_MASK;
			PORTD &= PORTD_MASK;
			PORTD |= D3_MASK;
			break;
		case 4:		
			PORTB &= PORTB_MASK;
			PORTB |= B4_MASK;
			PORTD &= PORTD_MASK;
			PORTD |= D4_MASK;
			break;
		case 5:		
			PORTB &= PORTB_MASK;
			PORTB |= B5_MASK;
			PORTD &= PORTD_MASK;
			PORTD |= D5_MASK;
			break;
		case 6:		
			PORTB &= PORTB_MASK;
			PORTB |= B6_MASK;
			PORTD &= PORTD_MASK;
			PORTD |= D6_MASK;
			break;
		case 7:		
			PORTB &= PORTB_MASK;
			PORTB |= B7_MASK;
			PORTD &= PORTD_MASK;
			PORTD |= D7_MASK;
			break;
		case 8:		
			PORTB &= PORTB_MASK;
			PORTB |= B8_MASK;
			PORTD &= PORTD_MASK;
			PORTD |= D8_MASK;
			break;
		case 9:		
			PORTB &= PORTB_MASK;
			PORTB |= B9_MASK;
			PORTD &= PORTD_MASK;
			PORTD |= D9_MASK;
			break;
	
		default:
			break;
		
	}
}


// turns on a display which id is given as an argument
/* IMPORTANT!!!
 * DISPLAY 0 IS WIRED THROUGH AN NPN TRANSISTOR SO IT'S ON WHEN 1 IS SET AS
 * OPPOSED TO THE OTHER DISPLAYS => further explanation in the pdf documentation */
void selectDisplay(int n) {
	switch (n) {
		case 0:
			PORTD |= (1 << PD4);
			PORTD |= (1 << PD3);
			PORTB |= (1 << PB1);
			PORTB |= (1 << PB2);
			break;
		case 1:
			PORTD &= ~(1 << PD4);
			PORTD &= ~(1 << PD3);
			PORTB |= (1 << PB1);
			PORTB |= (1 << PB2);
			break;
		case 2:
			PORTD &= ~(1 << PD4);
			PORTD |= (1 << PD3);
			PORTB &= ~(1 << PB1);
			PORTB |= (1 << PB2);
			break;
		case 3:
			PORTD &= ~(1 << PD4);
			PORTD |= (1 << PD3);
			PORTB |= (1 << PB1);
			PORTB &= ~(1 << PB2);
			break;
		default:
			//
			break;

	}
}

// displays digits provided as an array in the argument
void displayDigits(int digits[4]) {
	for (int i = 0; i < 4; i++) {
		selectDisplay(i);
		displayDigit(digits[i]);
		_delay_ms(1);
	}
}


#endif 