
#include <avr/io.h>
void delay(unsigned long z){
    while(z--!=0);
}



unsigned char lookup(unsigned int x){
    switch(x){
        
    
    case 0: x = 0x3F; break;
    case 1: x = 0x06; break;
    case 2: x = 0x5B; break;
    case 3: x = 0x4F; break;
    case 4: x = 0x66; break;
    case 5: x = 0x6D; break;
    case 6: x = 0x7D; break;
    case 7: x = 0x27; break;
    case 8: x = 0x7F; break;
    case 9: x = 0x6F; break;
    }
    return(x);
           
}


int main()
{
    DDRD = 0xFF;
    signed char w;
    while(1)
    {
        for(w=0;w<10;w++){
            PORTD = lookup(w);
            delay(100000);
            
        } 
        for(w=9;w>-1;w--){
            PORTD = lookup(w);
            delay(100000);
            
        }
    }
}
