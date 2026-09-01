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
void delay(unsigned int a){
    while(a--);
}

void enable(){
    RE1 = 1;
    delay(100);
    RE1 = 0;
    delay(100);
}

void lcd(char rs, char value){
    RE0 = rs ;
    PORTD = value & 0xF0;
    enable();
    PORTD = (value & 0x0F) << 4;
    enable();
}

void main() {
    TRISD = 0x00;
    TRISE = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    ANSEL = 0x00;
    
    lcd(0,0x02);
    lcd(0,0x28);
    lcd(0,0x0E);
    lcd(0,0x80);
    
    while(1){
        lcd(0,0x80);
        lcd(1,0x41);
    }
}
