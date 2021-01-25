/*******************************************************
This program was created by the CodeWizardAVR V3.32a 
Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Assignnment 2
Version : Problem1
Date    : 26/05/2020
Author  : Matas Sabaliauskas
Student ID :2019952471 
Comments:


    /*
    Interrupt 0 is activated as falling edge happens - when SW1 button is released.
    It activates sequence #1 once. SW1_ready is used as a control variable which
    dictates whether the button was previously turned on. Input changes from 1 to 0
    Then the sequence is activated.
    
    Interrupt 1 is activated on a loop of rising edge. While SW2 button is pressed
    It actiavates sequence #2 for an infinite loop as long as button is on.
    */ 
    
    /*
    Note 2:
    Switch input (PIN E) activates Interrupt Trigger (PORT D) which then activates Interrupt Service Routine
    
    */


Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*******************************************************/

#include <mega128.h>
#include <delay.h>

// Global variables
int SW1_ready;


// External Interrupt 0 service routine
// External Interrup 0 runs once, going through all 8 LEDs as the routine is activated
interrupt [EXT_INT0] void ext_int0_isr(void)
{
int i;
SREG.7 = 0; // Disables global interrupts while interrupt 0 is running

for(i=0; i<8; i++)
{
    PORTA = 0x01 << i;          // shifts LED by 1 from right to left
    delay_ms(100);              // creates 100ms second delay
}
SREG.7 = 1;
}



// External Interrupt 1 service routine
// Interrupt 1 is an infinite loop activated, external interrupt is activated each time by SW2
interrupt [EXT_INT1] void ext_int1_isr(void)
{
int i;
SREG.7 = 0; // Disables global interrupts while interrupt 1 is running

/*
This Interrupt 0 function runs through all the LEDs once. But the function is
called continiously as long as the button SW2 is switched on.
*/

for(i=0; i<8; i++)
{
    PORTA = 0x80 >> i;          // shifts LED by 1 from right to left
    delay_ms(100);              // creates 100ms second delay
}
SREG.7 = 1; //The global interrupt is now enabled for the next operation
}



void main(void)
{
    unsigned char SW;
    DDRA = 0xFF;         // Port A = LEDs, set as output port
    PORTA = 0x00;        // All LEDs off
    
    DDRD = 0x03;         // Port D = Falling & Rising signal, set as output port
    
	DDRE = 0x00;         // Port E is set to be input port
    PINE = 0x30;         // Pin E has switches on bits 4 and 5
    
    EIMSK = 0x03;       // External Interrupt 0 and Interrupt 1 enabled
	EICRA = 0x0B;       // Interrupt 0 = rising edge. Interrupt 1 = falling edge.
    
    // Or EICRA = 0x0E: int 1 = rising, int 0 = falling.
    // Then 0b00001110 = 0x0E
    
    // PORTD.1 = 1; default of PORTD.1 is 1.
    // EIFR = 0x02; Clears interrupt flag



// #asm("sei")

    SREG.7 = 1; // Global Interrupt Enable
    while (1)
    {
          SW = PINE & 0x30;    // SW is a variable controlled by the 2 switches
          // SW can be 0000 0000 / 0010 0000 / 0001 0000 / 0011 0000
          
          // When the button is clicked:
          switch(SW)
          {
            case 0x10:          // in case SW1 (INT0) is turned on
                SW1_ready = 1;       // When the button is turned on, the sequence is ready to be started, when the input switches to 0.
                break;
            case 0x20:           // in case SW2 (INT1) is turned on
                PORTD.1 = 0;
                PORTD.1 = 1;     // Interrupt 1 rising edge loop activated
                delay_ms(100);    
            
                break;
            case 0x10 & 0x20:       // nothing should work when both SW1 and SW2 are turned on
                PORTA = 0x00;
                break;
          
            default:          // when there is no input
                if(SW1_ready == 1){     // if the button was turned on, and is now turned off, the external interrupt routine can be activated
                    PORTD.0 = 1;
                    PORTD.0 = 0;    // Interrupt 0 falling edge activated
                    SW1_ready = 0; // Since there is no input, reset ready-function
                    delay_ms(10);
                } 
                else
                PORTA = 0x00;
                break;
          }
    }
}


/*
Alternative code:

while(1){
	SW = PINE & 0x30; // to read PINE
	
	switch(SW){
		case 0x20:
			PORTD.0 = 1;	// after SW1 is clicked, create falling edge.
			PORTD.0 = 0;
		
		case 0x10:
			PORTD.1 = 0;	// after SW2 is pressed
			break;
		default:			// and then released
			PORTD.1 = 1;	// create rising edge
			PORTA = 0x00;
			break;
	}
	
}

*/
