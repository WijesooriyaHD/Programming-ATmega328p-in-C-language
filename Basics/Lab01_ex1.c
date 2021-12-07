#include <avr/io.h>
#include <util/delay.h>

#define blink_delay 1500  // 1500ms delay

int main (void){
  

    
    DDRB=DDRB | ((1<<0)|(1<<1)|(1<<2)|(1<<3));  // decalare 4 pins of port b as output
   
  
  
  while(1){ // infinite loop
    
 	
    	PORTB=PORTB | ((1<<0)|(1<<1)|(1<<2)|(1<<3));  //  Turn on LEDs
        _delay_ms(blink_delay); //add delay
    
    
    	PORTB=PORTB&~((1<<0)|(1<<1)|(1<<2)|(1<<3));  // Turn off LEDs
    	_delay_ms(blink_delay); //add delay
    
    
   }
  
  
    return 0;
}