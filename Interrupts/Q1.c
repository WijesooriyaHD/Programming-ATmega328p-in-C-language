#include <avr/io.h>
#include <util/delay.h>

#define delay 500 // 150ms delay

int main (void){
  
  
	DDRD=DDRD &~(1<<7); //declare PD7 as a input port
      
    DDRB=DDRB | ((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)); // declare 6 pins of port B as ouputs
      
    char counter=0; // variable declaration
  
  	while(1){  //infinite loop
  
  		if(PIND & (1<<7)){ //check whether PD7 is high or not (push button is pressed or not)
      
      		counter++; //increment counter by 1
      
      		if(counter>63){ //check the number of time, the push button is pressed
        
        		counter=1; //assign 1 to variable counter , when counter variable is grater than 63
        
      		}
      
      
     	 PORTB=0x0;  //turn off all the LEDs
      	_delay_ms(delay); //add delay
        
      
      
      	 PORTB=counter; // display a 6 bit binary number
         _delay_ms(delay); //add delay
          
        }
        
   	}
      
   return 0;    
      
      
}

