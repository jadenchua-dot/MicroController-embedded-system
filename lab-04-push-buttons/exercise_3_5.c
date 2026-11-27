#include <avr/io.h>
#define ON 1
#define OFF 0
unsigned char ledPos; // Global

void delay(unsigned long z){
    while(--z!=0);
}

unsigned char chkSw(unsigned char w){
	unsigned char status=OFF;
	if (w==1){
		if ((PINB & 0x08)==0) status = ON; //if switch 1 is on , status = ON 

            
	}
	if (w==2){
        if ((PINB & 0x10)==0) status = ON; // If SW2 is pressed, status = ON.
		
	} 
    
    if (w==3){
        if ((PINB & 0x20)==0) status = ON;  // If SW3 is pressed, status = ON.
        
    }
	return(status);
}


void goLeft(){
	ledPos = ledPos << 1;
	if (ledPos==0){
		ledPos = 0x01;  //where uw to start the led from to go left 
	}
	PORTD = ~ledPos;
	delay(50000);
}

void goRight(){
	ledPos = ledPos >> 1;
	if (ledPos==0){
		ledPos = 0x80; // where uw to start the led from to go right 
	}
	PORTD = ~ledPos;
	delay(50000);
}

void blink(){
    unsigned char x;
    for (x=0;x<20;x++){
        PORTD=~ledPos;
        delay(50000);
        PORTD=0xff;  //
        delay(50000);
    }
}

int main(){
	DDRD = 0xFF;
	DDRB &= ~(0x38);
	PORTB |= 0x38;  
	while(1){
		if (chkSw(1)==ON) goLeft();
        	if (chkSw(2)==ON) goRight();
        	if (chkSw(3)==ON) blink();
	}
}