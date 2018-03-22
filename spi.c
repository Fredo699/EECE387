#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DDR_SPI (DDRB)
#define DD_MOSI (PB3)
#define DD_MISO (PB4)
#define DD_SCK  (PB5)

void SPI_MasterInit(void)
{
    // set MOSI and SCK to output, all others input
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
    // enable SPI, Master, set clock rate fck/16
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(char c)
{
    SPDR = c;
    while (!(SPSR & (1<<SPIF))); // wait for transmission complete
}

void SPI_SlaveInit(void)
{
    // set MISO output, all others input
    DDR_SPI = (1<<DD_MISO);
    // Enable SPI
    SPCR = (1<<SPE);
}

char SPI_SlaveReceive(void)
{
    // Wait for reception complete
    while (!(SPSR & (1<<SPIF)));

    return SPDR;
}

char c = 'a';

int main(void)
{

    DDRC = (1<<PC5);
	
	while(1)
	{
    SPI_MasterInit();
    SPI_MasterTransmit(c);
    PORTC ^= (1<<PC5);
    c++;

    _delay_ms(1000);
	}
}
