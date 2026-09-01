
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

void delay(unsigned long int a) {
    while (a--);
}

void main(void) {
    TRISA = 0X00;      // Segments
    TRISB = 0X00;      // Digit select
    TRISD = 0X00;      // Rows
    TRISE = 0X07;      // Columns
    PORTA = 0X00;
    PORTB = 0X00;
    PORTD = 0X00;
    PORTE = 0X00;
    ANSEL = 0X00;
    ANSELH = 0X00;
    char seg[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};
    int count = 0;
    int a1, a2, a3, a4;
    int a = 0;
    int i = 0;
    int mode = 1;
    int add = 0;
    int mul = 0;
    while (1) {
        RD0 = 1;
        RD1 = 0;
        RD2 = 0;
        RD3 = 0;
        if (RE0 == 1) {
            i = 1;
            a=(a%1000)*10+i;
            while (RE0 == 1);
        }
        if (RE1 == 1) {
            i = 2;
            a=(a%1000)*10+i;
            while (RE1 == 1);
        }
        if (RE2 == 1) {
            i = 3;
            a=(a%1000)*10+i;
            while (RE2 == 1);
        }
        delay(100);
        RD0 = 0;
        RD1 = 1;
        RD2 = 0;
        RD3 = 0;
        if (RE0 == 1) {
            i = 4;
            a=(a%1000)*10+i;
            while (RE0 == 1);
        }
        if (RE1 == 1) {
            i = 5;
            a=(a%1000)*10+i;
            while (RE1 == 1);
        }
        if (RE2 == 1) {
            i = 6;
            a=(a%1000)*10+i;
            while (RE2 == 1);
        }
        delay(100);
        RD0 = 0;
        RD1 = 0;
        RD2 = 1;
        RD3 = 0;
        if (RE0 == 1) {
            i = 7;
            a=(a%1000)*10+i;
            while (RE0 == 1);
        }
        if (RE1 == 1) {
            i = 8;
            a=(a%1000)*10+i;
            while (RE1 == 1);
        }
        if (RE2 == 1) {
            i = 9;
            a=(a%1000)*10+i;
            while (RE2 == 1);
        }
        delay(100);
        RD0 = 0;
        RD1 = 0;
        RD2 = 0;
        RD3 = 1;
        if (RE0 == 1) {
            add = (a / 100)+(a % 100);
            mode = 2;
            while (RE0 == 1);
        }
        if (RE1 == 1) {
            i = 0;
            a=(a%1000)*10+i;
            while (RE1 == 1);
        }
        if (RE2 == 1) {
            mul = (a / 100) * (a % 100);
            mode = 3;
            while (RE2 == 1);  // FIXED: Changed from RE0 to RE2
        }
        delay(100);
        if (mode == 1) {
            a1 = (a / 1000) % 10;
            a2 = (a / 100) % 10;
            a3 = (a / 10) % 10;
            a4 = (a % 10);
            PORTB = 0;
            PORTA = seg[a4];
            RB0 = 1;   // FIXED: Changed from RA0 to RB0
            RB1 = 0;   // FIXED: Changed from RA1 to RB1
            RB2 = 0;   // FIXED: Changed from RA2 to RB2
            RB3 = 0;   // FIXED: Changed from RA3 to RB3
            delay(100);
            PORTB = 0;
            PORTA = seg[a3];
            RB0 = 0;
            RB1 = 1;
            RB2 = 0;
            RB3 = 0;
            delay(100);
            PORTB = 0;
            PORTA = seg[a2];
            RB0 = 0;
            RB1 = 0;
            RB2 = 1;
            RB3 = 0;
            delay(100);
            PORTB = 0;
            PORTA = seg[a1];
            RB0 = 0;
            RB1 = 0;
            RB2 = 0;
            RB3 = 1;
            delay(100);
        }
        delay(100);
        if (mode == 2) {
            a1 = (add / 1000) % 10;
            a2 = (add / 100) % 10;
            a3 = (add / 10) % 10;
            a4 = (add % 10);
            PORTB = 0;
            PORTA = seg[a4];
            RB0 = 1;
            RB1 = 0;
            RB2 = 0;
            RB3 = 0;
            delay(100);
            PORTB = 0;
            PORTA = seg[a3];
            RB0 = 0;
            RB1 = 1;
            RB2 = 0;
            RB3 = 0;
            delay(100);
            PORTB = 0;
            PORTA = seg[a2];
            RB0 = 0;
            RB1 = 0;
            RB2 = 1;
            RB3 = 0;
            delay(100);
            PORTB = 0;
            PORTA = seg[a1];
            RB0 = 0;
            RB1 = 0;
            RB2 = 0;
            RB3 = 1;
            delay(100);
        }
        delay(100);
        if (mode == 3) {
            a1 = (mul/ 1000) % 10;
            a2 = (mul/ 100) % 10;
            a3 = (mul/ 10) % 10;
            a4 = (mul% 10);
            PORTB = 0;
            PORTA = seg[a4];
            RB0 = 1;
            RB1 = 0;
            RB2 = 0;
            RB3 = 0;
            delay(100);
            PORTB = 0;
            PORTA = seg[a3];
            RB0 = 0;
            RB1 = 1;
            RB2 = 0;
            RB3 = 0;
            delay(100);
            PORTB = 0;
            PORTA = seg[a2];
            RB0 = 0;
            RB1 = 0;
            RB2 = 1;
            RB3 = 0;
            delay(100);
            PORTB = 0;
            PORTA = seg[a1];
            RB0 = 0;
            RB1 = 0;
            RB2 = 0;
            RB3 = 1;
            delay(100);
        }
    }
}