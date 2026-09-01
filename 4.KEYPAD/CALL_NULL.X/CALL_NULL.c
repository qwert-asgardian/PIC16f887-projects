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

long int count = 0;

void delay(unsigned long int a){
    while(a--);
}

void main(void) {
    char nul[4] = {0x54,0x3E,0x38,0x38};   // N, U, L, L
    char cal[4] = {0x39,0x77,0x38,0x38};   // C, A, L, L
    long int mode = 0;

    TRISE = 0x07;   // columns: input
    TRISD = 0x00;   // rows: output
    TRISB = 0x00;   // digit enable: output
    TRISA = 0x00;   // segments: output

    PORTE = 0x00;
    PORTD = 0x00;
    PORTB = 0x00;
    PORTA = 0x00;
    ANSEL  = 0x00;
    ANSELH = 0x00;

    while(1){

        RD0=1; RD1=0; RD2=0; RD3=0;
        if(RE0==1){ count++; while(RE0==1); }
        if(RE1==1){ count++; while(RE1==1); }
        if(RE2==1){ count++; while(RE2==1); }
        delay(100);

        RD0=0; RD1=1; RD2=0; RD3=0;
        if(RE0==1){ count++; while(RE0==1); }
        if(RE1==1){ count++; while(RE1==1); }
        if(RE2==1){ count++; while(RE2==1); }
        delay(100);

        RD0=0; RD1=0; RD2=1; RD3=0;
        if(RE0==1){ count++; while(RE0==1); }
        if(RE1==1){ count++; while(RE1==1); }
        if(RE2==1){ count++; while(RE2==1); }
        delay(100);

        RD0=0; RD1=0; RD2=0; RD3=1;
        if(RE0==1){                       // '*' key
    if(count == 10) {
        mode = 1;}
    
    else{
    mode = 0;
    count = 0;
    while(RE0==1);
    }
}
if(RE1==1){                       // '0' key
        if(RE1==1){                       // '0' key
            count++;
            while(RE1==1);
        }
        delay(100);

        if(mode == 1){
            while(1){
            RB0=1; PORTA=cal[0]; delay(1000); RB0=0;
            RB1=1; PORTA=cal[1]; delay(1000); RB1=0;
            RB2=1; PORTA=cal[2]; delay(1000); RB2=0;
            RB3=1; PORTA=cal[3]; delay(1000); RB3=0;
            }}
        else{
            RB0=1; PORTA=nul[0]; delay(1000); RB0=0;
            RB1=1; PORTA=nul[1]; delay(1000); RB1=0;
            RB2=1; PORTA=nul[2]; delay(1000); RB2=0;
            RB3=1; PORTA=nul[3]; delay(1000); RB3=0;
        }
    }
}
}