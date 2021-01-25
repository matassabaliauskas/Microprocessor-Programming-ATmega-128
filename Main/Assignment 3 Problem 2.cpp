/*******************************************************
This program was created by the CodeWizardAVR V3.32a 
Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Assignment 3
Version : Problem 2
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

unsigned char num[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
int count = 0;


// Timer 1 output compare A interrupt service routine

interrupt [TIM1_COMPA] void timer1_compa_isr(void){
    
    SREG.7 = 0; // Global interrupts disabled
        
    count++;    

    SREG.7 = 1; // Global interrupts enabled    
}

void main(void){
 
    char flag = 0; 
    
    DDRC = 0xFF;    // 7 segment output device powered on
    DDRG = 0x03;    // 7-Segment Device is Port G. It is set as output
    PORTC = 0xFF;   // 7 segment device is on
    
    TCCR1A = 0x00;  // Control Register A: Normal mode, CTC: 0000 0000
    TCCR1B = 0x0D;  // Control Register B: CTC mode, 1024 prescaler: 0000 1101
    
    TCNT1H = 0x10;  // Limit is TCNT1 = 0x1000 precscaler = 1/1024
    TCNT1L = 0x00;
    
    OCR1AH = 0x8A;  // OCR was calculcated to be 0x8A12 (= 0x7A12 + 0x1000)
    OCR1AL = 0x12;
    
    // timer goes from TCNT to OCR from 0x1000 to 0x8A12, which (at 1/1024 prescaler) is 2 seconds
    
    //Timer/counter interrupt mask register is 0011 0000 = 0x30. Timer1 input capture interrupt enabled, output compare match interrupt enabled  
    TIMSK = 0x30;
    
    SREG.7 = 1; // Global interrupts enabled
    
    while (1){               
    // Each time TCNT equals OCR, TIFR changes to 1, flag becomes 1, external interrupt is triggered. that increases the count. 
    
        flag = TIFR & 0x01;       
        
        PORTG = 0x02;               // 0000 0010. Selects Segment 1 of device (Tens)
        PORTC = num[count/10];      // Tens: only changes every 10th iteration
        delay_ms(1);                // 1ms delays needed so the system can show tens correctly
                            
        PORTG = 0x01;               // 0000 0001 Selects Segment 0 of device (Ones)
        PORTC = num[count%10];      // The output will always be between 0 and 9.
        delay_ms(1);
        
        if (flag == 1){           	// timer interrupt function is activated when TIFR == 1 
			TIFR = 0x00;	        // TIFR flag is reset
        }  
    }
}
