#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

uint8_t dutyCycle = 0; // duty cycle out of 255

void USART_Init(uint16_t ubrr)
{
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 1 stop bit */
    UCSR0C = (0<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

unsigned char USART_Receive( void )
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)));
    /* Get and return received data from buffer */
    return UDR0;
}

int main(void)
{
    USART_Init(BAUD_PRESCALE); // 9600 baud rate
	DDRD |= (1 << PD6);
    DDRD &= ~(1 << PD0);
    
    DDRC |= (1 << PC5);
    
	
	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK0 = (1 << TOIE0);
	
	OCR0A = dutyCycle;
	
	sei();
	
	TCCR0B = (1 << CS00) | (1 << CS02);
	
	while(1)
	{
        dutyCycle = (uint8_t) USART_Receive();
        USART_Transmit((unsigned char) dutyCycle);
        PORTC ^= (1 << PC5);
	}
}

ISR(TIMER0_OVF_vect)
{
	OCR0A = dutyCycle;
}
