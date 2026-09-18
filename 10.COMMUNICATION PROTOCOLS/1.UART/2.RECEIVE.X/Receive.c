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

void delay(unsigned int a)
{
    while(a--);
}

void lcd(char rs, char data)
{
    RE0 = rs;
    
    PORTD = (data & 0xF0) >> 4;
    RE1 = 1;
    delay(100);
    RE1 = 0;
    delay(1000);

    PORTD = data & 0x0F;
    RE1 = 1;
    delay(100);
    RE1 = 0;
    delay(1000);
}

void receive()
{
    while(!RCIF);

    char value = RCREG;

    lcd(1,value);
}

void main()
{
    ANSEL = 0x00;
    ANSELH = 0x00;

    TRISC = 0x80;     // RC7 RX input
    TRISD = 0x00;     // LCD data
    TRISE = 0x00;     // LCD control

    PORTD = 0x00;
    PORTE = 0x00;

    SPBRG = 25;       // 9600 baud @ 4MHz
    TXSTA = 0x26;
    RCSTA = 0x90;

    delay(10000);
    lcd(0,0x02);
    lcd(0,0x28);   // 4-bit, 2 line, 5x8 font
    lcd(0,0x0C);   // Display ON
    lcd(0,0x06);   // Cursor increment
    lcd(0,0x01);
    delay(10000);
    

    while(1)
    {
        receive();
    }
}