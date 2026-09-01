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
// CONFIG2
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF

#include <xc.h>
#define _XTAL_FREQ 4000000

int count = 0;

void enable(){
    RE1 = 1;             
    __delay_ms(10);
    RE1 = 0;            
    __delay_ms(10);
}

void lcd(int rs, int value){
    RE0 = rs;
    PORTD = value;
    enable();
}

void str(char *ptr){
    while(*ptr != '\0'){
        lcd(1, *ptr++);
    }
}

void tmr(){
    if(TMR1IF == 1) {
        count++;
        TMR1IF = 0;
    }
    if (count < 10){
        RA0 = 1; RA1 = 0; RA2 = 0;
    }
    if ((count >= 10) && (count < 16)){
        RA1 = 1; RA0 = 0; RA2 = 0;
    }
    if((count >= 16) && (count < 26)){
        RA2 = 1; RA0 = 0; RA1 = 0;
    }
    if(count > 26){
        count = 0;
    }
}

void main() {
    PORTA = 0x00;
    TRISA = 0x00;
    TRISD = 0x00;
    PORTD = 0x00;
    TRISE = 0x00;
    PORTE = 0x00;
    ANSEL = 0x00;
    ANSELH = 0x00;
    T1CON = 0x31;
    TMR1 = 3036;

    lcd(0, 0x38);
    lcd(0, 0x0E);
    lcd(0, 0x80);

    while(1){
        lcd(0, 0x01);
        RA0 = 1; RA1 = 0; RA2 = 0;
        str("STOP!");
        __delay_ms(1000);
        RA0 = 0;
        lcd(0, 0x01);

        RA0 = 0; RA1 = 1; RA2 = 0;
        str("GET READY!");
        __delay_ms(1000);
        RA1 = 0;
        lcd(0, 0x01);

        RA0 = 0; RA1 = 0; RA2 = 1;
        str("GO!");
        __delay_ms(1000);
        RA2 = 0;
        lcd(0, 0x01);
    }
}