#include <avr/io.h>

void serialInit(){
	UCSR0B |= 0x18;// Select the serial port pins.
    // UBRR0=0x67;// Setup baud rate.
    UBRR0 = 0xD04; //baud rate of 300 
	
}


void sendData(unsigned char y){
    while((UCSR0A & 0x20)==0);// Check transmit buffer.
	UDR0 = y; // Send data.
}
int main(){
	unsigned char w;
	serialInit();
	while(1){
		for(w=0x30;w<0x5B;w++){
            sendData(w);
		}
        sendData(0x0a);
        sendData(0x0d);
	}
}

