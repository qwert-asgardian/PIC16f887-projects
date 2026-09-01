#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = ON
#pragma config FCMEN = ON
#pragma config LVP = OFF
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF

#include <xc.h>

void delay(unsigned long i)
{
    while(i--);
}

void main(void)
{
    ANSEL  = 0;
    ANSELH = 0;
    TRISA  = 0;
    PORTA  = 0;

    unsigned char a = 0;      
    unsigned char i;
    unsigned char count = 0;

    while(1){
        for(i = 0; i <= (7 - count); i++){
            PORTA = 1 << i | a;
            delay(1500);
        }
        a |= 1<<(7-count);
        count++;
        if(count==8){
        for(i=0; i<=7;i++){
            PORTA &=(~(1<<i));
            delay(1500); 
        }
        count = 0;
        a = 0;
      
    }
}
}