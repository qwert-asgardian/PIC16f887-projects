#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#include <xc.h>

void delay(int a){
    while(a--);
}
void enable(){
    RE2 = 1;
    delay(10);
    RE2 = 0;
    delay(10);
}
void lcd(int rs, int value){
    RE0 = rs;
    PORTD = value;
    enable();
}
void main(){

    TRISC = 0x01;      // RA4/T1CKI input
    TRISD = 0x00;
    TRISE = 0x00;

    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;

    ANSEL = 0x00;
    ANSELH = 0x00;

    T1CON = 0x07;      // External counter mode

    TMR1= 0;

    lcd(0,0x38);
    lcd(0,0x0E);
    lcd(0,0x80);

    while(1)
    {
        lcd(0,0x80);
        lcd(1,TMR1+ 48);
    }
}