#include <avr/io.h>

void delay(unsigned long k){  //delay funciton 
	while(--k!=0);
}

float convert(unsigned int a){  // to convert adc value into celcius 
    float c;
    c = (a * 1.075)/10;
    return(c); // return the value back into the convert() function 
}

void sendData(unsigned char w){  // to send data to the microcontroller 
    while((UCSR0A & 0x20)==0);  // to check if its 0 , 0 means finish transmitting 
    UDR0 = w; // to get the data from the varibale ontop , IF UCSR0A = 0 . 
}


void sendtemp(unsigned int num,unsigned char w){
	unsigned char n[7],x;
    float f, c;
    unsigned int tc;
	
    c = convert(num);
    tc= c * 10; // to not have decimal place so it can show 235 when its 23.5 
    if ((w=='f')||(w=='F')){    //conversion for Farads when input is f / F 
        f= (c*1.8)+32;
        tc=f*10; // to not have decimal place so it can show 743 when its 74.3 
    }
    
    n[0] = (tc/100) + 0x30;
    n[1] = ((tc%100)/10)+ 0x30;
    n[2] = '.';
    n[3] = (tc%10) + 0x30;
	n[4] = w;             // auto change to follow c or f (based on my input)
	n[5] = 0x0A;     // line feed (moves to the next line)
	n[6] = 0x0D;     // carriage return ( start from the left most line)

    for(x=0;x<7;x++){
        sendData(n[x]);
	}
}

void ADC_Init(){
  DIDR0 = 0x20;  // Disable digital. 
  DDRC = DDRC & ~(0x20);  //to turn on the temp sensor 
  ADCSRA |= 0x87; // Set clock.
  ADMUX = 0xC5; // Vref=1.1V
}

unsigned int ADC_Read(){ 
  ADCSRA |= 0x40; // Start ADC.
  while ((ADCSRA & 0x10)==0); // Wait if not 0 means its still converting 
  ADCSRA |= 0x10; // Reset. (after confirming adcsra is =0 , to clear it , set to 1 . )
  return ADCW; 
}

void SerialInit(){
    UCSR0B |= 0x18;  // enable tx and rx 
    UBRR0 = 0x67;   //make it 9600bps
}

int main()
{
	unsigned int adcValue;
    unsigned char r;
	SerialInit();
	ADC_Init();
	while(1){
		if((UCSR0A&0x80)!=0){ // check if buffer is empty , if is not empty then execute the functions 
            r=UDR0; // reading data from udr0 to send into (sendtemp()) function
            if ((r=='C')||(r=='F')||(r=='c')||(r=='f')){ // check if input is c or f 
                adcValue=ADC_Read(); 
                sendtemp(adcValue,r);
            
			}
		}
	}
}
