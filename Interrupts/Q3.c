#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define delay 100 // 150ms delay

int main (void){
  
  
	DDRD=DDRD &~(1<<2); //declare PD2 as an input port
      
    DDRB=DDRB |((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)); // declare all the pins of port B as ouputs
      
  //set external interrupt control register A for falling edge detection
    EICRA=EICRA |(1<<ISC01);
    EICRA=EICRA &~(1<<ISC00);
      
    sei(); //enable global interrupt
  
  	EIMSK = EIMSK | (1<<INT0); //enable external interrupts for INT0
  
    
  
  	while(1){  //infinite loop
  
        
   	}
      
   return 0;    
      
      
}

ISR(INT0_vect){  // ISR
  
  unsigned char counter; //variable decleration
  
  counter++; //increment counter by 1
  
  if(counter>63){ //check whether the counter is grater than 63 or not
    
    counter=1; //if counter is > 63 then assign 1 to counter
  }
  
  
  
  PORTB=0x00; //turn off all the LEDs
  _delay_ms(delay); //add delay
  
  PORTB=counter; //display the bit pattern
  _delay_ms(delay); // add delay
  
  
  
}

