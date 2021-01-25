/*******************************************************
This program was created by the CodeWizardAVR V3.32a 
Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Assignment 3
Version : Problem 1
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


void main(void)
{
    char flag = 0;
    int count = 0;
    int itr = 0;
    
    DDRA = 0xFF; // Port A = LEDs, set as output port
    PORTA = 0x00;
    TCCR0 = 0x07; // binary 0000 0111, normal mode, precscaler = 1/1024
    TCNT0 = 0x63; // initial TCNT0 value is 255 - 157 = 99 = 0x63



    while (1){
        
        flag = TIFR & 0x01;                // Read timer/counter overflow flag
        
        if(flag == 1){                    //each loop is 157 * 64 us = 10 ms
            TIFR = 0x01;                // clear T0V0 (clear timer overflow flag)
            count++;
            TCNT0 = 0x63;                
        }
        if(count == 200){                 // 200 loops of 10 ms equals 2s for each LED
            PORTA = 0x01 << itr;
            itr++;
            count = 0;
        }
        if(itr == 8){                    // itr goes through all 8 LEDs
            itr = 0;
        }
    }
}