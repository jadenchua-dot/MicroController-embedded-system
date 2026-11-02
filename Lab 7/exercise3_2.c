#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char sec=0;

void delay(unsigned long w){
	while(w--!=0);
}
void blink(unsigned char w){
    unsigned char k;
    for(k=0;k<10;k++){
        PORTD ^= w;
        delay(100000);
    }
}

ISR(INT0_vect) {
    blink(0x30); // put this to what led uw to blink when SW1 is pressed 
}

ISR(INT1_vect) {
    blink(0xc0); // put this to what uw to blink when SW0 is Pressed 
}

int main(){
	unsigned char x=0;
	DDRD = 0xF0;
	DDRC = 0x0F;
	DDRB = 0x07;
    sei(); // always have to enable when using interrupts
	PORTB |= 0x01;	// this is for the most left 3 segment led to on , 2 is the middle , 4 is the right 
	PORTD &= ~(0xF0);	// Off LEDs.
	PORTD |= 0x0C; 	// Setup Inputs.
    EICRA = (EICRA & 0xf0) | 0x0A;  // this is to make the INT0 and INT1 to falling edge 
    EIMSK |= 0x03;  
	
	while(1){
		PORTC = (PORTC & 0xF0) | x;
		delay(400000);
		x++;
		if (x>9) x=0; // make my 3 digit run from 0 to 9 , the most right side one only 
		

	}
}

