#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define delay 500 // 150ms delay

int main (void){
  
  
	DDRD=DDRD &~(1<<2); //declare PD2 as an input port
      
    DDRB=DDRB |(1<<0); // declare 0th pin of port B as an ouput port
      
  //set EICRA (External Intrrupt Control Registar A) for falling edge detection
    EICRA=EICRA |(1<<ISC01);
    EICRA=EICRA &~(1<<ISC00);
      
    sei(); //enable global interrupt
  
  	EIMSK = EIMSK | (1<<INT0); //enable external interrupat for INT0
  
  	while(1){  //infinite loop
  
        
   	}
      
   return 0;    
      
      
}

ISR(INT0_vect){ //ISR -Interrupt service routine
  
  PORTB=PORTB^(1<<0); //toggaling PB0
  
  
}

