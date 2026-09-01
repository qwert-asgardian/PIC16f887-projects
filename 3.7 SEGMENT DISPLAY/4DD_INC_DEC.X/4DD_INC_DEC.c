
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
    
    void main(){
        TRISC = 0x00; 
        PORTC = 0x00;
        ANSEL = 0x00;
        TRISD = 0x00;
        PORTD = 0x00;
        ANSELH = 0x00;
        unsigned char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
        unsigned char i = 0, k = 0;
        
        while(1){
            for(i=0;i<100;i++){
                unsigned char j = 99 - i;
                for(k=0;k<10;k++){
                    RD0 = 1; 
                    RD1=RD2=RD3=0;
                    PORTC = arr[i/10];
                    delay(1000);
                    PORTC = 0;
                    
                    RD1 = 1;
                    RD0=RD2=RD3=0;
                    PORTC = arr[i%10];
                    delay(1000);
                    PORTC = 0;
                    
                    RD2 = 1;
                    RD0=RD1=RD3=0;
                    PORTC = arr[j/10];
                    delay(1000);
                    PORTC = 0;
                    
                    RD3= 1;
                    RD0=RD1=RD2=0;
                    PORTC = arr[j%10];
                    delay(1000);
                    PORTC = 0;           
                }
            }
        }
    }
 
        
        
    