#include <stdio.h>
#include <stdint.h>

int main(void)
{
	// variables
	int8_t x = 12;
	int8_t y = 10;
	int8_t t;
	
	// simple calculations
	y = x + 2;
	t = y;
	x = t;
	
	// output variables
	printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("t = %d\n", t);
	
	
	return (0);
}
