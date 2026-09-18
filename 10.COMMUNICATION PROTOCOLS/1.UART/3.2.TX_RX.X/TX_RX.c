/*
 * File:   receive.c
 * Author: subik
 *
 * Created on 18 September, 2026, 11:45 AM
 */
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
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
void delay(unsigned long int a)
{
    while(a--);
}
void enable()
{
     RE1=1;
     delay(100);
     RE1=0;
     delay(100);
}
void lcd(char rs, char value)
{
   RE0=rs;
   PORTD=value;
   enable();   
}
void string(char *ptr)
{
    while(*ptr)
    {
        lcd(1,*ptr++);
    }
}
void receiver()
{
    while(!(RCIF==1));
    char value = RCREG;
    RCIF=0;
    lcd(1,value);
}
void main()
{
    TRISD=TRISE=0X00;
    TRISC=0X80;
    PORTC = PORTD = PORTE=0X00;
    ANSEL=0X00;
    ANSELH=0X00;
    SPBRG=25;
    TXSTA=0X26;
    RCSTA=0X90;
    delay(1000);
    lcd(0, 0x38);
    lcd(0, 0x0E);
    lcd(0, 0x80);
    while(1)
    {
       // string("hello");
        receiver();
    }   
}