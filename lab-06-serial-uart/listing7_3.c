#include <avr/io.h>

void delay(unsigned long k){ 
	while(--k!=0);
}

void display(unsigned int w){
	unsigned char a,b,c,x;
    a = w/100;    // to make the number 1 
    b = (w%100)/10;  // to make the number 3
    c = w%10;   // to make the number 5 
    for(x=0;x<100;x++){
        PORTB= (PORTB & 0xF8)|0x01; // on the first 3 digit display
        PORTC = (PORTC & 0xF0)|a; 
        delay(100); // short delay so it shows the 3 digits at the same time 
        PORTB= (PORTB & 0xF8)|0x02; // on the second 3 digit display 
        PORTC = (PORTC & 0xF0)|b;
        delay(100);
        PORTB= (PORTB & 0xF8)|0x04; // on the third 3 digit display 
        PORTC = (PORTC & 0xF0)|c;
        delay(100);
    }
	// Put your display multiplexing
	// routine here.
	
}

void send(unsigned char d){
    while((UCSR0A & 0x20 )==0);
    UDR0 = d;
}
    
    
void SerialInit(){
    UCSR0B |= 0x18;
    UBRR0 = 0x67;
}
  
  
int main()
{
	unsigned char k,t;
	SerialInit();
	DDRC |= 0x0F;  // set output of the PC0 to PC3
	DDRB |= 0x07; // set output of the PB0 to PB2 
	while(1){
		if ((UCSR0A & 0x80)!=0 ) {
			k=UDR0;
			if ((k>=0x30) && (k<=0x39)){ // if number received is from 0 to 9 
				display(k-0x30); // to show the char what i type 
			}
			else if ((k>=0x61)&&(k<=0x7A )) {  // if the letter from a to z in hex code number 
                k= k-0x20;  // to make the letter from lowercase to upper case 
                send(k);
//				Convert data to Upper Case
//				by subtracting its ASCII code by 0x20.
//				Send back the converted data.
			}
			else {
//				Send back received data.
                send(k); // it will just show whatever i type on the tera term if its not someting from a to z 
			}
		}
	}
}
