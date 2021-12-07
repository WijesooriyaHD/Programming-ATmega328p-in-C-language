#include <avr/io.h>
#include <util/delay.h>

#define delay 150 // 150ms delay



int main (void){
  
  unsigned char counter1 ;   // varibale declaration , it is used as a counter variable for loops
  
 
  // decalare 4 pins of port B as output port
  DDRB=DDRB | ((1<<0)|(1<<1)|(1<<2)|(1<<3));
  
  
  while(1){ // infinite loop
    
    
    // pin3 = led A / pin2= led B / pin1 =led C / pin0= led D
    
    
    
    //move to right 
    
    for(counter1=4;counter1>=1;counter1--){
      
      
       //turn off all the LED
    
    	PORTB=PORTB & ~((1<<0)|(1<<1)|(1<<2)|(1<<3));   
        _delay_ms(delay) ; //add delay (off)
      
     
       PORTB=PORTB|(1<<counter1-1);  // turn on the corresponding LED 
       _delay_ms(delay) ; //add delay (on)
      
      
      
     }
   
 
     //move to left
    
    for(counter1=0;counter1<=3;counter1++){

      //turn off all the LEDs
    
    	PORTB=PORTB & ~((1<<0)|(1<<1)|(1<<2)|(1<<3)); 
        _delay_ms(delay) ; //add delay (off)
      
      
      PORTB=PORTB|(1<<counter1);  // turn on the corresponding LED
      _delay_ms(delay) ; //add delay (on)
      
      
    }
    
    
  }
  
    return 0;
}



