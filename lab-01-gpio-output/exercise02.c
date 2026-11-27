#include <avr/io.h>

int main(){
    unsigned long x;
    DDRD = 0xFF;
    while(1){
        PORTD ^=0x0F;
        for(x=0;x<100000;x++);
    }
}
