#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define delay 100 // 150ms delay

unsigned char counter; //declare variable counter as a global variable

int main (void){
  
    counter=0; //assign 0 to counter
  
	DDRD=DDRD &~(1<<2); //declare PD2 as an input port
    DDRD=DDRD &~(1<<3); //declare PD3 as an inpur port
      
    DDRB=DDRB |((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)); // declare all the pins of port B as ouputs
      
  //set EICRA for rising edge detection (at INT0 pin /PD2)
    EICRA=EICRA |(1<<ISC01);
    EICRA=EICRA |(1<<ISC00);
  
  //set ECICRA for rising edge detection (at INT1 pin /PD3)
    EICRA=EICRA |(1<<ISC10);
    EICRA=EICRA |(1<<ISC11);
  
  
    sei(); //enable global interrupt
  
  	EIMSK = EIMSK | (1<<INT0); //enable external interrupts for INT0
    EIMSK = EIMSK | (1<<INT1); //enable external interrupts for INT1
    
  
  	while(1){  //infinite loop
  
        
   	}
      
   return 0;    
      
      
}

ISR(INT0_vect){  // ISR for push button B (PD2) ,'1'
  
  if(counter==6){ //check whether the counter is equal to 6 or not
    
    counter=0; //if counter is ==6 then assign 0 to counter
    PORTB=0x00;
     _delay_ms(delay); //add delay
  }
 
  PORTB=PORTB<<1; //shift the pattern to left
  PORTB=PORTB | (1<<0);  //assign 1 to LSB
 
  counter++; //increment counter by 1
  
  
  
}

ISR(INT1_vect){  // ISR for push button A (PD3),'0'
  
   if(counter==6){ //check whether the counter is equal to 6 or not
    
    counter=0; //if counter is == 6 then assign 0 to counter
    PORTB=0x00; //turn off all the LEDs
    _delay_ms(delay); // add delay
  }
  
  PORTB=PORTB<<1; //shift the pattern to left
  PORTB=PORTB &~(1<<0); //assign 0 to LSB
  
  counter++; //increment counter by 1
  
  
  
}

