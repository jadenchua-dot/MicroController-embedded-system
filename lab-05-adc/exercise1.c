#include <avr/io.h>

void delay(unsigned long z){
    while(--z!=0);
}

void display(unsigned int num){
    unsigned char a,b,c,x;
    a = num/100;
    b = (num%100)/10;
    c = num%10;
    for(x=0;x<100;x++){
        PORTB = (PORTB & 0xF8) | 0x01;
        PORTC = (PORTC & 0xF0) | a;
        delay(10);
        PORTB = (PORTB & 0xF8) | 0x02;
        PORTC = (PORTC & 0xF0) | b;
        delay(10);
        PORTB = (PORTB & 0xF8) | 0x04;
        PORTC = (PORTC & 0xF0) | c;
        delay(10);
    }
}

void ADC_Init(){
    DIDR0 = 0x30;
    DDRC &= ~0x30;
    PORTC &= ~0x30;
    ADCSRA |= 0X87;
    ADMUX |= 0xc0;
}

float convert(unsigned int x){
float c;
c = (x * 1.075); 
return (c);
}

unsigned int ADC_Read(unsigned char channel){
    ADMUX = (ADMUX & 0xf0) | channel;
    ADCSRA |= 0x40;
    while((ADCSRA & 0x10)==0);
    ADCSRA |= 0x10;
    return ADCW;
}

int main(){
    unsigned int adcValue;
    float t;
    DDRC |= 0x0f;
    DDRB |= 0x07;
    ADC_Init();
    while(1){
        adcValue = ADC_Read(5);
        t = convert(adcValue);
        display(t);
    }
}
