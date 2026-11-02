#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char sec=0;

void delay(unsigned long w){
	while(w--!=0);
}

void blink(){
	unsigned char k;
	for(k=0;k<10;k++){
		PORTD ^= 0xF0; //make it blink ( on and off ) change this respectively to what pins uw to blink 
		delay(100000);
	}
}
ISR(INT0_vect) {
    blink(); // it will blink when the button sw4 is pressed 
    } 

int main(){
	unsigned char x=0;
	DDRD = 0xF0;
	DDRC = 0x0F;
	DDRB = 0x07;
    sei(); // always have to enable when using interrupts
	PORTB |= 0x04;	// Mux3 on.
	PORTD &= ~(0xF0);	// Off LEDs.
	PORTD |= 0x0C; 	// Setup Inputs.
    EICRA = (EICRA & 0xfc) | 0x02;  // this is to make the INT0 to falling edge 
    EIMSK |= 0x01; 
	
	while(1){
		PORTC = (PORTC & 0xF0) | x;
		delay(400000);
		x++;
		if (x>9) x=0; // make my 3 digit run from 0 to 9 , the most right side one only 
		

	}
} 

