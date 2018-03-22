
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main() {

  
  DDRC = (1 << PC5 | 1 << PC4 | 1 << PC3);


  PORTC |= 1 << PC5;

 
  PORTC &= ~(1 << PC4);

 
  while(1) {

  
    _delay_ms(1);

   
    PORTC ^= 1 << PC3;
  }
  return 1;

}
