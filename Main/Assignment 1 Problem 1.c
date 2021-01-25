/*******************************************************
This program was created by the CodeWizardAVR V3.32a 
Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Assignment 1
Version : Problem1
Date    : 3/05/2020
Author  : Matas Sabaliauskas
Student ID :2019952471 
Comments: 


Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*******************************************************/

#include <mega128.h>
#include <delay.h>

// Declare your global variables here

void main(void)
{
    int i = 0;
    DDRA = 0xFF;         // Port A is set to be output port
    
    // The entire program is on an infinite loop.
    
    while(1){
        PORTA = 0x00;        // Initally all LEDs turned off 0000 0000

        for(i=0; i<7; i++)
        {
            PORTA = 0x01 << i;          // shifts LED by 1: 0000 0001
            delay_ms(200);              // creates 200ms second delay
        }
        
        for(i=0; i<7; i++)
        {
            PORTA = 0x80 >> i;          // shifts LED by 1 from: 1000 0000
            delay_ms(200);              // creates 200ms second delay
        } 
    }
	
	/*
	Note: 
	may also use direction variable. e.g. int direction = 1 means PORTA <<= 1;
	and int direction = 2 means PORTA >>= 1;
	PORTA changes from 0x01 to 0x80 
	*/    
}
