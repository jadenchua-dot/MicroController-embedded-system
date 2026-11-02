#include <avr/io.h>

int main(){
    unsigned long x;
    DDRD  = 0xff;
    while(1){
        PORTD &= ~(0x04);
        for(x=0;x<300000;x++);
        PORTD &= ~(0x02);
        for(x=0;x<300000;x++);
      
    }
}

