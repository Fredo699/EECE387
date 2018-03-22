#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define DB_DELAY 1000;

uint16_t adc;
uint16_t i;

int main (void)
{
	
    // Turn on Port D
	DDRD |= (1 << PORTD5);

	/* Insert application code here, after the board has been initialized. */
	// set up ADC
    ADCSRA |= ((1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE) | (7 << ADPS0)); // enable ADC
	ADCSRB &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));    // free-running mode
    ADCSRB |= (1 << ACME); // comparator mux enable
    ADMUX = 0x05;
	
	// Logic that takes in the potentiometer voltage and determines if LED is lit
	while(1){
        if (ADCW > 512){
            i = DB_DELAY;
            while (--i);
            if (ADCW > 512) PORTD |= (1 << PD5);
        }
        else PORTD &= ~(1 << PD5);
    }
	
	return (0);
}
