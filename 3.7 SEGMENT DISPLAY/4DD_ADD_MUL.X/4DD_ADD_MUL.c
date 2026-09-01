
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
        TRISA = 0x0F;
        PORTA = 0x00;
        ANSELH = 0x00;
        unsigned char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
        unsigned char i = 0, j = 0, k = 0, x = 0;
        unsigned char count1=0;
        unsigned char count2=0;
        unsigned char add;
        unsigned int mul;
        
        while(1){
            if(RA0 == 1){
                count1++;
                while(RA0 == 1);
            }
            
                for(j=0;j<10;j++){
                    RD0 = 1; 
                    RD1=RD2=RD3=0;
                    PORTC = arr[count1 /10];
                    delay(10);
                    PORTC = 0;
                    
                    RD1 = 1;
                    RD0=RD2=RD3=0;
                    PORTC = arr[count1 %10];
                    delay(10);
                    PORTC = 0;
                }
            if(RA1 == 1){
                count2++;
                while(RA1 == 1);
            }
            
                for(k=0;k<10;k++){
                    RD2 = 1; 
                    RD1=RD0=RD3=0;
                    PORTC = arr[count2 /10];
                    delay(10);
                    PORTC = 0;
                    
                    RD3 = 1;
                    RD0=RD2=RD1=0;
                    PORTC = arr[count2 %10];
                    delay(10);
                    PORTC = 0;
                }
            
            if(RA2 == 1){
                add = count1 + count2;
                for(i=0;i<10;i++){
                    RD3 = 1;
                    RD0=RD2=RD1=0;
                    PORTC = arr[add%10];
                    delay(10);
                    PORTC = 0;
                    RD2 = 1; 
                    RD1=RD0=RD3=0;
                    PORTC = arr[(add /10)% 10];
                    delay(10);
                    PORTC = 0;
                    RD1 = 1;
                    RD0=RD2=RD3=0;
                    PORTC = arr[(add/100) % 10];
                    delay(10);
                    PORTC = 0;
                    RD0 = 1;
                    RD1=RD2=RD3=0;
                    PORTC = arr[(add/1000) % 10];
                    delay(10);
                    PORTC = 0;
                }
            }
            if(RA3 == 1){
                mul = count1 * count2;
                for(x=0;x<10;x++){
                    RD3 = 1;
                    RD0=RD2=RD1=0;
                    PORTC = arr[mul%10];
                    delay(10);
                    PORTC = 0;
                    RD2 = 1; 
                    RD1=RD0=RD3=0;
                    PORTC = arr[(mul /10)% 10];
                    delay(10);
                    PORTC = 0;
                    RD1 = 1;
                    RD0=RD2=RD3=0;
                    PORTC = arr[(mul/100) % 10];
                    delay(10);
                    PORTC = 0;
                    RD0 = 1;
                    RD1=RD2=RD3=0;
                    PORTC = arr[(mul/1000) % 10];
                    delay(10);
                    PORTC = 0;
                    
                }
            }
            }
    }
    
        
        