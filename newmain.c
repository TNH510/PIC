// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)
// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)
#include <xc.h>
#define _XTAL_FREQ 500000
#include <xc.h>


int A[80] = {
    0,0,0,0,0,0,1,1,  1,0,0,1,1,1,1,1,  0,0,1,0,0,1,0,1,
    0,0,0,0,1,1,0,1,  1,0,0,1,1,0,0,1,  0,1,0,0,1,0,0,1,
    0,1,0,0,0,0,0,1,  0,0,0,1,1,1,1,1,  0,0,0,0,0,0,0,1,  
    0,0,0,0,1,0,0,1,                                        };   
void data(unsigned int a){
    signed int i;
    for(i=8*a+7;i>=8*a;i--)
        {   
            LATCbits.LATC1 = A[i];
            LATCbits.LATC0 = 1;
            LATCbits.LATC0 = 0;
        }       }
void hienthi(unsigned int a,unsigned int b,unsigned int c){
         data(c); data(b); data(a);
        LATCbits.LATC2 = 1;
        LATCbits.LATC2 = 0;    }



void main(void) {
    
    TRISCbits.TRISC0 = 0; //CLOCK
    TRISCbits.TRISC1 = 0; //DATA
    TRISCbits.TRISC2 = 0; //LATCH
    TRISCbits.TRISC3 = 0; //Motor
    TRISBbits.TRISB4 = 1; //CBT
    TRISBbits.TRISB5 = 1; //Reset
    TRISBbits.TRISB7 = 1; //S
    LATCbits.LATC0 = 0; 
    LATCbits.LATC1 = 0;
    LATCbits.LATC2 = 0;
    LATCbits.LATC3 = 0;
        
    unsigned int a; unsigned int b; unsigned int c; unsigned int s; 
    unsigned int state; 
    a = 0;b = 0; c = 0;
    while(1)
    {   
        s=3;

        if (PORTBbits.RB7 == 1){s=1;}
        if (PORTBbits.RB7 == 0){s=0;}
        if (s == 1)
        {    
            
            if (PORTBbits.RB4 == 1)
            {__delay_ms(100);c=c+1;}
            LATCbits.LATC3 = 1;               
            hienthi(a,b,c);
            __delay_ms(100);
       
        }
        if (s == 0)
        {               
            
            LATCbits.LATC3 = 1;               
            hienthi(0,0,0);
            __delay_ms(100);
                
        }
        while(PORTBbits.RB5 == 1)
        {LATCbits.LATC3 = 0; }
       

    }
    return;
}
