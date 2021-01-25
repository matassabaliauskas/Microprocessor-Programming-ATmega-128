/*******************************************************
This program was created by the CodeWizardAVR V3.32a 
Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Assignment 3
Version : Problem 3
Date    : 07/06/2020
Author  : Matas Sabaliauskas
Student ID: 2019952471
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

void main(void){
    
    char flag = 0;
    
    DDRA = 0xFF; 	// Port A = LEDs, set as output port
    PORTA = 0xFF;
    
    DDRB = 0xFF;	// Port B is set as output	
	PORTB = 0x80;	//PB7 = OC1C. So port B = 1000 0000 = 0x80
    
    
    TCCR1A = 0x83;  // TCCR1A = 0x0B Phase Correct PWM
    TCCR1B = 0x05;  // 1/1024 prescaler: 0000 0101
    
 
    OCR1CH = 0x0A;	// OCR = 0.60 * 0x03FF = 0x017A
    OCR1CL = 0x7A;
    
    /* 
	Actually: 
    OCR1CH = 0x02;
    OCR1CL = 0x66;
    
    OCR1C / TCNT1_top = 0.6
    TCNT1_top = 0x3FF
    
    0x3FF = 1023
    1023 * 0.6 = 613.8 = 614 = 0x0266
    */
    
    
    TCNT1H = 0x00;  //TCNT goes from 0x0000 to 0x03FF
    TCNT1L = 0x00;
   
//The program switches between the two loops, as flag is turned on half of the time    
    while (1){     
         flag = PINB & 0x80;    // PINB = OC, which changes between 0x00 and 0x80
         if(flag == 0x80){      // program enters this loop correctly
            PORTA = ~PORTA;     // inverts all LEDs when TCNT == OCR
            delay_ms(10);
            PINB = 0x01;        // resets the OC indicator
         }
         if(flag != 1){         // program enters this loop correctly
            PINB = 0x01;        // do nothing and reset the OC indicator    
         }
        TCNT1H = 0x00;          // reset TCNT after each run
        TCNT1L = 0x00;
    }
}

/*
	while(1){
		flag = PINB & 0x80;
		if(flag != 0x80){		// Turn off all LEDs when OC1C is clear
			PORTA = 0x00;
		}
		if(flag == 0x80){		// Turn on all LEDs when OC1C is set
			PORTA = 0xFF
		}
	}
*/
