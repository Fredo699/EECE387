#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>



#define pwm_coma1 7
#define pwm_coma0 6
#define pwm_comb1 5
#define pwm_comb0 4

#define pwm_wgm0 0
#define pwm_wgm1 1
#define pwm_wgm2 3

#define pwm_cs0 0
#define pwm_cs1 1
#define pwm_cs2 2

double dutyCycle = 0;

int main(void)
{
	DDRD = (1 << PORTD6);
	
	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK0 = (1 << TOIE0);
	
	OCR0A = (dutyCycle/100.0)*255.0;
	
	sei();
	
	TCCR0B = (1 << CS00) | (1 << CS02);
	
	while(1)
	{
		_delay_ms(1000);
		
		dutyCycle += 10;
		
		if(dutyCycle > 100)
		{
			dutyCycle = 0;
		}
	}
}

ISR(TIMER0_OVF_vect)
{
	OCR0A = (dutyCycle/100.0)*255;
}
