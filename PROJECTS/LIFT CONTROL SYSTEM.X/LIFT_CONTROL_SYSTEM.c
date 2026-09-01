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

void delay(unsigned int a);
void enable();
void lcd(char rs, char value);
void str(char *ptr);
void read_floor();
void read_destination();
void go_up();
void go_down();
void stop_motor();

int current_floor = 0;
int destination_floor = -1;
int last_shown_floor = -1;

void delay(unsigned int a)
{
    while(a--);
}

void enable()
{
    RE1 = 1;
    delay(100);
    RE1 = 0;
    delay(100);
}

void lcd(char rs, char value)
{
    RE0 = rs;

    PORTD = value & 0xF0;
    enable();

    PORTD = (value & 0x0F) << 4;
    enable();
}

void str(char *ptr)
{
    while(*ptr)
    {
        lcd(1,*ptr++);
    }
}

void go_up()
{
    RC0 = 1;
    RC1 = 0;
}

void go_down()
{
    RC0 = 0;
    RC1 = 1;
}

void stop_motor()
{
    RC0 = 0;
    RC1 = 0;
}

void read_floor()
{
    if(RA0){current_floor = 0;}
    else if(RA1){current_floor = 1;}
    else if(RA2){current_floor = 2;}
    else if(RA3) {current_floor = 3;}
}

void read_destination()
{
    if(RB0){destination_floor = 0;}
    else if(RB1){destination_floor = 1;}
    else if(RB2){destination_floor = 2;}
    else if(RB3){destination_floor = 3;}
}

void main()
{
    TRISA = TRISB = 0x0F;
    TRISC = TRISD = TRISE = 0x00;
    PORTA = PORTB = PORTC = PORTD = PORTE = 0x00;
    ANSEL = 0x00;
    ANSELH = 0x00;

    lcd(0,0x02);
    lcd(0,0x28);
    lcd(0,0x0C);
    lcd(0,0x06);
    lcd(0,0x01);
    delay(30000);

    lcd(0,0x80);
    str("Lift System");
    lcd(0,0xC0);
    str("Initializing");
    delay(60000);
    lcd(0,0x01);

 while(1)
{
    read_floor();

    if(current_floor != last_shown_floor)   // only redraw when it changes
    {
        lcd(0,0x01);
        delay(30000);
        lcd(0,0x80);
        str("Current Floor");
        lcd(0,0xC0);
        if(current_floor == 0){str("Ground");}
        else if(current_floor == 1){str("1st Floor");}
        else if(current_floor == 2){str("2nd Floor");}
        else if(current_floor == 3){str("3rd Floor");}

        last_shown_floor = current_floor;
    }

    read_destination();
    if(destination_floor != -1)
    {
        lcd(0,0x01);
        delay(30000);
        lcd(0,0x80);
        str("Destination");
        lcd(0,0xC0);
        if(destination_floor == 0){str("Ground");}
        else if(destination_floor == 1){str("1st Floor");}
        else if(destination_floor == 2){str("2nd Floor");}
        else if(destination_floor == 3){str("3rd Floor");}
        delay(60000);

            if(destination_floor > current_floor)
            {
                lcd(0,0x01);
                lcd(0,0x80);
                str("Going Up");
                go_up();

                while(current_floor != destination_floor)
                {
                    read_floor();
                }
                stop_motor();
                lcd(0,0x01);
                lcd(0,0x80);
                str("Reached");
                delay(60000);
            }
            else if(destination_floor < current_floor)
            {
                lcd(0,0x01);
                lcd(0,0x80);
                str("Going Down");
                go_down();

                while(current_floor != destination_floor)
                {
                    read_floor();
                }
                stop_motor();
                lcd(0,0x01);
                lcd(0,0x80);
                str("Reached");

                delay(60000);
            }
            else
            {
                lcd(0,0x01);
                lcd(0,0x80);
                str("Already Here");

                stop_motor();

                delay(60000);
            }

            destination_floor = -1;
        }
        }
    }
