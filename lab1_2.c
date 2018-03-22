#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SWITCHVAR (PINB & 0x02)

uint8_t i, leds, upper, lower, switch_flag = 0;


int main() {

  
  DDRC |= 0x7F;
  DDRD |= 0x01;
  DDRB |= 0x00;
 
  while(1) {

    for (i = 0; i < 10; i++){
        _delay_ms(100);
        if (SWITCHVAR && switch_flag){
            PORTC ^= 1 << PC5;
            switch_flag = 0;
        }
        if (!SWITCHVAR) switch_flag = 1;
    }
    
    PORTC ^= 1 << PC4;
  }
  return 1;

}
