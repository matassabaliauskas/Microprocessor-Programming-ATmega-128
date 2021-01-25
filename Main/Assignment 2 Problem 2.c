/*******************************************************
This program was created by the CodeWizardAVR V3.32a 
Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Assignment 2 
Version : Problem2
Date    : 26/05/2020
Author  : Matas Sabaliauskas
Student ID : 2019952471 
Comments: 

The Student ID is 2019952471
The last 3 digits are 471
On 7-segment device:
4 = 0x66
7 = 0x07
1 = 0x06

Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*******************************************************/

#include <mega128.h>
#include <delay.h>

unsigned char num[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

// Declare your global variables here

void main(void)
{
    DDRC = 0xFF; // Port C: every bit is set as output.
    DDRG = 0x07; // 0000 0111. 7-Segment Device is Port G. It is set as output.

    while (1)
    {
        PORTG = 0x04;       // 0000 0100. Selects segment 2 of device (Hundreds)
        PORTC = num[4];     // Number 4 will be displayed. Could also write PORTC = 0x066;
        delay_ms(1);        // 1ms delay is required to avoid the glitch.
        
        PORTG = 0x02;       // 0000 0010. Selects segment 1 of device (Tens)
        PORTC = num[7];     // Number 7 will be displayed. Could also write PORTC = 0x07;
        delay_ms(1);
        
    // Alternative way to write a code: 
                    
        PORTG = 0x01;       // 0000 0001 Selects segment 0 of device (Ones)
        PORTC = 0x06;       // Number 1 will be displayed
        delay_ms(1);    
    }
}


/*
Note: Alternative code can display one digit at a time


unsigned char num[3] = {0x66, 0x07, 0x06}
while(1){

	int i=0;
	for(i=0;i<3;i++){
		PORTG = 0x01 << i;	// 3 numbers will be displayed one at a time
		PORTC = num[2-i];	// the array must only include the 3 numbers of the student ID
		delay_ms(2);		
	}
}

*/
