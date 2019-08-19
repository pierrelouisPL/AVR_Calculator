#ifndef _ADC_H_
#define _ADC_H_

#include <avr/io.h>

void adcSetup() {
	// sets prescaler factor to 128
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

int adcRead() {
	// start conversion
	ADCSRA |= (1 << ADSC);
	// wait until it's finished
	while(ADCSRA & (1 << ADSC));
	// returns conversion result
	return(ADC);
}

#endif