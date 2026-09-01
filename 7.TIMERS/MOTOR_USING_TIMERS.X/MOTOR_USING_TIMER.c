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
#define _XTAL_FREQ 4000000
int count = 0;

void tmr(){
   if(T0IF == 1) {
        count++;
        T0IF = 0;
    }
    if (count <= 1250){
        RC0 = 1; RC1 = 0;
    }
    if (count > 1250 && count <=2500){
        RC0 = 0; RC1 = 1;
    }
   if(count > 2500){
       count = 0;
       RC0=0; RC1 = 0;
       __delay_ms(100);
   }
}
   
        
void main() {
    TRISC = 0x00;
    PORTC = 0x00;
    
    OPTION_REG = 0xC3;
    TMR0 = 6;
    
    while(1){
        tmr();
    }
    
}

