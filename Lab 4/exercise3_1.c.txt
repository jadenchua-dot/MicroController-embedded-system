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
	unsigned char status=OFF; // to make all switches as (0) off
	if (w==1){
	if ((PINB & 0x08)==0) status = ON;  // If SW1 is pressed, status = ON.

            
	}
	if (w==2){
        if ((PINB & 0x10)==0) status = ON;  // If SW2 is pressed, status = ON.

		
	} 
    
    	if (w==3){
        if ((PINB & 0x20)==0) status = ON; // if sw3 is pressed, status = ON. 
        
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
		if (chkSw(1)==ON){
			onLED(0x01); // turn on led 1 if button is pressed 
            
		}
		if (chkSw(2)==ON){
            
			onLED(0x02); // turn on led 2 if button is pressed 
			
		}  				
        	if (chkSw(3)==ON){
            		onLED(0); // off all led 
        	}
	}
}