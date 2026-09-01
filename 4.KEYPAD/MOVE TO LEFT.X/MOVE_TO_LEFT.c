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

unsigned int old_num = 0;
char seg[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};

void delay(unsigned char a){
    while(a--);
}

void main(void){
    ANSEL=0x00;
    ANSELH=0x00;
    TRISA=0x00;
    TRISB=0x00;
    TRISD=0x00;
    TRISE=0x07;
    PORTA=0x00;
    PORTB=0x00;
    PORTD=0x00;
    PORTE=0x00;

    while(1){
        //ROW A 
        RD0=1; RD1=0; RD2=0; RD3=0;
        if(RE0==1){ PORTA=seg[1]; delay(10); while(RE0==1); old_num=(old_num*10+1)%10000; }
        if(RE1==1){ PORTA=seg[2]; delay(10); while(RE1==1); old_num=(old_num*10+2)%10000; }
        if(RE2==1){ PORTA=seg[3]; delay(10); while(RE2==1); old_num=(old_num*10+3)%10000; }

        //ROW B 
        RD0=0; RD1=1; RD2=0; RD3=0;
        if(RE0==1){ PORTA=seg[4]; delay(10); while(RE0==1); old_num=(old_num*10+4)%10000; }
        if(RE1==1){ PORTA=seg[5]; delay(10); while(RE1==1); old_num=(old_num*10+5)%10000; }
        if(RE2==1){ PORTA=seg[6]; delay(10); while(RE2==1); old_num=(old_num*10+6)%10000; }

        //ROW C
        RD0=0; RD1=0; RD2=1; RD3=0;
        if(RE0==1){ PORTA=seg[7]; delay(10); while(RE0==1); old_num=(old_num*10+7)%10000; }
        if(RE1==1){ PORTA=seg[8]; delay(10); while(RE1==1); old_num=(old_num*10+8)%10000; }
        if(RE2==1){ PORTA=seg[9]; delay(10); while(RE2==1); old_num=(old_num*10+9)%10000; }

        //ROW D 
        RD0=0; RD1=0; RD2=0; RD3=1;
        if(RE1==1){ PORTA=seg[0]; delay(10); while(RE1==1); old_num=(old_num*10+0)%10000; }

      //DISPLAY REFRESH 
        unsigned char d1=(old_num/1000)%10;
        unsigned char d2=(old_num/100)%10;
        unsigned char d3=(old_num/10)%10;
        unsigned char d4=old_num%10;

        PORTB=0x00; PORTA=seg[d1]; RB0=1; delay(150); RB0=0;
        PORTB=0x00; PORTA=seg[d2]; RB1=1; delay(150); RB1=0;
        PORTB=0x00; PORTA=seg[d3]; RB2=1; delay(150); RB2=0;
        PORTB=0x00; PORTA=seg[d4]; RB3=1; delay(150); RB3=0;
    }
}
/*#include <xc.h>

unsigned int new_num = 0;
unsigned int old_num = 0;
unsigned int digit = 0;

char seg[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};

void delay(unsigned char a){
    while(a--);
}

void number(unsigned int num1){
  // Updates the running number
    digit = num1;
    new_num = ((old_num * 10) + digit)%10000;
    old_num = new_num;
}

void display_number(unsigned int num){
    // Refreshes all 4 digits ONE TIME through (call this every loop!)
    unsigned char d1 = (num/1000)%10;
    unsigned char d2 = (num/100)%10;
    unsigned char d3 = (num/10)%10;
    unsigned char d4 = num%10;

    PORTB=0x00; PORTA=seg[d1]; RB0=1; delay(150); RB0=0;
    PORTB=0x00; PORTA=seg[d2]; RB1=1; delay(150); RB1=0;
    PORTB=0x00; PORTA=seg[d3]; RB2=1; delay(150); RB2=0;
    PORTB=0x00; PORTA=seg[d4]; RB3=1; delay(150); RB3=0;
}


void main(void){    
    char seg[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};
    ANSEL=0x00;
    ANSELH=0x00;
    
    TRISA=0x00;      // Segments
    TRISB=0x00;      // Digit select
    TRISD=0x00;      // Rows
    TRISE=0x07;      // Columns
    
    PORTA=0x00;
    PORTB=0x00;
    PORTD=0x00;
    PORTE=0x00;
    
    while(1){
        RD0=1; RD1=0 ; RD2=0; RD3=0;
        if(RE0 == 1){digit=1; PORTA = seg[1]; delay(10); while(RE0==1); number(digit);}
        if(RE1 == 1){digit=2; PORTA = seg[2]; delay(10); while(RE1==1); number(digit);}
        if(RE2 == 1){digit=3; PORTA = seg[3]; delay(10); while(RE2==1); number(digit);}
        
        RD0=0; RD1=1 ; RD2=0; RD3=0;
        if(RE0 == 1){digit=4; PORTA = seg[4]; delay(10); while(RE0==1); number(digit);}
        if(RE1 == 1){digit=5; PORTA = seg[5]; delay(10); while(RE1==1); number(digit);}
        if(RE2 == 1){digit=6; PORTA = seg[6]; delay(10); while(RE2==1); number(digit);}
        
        RD0=0; RD1=0 ; RD2=1; RD3=0;
        if(RE0 == 1){digit=7; PORTA = seg[7]; delay(10); while(RE0==1); number(digit);}
        if(RE1 == 1){digit=8; PORTA = seg[8]; delay(10); while(RE1==1); number(digit);}
        if(RE2 == 1){digit=9; PORTA = seg[9]; delay(10); while(RE2==1); number(digit);}
        
        RD0=0; RD1=0 ; RD2=0; RD3=1;
        if(RE1 == 1){digit=0; PORTA = seg[0]; delay(10); while(RE1==1); number(digit);}
        
        display_number(old_num);
    }
}*/

