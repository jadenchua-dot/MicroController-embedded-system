#include <avr/io.h>

int main()
{
	DDRD = 0xFF;  // Set as output.
	DDRB &= ~(0x38);
	PORTB |= 0x38;  // Set as input.
	PORTD = 0xff;  // Off all LEDs.	
	while(1)
	{
		if ((PINB & 0x08)==0){
			PORTD = 0xFC;  // On 2 LEDs.
		}
		if ((PINB & 0x10)==0){
			PORTD =  0xFF; // Off all LEDs.
		}  				
	}
}
