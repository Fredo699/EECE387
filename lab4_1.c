#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define ECHO_PIN11 (PINB & (1 << PB1))
#define ECHO_PIN12 (PINB & (1 << PB2))

uint8_t tocks1, tocks2 = 0;
uint16_t ticks1, ticks2 = 0;
uint8_t echo_flag1, echo_flag2;
uint8_t delay_flag = 1;
uint8_t start_time1, start_time2 = 0;

uint16_t cm;

int main(void) { DDRB |= 0x01;   // B0 an output
    DDRB &= ~(0x02);// B1 an input

	DDRC |= (7 << PC0);
 
    TCCR0A |= (1 << CS00);
    TCCR0B |= (1 << CS00);
	TIMSK0 = (1 << TOIE0);

	sei();
    // send first trig pulse
    PORTB |= (1 << PB0);
    _delay_us(10);
    PORTB &= ~(1 << PB0);
	
	while(1)
	{
        if (echo_flag && !(PINB & (1 << PB1))) // We are in the echo state, but it just ended
        {
            if (tocks > 0) delay_flag = 0;
            ticks = 255 * tocks + (uint8_t)(TCNT0 - start_time);
            echo_flag = 0;

            _delay_ms(60); // wait before trig (see datasheet)
            
            // send trig
            PORTB |= (1 << PB0); 
            _delay_us(10);
            PORTB &= ~(1 << PB0);

            if (!delay_flag){
                cm = ticks / 58;
                if (cm < 10) PORTC |= (1 << PC0); // less than 10 cm away
                else PORTC &= ~(1 << PC0);
                delay_flag = 1;
            }

            tocks = 0;
        }

        else if (!echo_flag && (PINB & (1 << PB1))){ 
            echo_flag = 1;
            start_time = TCNT0;
        }

	}
}

ISR(TIMER0_OVF_vect)
{
    if (ECHO_PIN1) tocks++;
    PORTC ^= (1 << PC2); // debug to see how long this takes
}
