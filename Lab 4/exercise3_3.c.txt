#include <avr/io.h>
#define ON  1
#define OFF 0

void onLED(unsigned char w){

		// Complete your code.
    PORTD = ~w;
}
unsigned char delay(unsigned char z){
    if (z!=0);

}
    

unsigned char chkSw(unsigned char w){
	unsigned char status=OFF;
	if (w==1){
		if ((PINB & 0x08)==0) status = ON;

            
	}
	if (w==2){
        if ((PINB & 0x10)==0) status = ON;
		// If SW2 is pressed, status = ON.
	} 
    
    if (w==3){
        if ((PINB & 0x20)==0) status = ON;
        
    }
	return(status);
}



int main()
{
	// Initialization codes here.
    
    DDRD = 0xFF;  // Set as output.
	DDRB &= ~(0x38);
	PORTB |= 0x38;  // Set as input.
	PORTD = 0xff;  // Off all LEDs.	
	while(1)
	{
		while (chkSw(1)==OFF);
			onLED(0b00000001);
            
		
		while (chkSw(2)==OFF);
            
			onLED(0b00000010);
			
		  				
        while (chkSw(3)==OFF);
            onLED(0);
        
	}
}
