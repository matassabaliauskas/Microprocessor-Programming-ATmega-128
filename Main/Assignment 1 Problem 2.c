/*******************************************************
This program was created by the CodeWizardAVR V3.32a 
Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Assignment 1
Version : Problem2
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
    unsigned char SW;
    DDRA = 0xFF;         // Port A is set to be output port
    PORTA = 0x00;        // 0000 0000 turned off LEDs
    DDRE = 0x00;         // Port E is set to be input port
    PINE = 0x30;         // Pin E has switches on bits 4 and 5
    
    while(1)
    {
        SW = PINE & 0x30;    // SW is a variable controlled by the 2 switches
        
        switch(SW)
        {
            case 0x20:              // in case SW2 is controlled
                PORTA = 0x0F;
                break;
            case 0x10:              // in case SW1 is controlled
                PORTA = 0xF0;
                break;
            case 0x10 & 0x20:       // both SW1 and SW2 on
                PORTA = 0xFF;
                break;
            default:                // default case : all off
                PORTA = 0x00;
                break;
        }
    }
}