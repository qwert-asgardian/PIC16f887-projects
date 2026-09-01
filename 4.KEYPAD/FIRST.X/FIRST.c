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

void delay(unsigned long int d)
{
    while(d--);
}

void main(void)
{
    //--------------- PORT CONFIGURATION -----------------
    TRISB = 0x00;      // 7-Segment Output
    TRISD = 0x00;      // Keypad Rows Output
    TRISE = 0x07;      // Keypad Columns Input

    ANSEL  = 0x00;
    ANSELH = 0x00;

    PORTB = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;

    // Common Cathode 7-Segment Codes
    unsigned char arr[10] =
    {
        0x3F,   //0
        0x06,   //1
        0x5B,   //2
        0x4F,   //3
        0x66,   //4
        0x6D,   //5
        0x7D,   //6
        0x07,   //7
        0x7F,   //8
        0x6F    //9
    };
      while(1)
{
    //--------------- ROW 1 ----------------
    RD0 = 1;
    RD1 = RD2 = RD3 = 0;
    delay(100);

    if(RE0 == 1){
        delay(100);
        PORTB = arr[1];
        while(RE0 == 1);
        delay(100);
    }

    if(RE1 == 1){
        delay(100);
        PORTB = arr[2];
        while(RE1 == 1);
        delay(100);
    }

    if(RE2 == 1){
        delay(100);
        PORTB = arr[3];
        while(RE2 == 1);
        delay(100);
    }

    //--------------- ROW 2 ----------------
    RD1 = 1;
    RD0 = RD2 = RD3 = 0;
    delay(100);

    if(RE0 == 1){
        delay(100);
        PORTB = arr[4];
        while(RE0 == 1);
        delay(100);
    }

    if(RE1 == 1){
        delay(100);
        PORTB = arr[5];
        while(RE1 == 1);
        delay(100);
    }

    if(RE2 == 1){
        delay(100);
        PORTB = arr[6];
        while(RE2 == 1);
        delay(100);
    }

    //--------------- ROW 3 ----------------
    RD2 = 1;
    RD0 = RD1 = RD3 = 0;
    delay(100);

    if(RE0 == 1){
        delay(100);
        PORTB = arr[7];
        while(RE0 == 1);
        delay(100);
    }

    if(RE1 == 1){
        delay(100);
        PORTB = arr[8];
        while(RE1 == 1);
        delay(100);
    }

    if(RE2 == 1){
        delay(100);
        PORTB = arr[9];
        while(RE2 == 1);
        delay(100);
    }

    //--------------- ROW 4 ----------------
    RD3 = 1;
    RD0 = RD1 = RD2 = 0;
    delay(100);

    if(RE0 == 1){
        delay(100);
        PORTB = arr[0];
        while(RE0 == 1);
        delay(100);
    }

    if(RE1 == 1){
        delay(100);
        PORTB = arr[0];
        while(RE1 == 1);
        delay(100);
    }

    if(RE2 == 1){
        delay(100);
        PORTB = arr[0];
        while(RE2 == 1);
        delay(100);
    }
}
}