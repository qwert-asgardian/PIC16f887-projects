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
int sampling1 = 0;
int sampling2 = 0;
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;
int g = 0;
int x = 0;
int y = 0;
int z = 0;
int poten = 0;
int percentage = 0;

void delay(int count) {
    while (count--);
}

void lcd(int rs, int data) {
    RE0 = rs;
    PORTD = data;
    RE1 = 1;
    delay(1000);
    RE1 = 0;
    delay(1000);
}

void ADC1() {
    GO = 1; // TELLS ADC TO START CONVERSION
    while (GO == 1); // WAIT TILL CONVERSION ENDS AND STORES DATA IN ADRESL AND ADRESH
    sampling1 = ADRESL | (ADRESH << 8); // 00 = 0*256 ; 01 = 1*256 ; 10 = 2*256 ; 11 = 3*256   (ADRESL = 255 + (00)= 255) (ADRESL = 255 + (10)= 511) 

    CCPR1L = sampling1 >> 2;
    CCP1CON |= ((sampling1 << 4)&0x30);
    
    // DISPLAY SAMPLES ON LCD
    a = sampling1 / 1000;
    b = (sampling1 % 1000) / 100;
    c = (sampling1 % 100) / 10;
    d = sampling1 % 10;
    lcd(1, a + 48);
    lcd(1, b + 48);
    lcd(1, c + 48);
    lcd(1, d + 48);
 
    // DISPLAY VOLTAGE ON LCD
    percentage = sampling1 * 0.098;
    e = (percentage / 100) % 10;
    f = (percentage / 10) % 10;
    g = percentage % 10;
    lcd(1, 32); // ASCII FOR SPACE
    lcd(1, e + 48);
    lcd(1, f + 48);
    lcd(1, g + 48);
    lcd(1, 37); // ASCII FOR PERCENTAGE
    
    // DISPLAY POTENTIOMETER % ON LCD
    poten = (sampling1 * 0.00489) * 1000;
    x = poten / 1000;
    y = (poten % 1000) / 100;
    z = (poten % 100) / 10;
    lcd(1, 32); // ASCII FOR SPACE
    lcd(1, x + 48);
    lcd(1, 46); // ASCII FOR "."
    lcd(1, y + 48);
    lcd(1, z + 48);
    lcd(1, 86); // ASCII FOR 'V'
}

void ADC2() {
    GO = 1; // TELLS ADC TO START CONVERSION
    while (GO == 1); // WAIT TILL CONVERSION ENDS AND STORES DATA IN ADRESL AND ADRESH
    sampling2 = ADRESL | (ADRESH << 8); // 00 = 0*256 ; 01 = 1*256 ; 10 = 2*256 ; 11 = 3*256   (ADRESL = 255 + (00)= 255) (ADRESL = 255 + (10)= 511) 

    CCPR1L = sampling2 >> 2;
    CCP1CON |= ((sampling2 << 4)&0x30);
    
    // DISPLAY SAMPLES ON LCD
    a = sampling2 / 1000;
    b = (sampling2 % 1000) / 100;
    c = (sampling2 % 100) / 10;
    d = sampling2 % 10;
    lcd(1, a + 48);
    lcd(1, b + 48);
    lcd(1, c + 48);
    lcd(1, d + 48);
 
    // DISPLAY VOLTAGE ON LCD
    percentage = sampling2 * 0.098;
    e = (percentage / 100) % 10;
    f = (percentage / 10) % 10;
    g = percentage % 10;
    lcd(1, 32); // ASCII FOR SPACE
    lcd(1, e + 48);
    lcd(1, f + 48);
    lcd(1, g + 48);
    lcd(1, 37); // ASCII FOR PERCENTAGE
    
    // DISPLAY POTENTIOMETER % ON LCD
    poten = (sampling2 * 0.00489) * 1000;
    x = poten / 1000;
    y = (poten % 1000) / 100;
    z = (poten % 100) / 10;
    lcd(1, 32); // ASCII FOR SPACE
    lcd(1, x + 48);
    lcd(1, 46); // ASCII FOR "."
    lcd(1, y + 48);
    lcd(1, z + 48);
    lcd(1, 86); // ASCII FOR 'V'
}

void main() {
    PORTA = PORTC = PORTD = PORTE = TRISC = TRISD = TRISE = 0x00;
    TRISA = 0x03;
    ANSEL = 0x03;
    ANSELH = 0x00;
    lcd(0, 0x38);
    lcd(0, 0x0C);
    PR2 = 124;
    T2CON = 0x05;
    CCP1CON = 0x0C;

    while (1) {
        lcd(0, 0x80);
        ADCON0 = 0x81;
        ADCON1 = 0x80;
        sampling1 = ADRESL | (ADRESH << 8); // 00 = 0*256 ; 01 = 1*256 ; 10 = 2*256 ; 11 = 3*256   (ADRESL = 255 + (00)= 255) (ADRESL = 255 + (10)= 511) 
        ADC1();
        lcd(0, 0xC0); // NEXT LINE ON LCD
        
        ADCON0 = 0x85;
        ADCON1 = 0x80;
        sampling2 = ADRESL | (ADRESH << 8); // 00 = 0*256 ; 01 = 1*256 ; 10 = 2*256 ; 11 = 3*256   (ADRESL = 255 + (00)= 255) (ADRESL = 255 + (10)= 511) 
        ADC2();
    }
}
