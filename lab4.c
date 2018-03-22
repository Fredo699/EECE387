#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define ECHO_PIN1 (PINB & (1 << PB1))
#define ECHO_PIN2 (PINB & (1 << PB2))

uint8_t tocks1, tocks2 = 0;
uint16_t ticks1, ticks2 = 0;
uint8_t echo_flag1, echo_flag2;
uint8_t start_time1, start_time2 = 0;

uint16_t cm1, cm2;

int main(void) { 
    DDRB |= 0x01;   // B0 an output
    DDRB &= ~(0x02);// B1 an input
    DDRD |= (1 << PD1);
	DDRC |= (7 << PC0);
 
    TCCR0A |= (1 << CS00);
    TCCR0B |= (1 << CS00);
	TIMSK0 = (1 << TOIE0);

	sei();
    // send first trig pulse
    PORTB |= (1 << PB0);
    PORTD |= (1 << PD1);
    _delay_us(10);
    PORTB &= ~(1 << PB0);
    PORTD &= ~(1 << PD1);
	
	while(1)
	{
        if (!(ECHO_PIN1)) // We are in the echo state, but it just ended
        {
            echo_flag1 = 0;
            _delay_ms(60); // wait before trig (see datasheet)

            // send trig
            PORTB |= (1 << PB0); 
            _delay_us(10);
            PORTB &= ~(1 << PB0);

            while(!(ECHO_PIN1));
            while(ECHO_PIN1);
            ticks1 = 255 * tocks1 + (uint8_t)(TCNT0 - start_time1);

            cm1 = ticks1 / 58;
            if (cm1 < 10) PORTC |= (1 << PC0); // less than 10 cm away
            else PORTC &= ~(1 << PC0);

            tocks1 = 0;
        }

        else if (!echo_flag1 && (PINB & (1 << PB1))){ 
            echo_flag1 = 1;
            start_time1 = TCNT0;
        }

        if (!(ECHO_PIN2)) // We are in the echo state, but it just ended
        {
            echo_flag2 = 0;

            _delay_ms(60); // wait before trig (see datasheet)
            
            // send trig
            PORTD |= (1 << PD1); 
            _delay_us(10);
            PORTD &= ~(1 << PD1);
            
            while(!(ECHO_PIN2));
            while(ECHO_PIN2);
            ticks2 = 255 * tocks2 + (uint8_t)(TCNT0 - start_time2);

            cm2 = ticks2 / 58;
            if (cm2 < 10) PORTC |= (1 << PC1); // less than 10 cm away
            else PORTC &= ~(1 << PC1);

            tocks2 = 0;
        }

        else if (!echo_flag2 && (ECHO_PIN2)){ 
            echo_flag2 = 1;
            start_time2 = TCNT0;
        }

	}
}

ISR(TIMER0_OVF_vect)
{
    if (ECHO_PIN1){
        tocks1++;
        echo_flag1 = 1;
    }
    
    if (ECHO_PIN2){
        tocks2++;
        echo_flag2 = 1;
    }

    PORTC ^= (1 << PC2); // debug to see how long this takes
}
