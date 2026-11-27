#include <avr/io.h>

void delay(unsigned long k){
	while(--k!=0);
}

float convert(unsigned int a){
    float c;
    c = (a * 1.075)/10;
    return(c);
}

void sendData(unsigned char w){
    while((UCSR0A & 0x20)==0);
    UDR0 = w;
}

void sendtemp(unsigned int num){
	unsigned char n[7],x;
    float t;
    unsigned int tc;
    
    t = convert(num);
    tc= t*10;
	// Convert the ADC value to
	// temperature.

	n[0] = (tc/100)+0x30;
    n[1] = ((tc%100)/10)+ 0x30 ;
	n[2] = '.';
    n[3] = (tc%10)+0x30;
	n[4] = 'C';
	n[5] = 0x0A;
	n[6] = 0x0D;

	// Convert the digit to send
	// to ASCII characters.

	for(x=0;x<7;x++){
    sendData(n[x]);
	}
}

void ADC_Init(){
  DIDR0 = 0x20;  // Disable digital. 
  DDRC = DDRC & ~(0x20);  
  ADCSRA |= 0x87; // Set clock.
  ADMUX = 0xC5; // Vref=1.1V
}

unsigned int ADC_Read(){ 
  ADCSRA |= 0x40; // Start ADC.
  while ((ADCSRA & 0x10)==0); // Wait. 
  ADCSRA |= 0x10; // Reset.
  return ADCW; 
}

void SerialInit(){
    UCSR0B |= 0x18;
    UBRR0= 0x67;
}

int main()
{
	unsigned int adcValue;
	SerialInit();
	ADC_Init();
	while(1){
		adcValue = ADC_Read();
		sendtemp(adcValue);
		delay(200000);
	}
}
