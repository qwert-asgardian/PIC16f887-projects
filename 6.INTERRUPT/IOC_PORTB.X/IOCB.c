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
#define _XTAL_FREQ 4000000

void delay(unsigned int a){
    while(a--);
}

void enable(){
    RE2 = 1;
    delay(1000);
    RE2 = 0;
    delay(1000);
}

void lcd(char rs,char value){
    RE0 = rs;
    PORTD = value;
    enable();
}

void str(char *ptr){
    while(*ptr != '\0'){
        lcd(1,*ptr++);
    }}

void __interrupt() ext(){
    if(RBIF==1){
        RA0 = 1; RA1 = 0;  RA2=0;
        lcd(0,0x01);
        str("EMERGENCY STOP");
        __delay_ms(1000);
        lcd(0,0x01);
         RA0=0;
        __delay_ms(1000);
        RBIF=0;
        while(RB3==1);
        }
}

void main(void) {
    TRISB = 0x08;
    TRISA = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    PORTA = 0x00;
    PORTB = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    ANSELH=0x00;
    ANSEL = 0X00;
    
    IOCB =0x08;
    INTCON = 0x88;
    lcd(0,0x38);//FUNCTION SET - 8 BIT - 2LINE
    lcd(0,0x0E);//DISPLAY ON / CURSOR ON
    lcd(0,0x80);//FORCE CURSOR TO BEGINNING OF FIRST ROW
    
    while(1){
        lcd(0,0x01);
        RA0=1; RA1=0; RA2=0;
        str("STOP!");
        __delay_ms(1000);
        RA0=0;
        lcd(0,0x01);
        
        RA0=0; RA1=1; RA2=0;
        str("GET READY!");
        __delay_ms(1000);
        RA1=0;
        lcd(0,0x01);
        
        RA0=0; RA1=0; RA2=1;
        str("GO!");
        __delay_ms(1000);
        RA2=0;
        lcd(0,0x01);
    }
}
