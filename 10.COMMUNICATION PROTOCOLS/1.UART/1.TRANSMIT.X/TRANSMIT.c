
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

void transmit(){
    char *ptr= "Hello There!";
    int i=0;
    while(*ptr !='\0'){
         while(TXIF==0);
    TXREG=*ptr;
    ptr++;
    }
    
}
void main() {
    PORTC=TRISC=0X00;
    
    SPBRG=25;
    RCSTA=0X80;
    TXSTA=0X26;
    
    while(1){
        transmit();
    }
    return;
}