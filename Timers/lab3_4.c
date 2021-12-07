#include<avr/io.h>
#include<avr/interrupt.h>
#include <util/delay.h>

#define delay 150 // 150ms delay




/*

	Calculations for 1s ,using TIMER1

	pre scaler=1:64
    T counter_clock=64/16 micro sec =4micro sec
    
    overflow occurs at every : 4*(2^16) =262144 micro sec =262.144ms
    number of oveflows in 100ms time interval = (10^6)/262144
    										  = 3.8146 
                                              
    when t=1s, counter variable = 4
    
    
*/


volatile uint8_t count1; //declare a global variable   
  

int main(void){
  
  unsigned char counter1 ;   // varibale declaration , it is used as a counter variable for loops
  
  // decalare 4 pins of port B as output port
  DDRB=DDRB | ((1<<0)|(1<<1)|(1<<2)|(1<<3));
  
  
  
  
  //assign 0 to variables
  count1=0;
  
  
  DDRB=DDRB|(1<<5); // pin B5 is an output port 
  
 
  TCNT1=0x00; //load timer counter register in timer1 with 0
  
 
  
  TCCR1A=0x00; //set the timer1 under normal mode with 1:64 prescaler 
  TCCR1B=0x03;
  
  TIMSK1=TIMSK1|(1<<TOIE1);//enable timer1 overflow interrupt
  
  sei(); //enable global interupt 
  
  while(1){
    
     //move to right 
    
    for(counter1=4;counter1>=1;counter1--){
      
      
       //turn off all the LED
    
    	PORTB=PORTB & ~((1<<0)|(1<<1)|(1<<2)|(1<<3));   
        _delay_ms(delay) ; //add delay (off)
      
     
       PORTB=PORTB|(1<<counter1-1);  // turn on the corresponding LED 
       _delay_ms(delay) ; //add delay (on)
      
      
      
     }
   
 
     //move to left
    
    for(counter1=1;counter1<3;counter1++){

      //turn off all the LEDs
    
    	PORTB=PORTB & ~((1<<0)|(1<<1)|(1<<2)|(1<<3)); 
        _delay_ms(delay) ; //add delay (off)
      
      
      PORTB=PORTB|(1<<counter1);  // turn on the corresponding LED
      _delay_ms(delay) ; //add delay (on)
      
      
    }
    
    
  }
  
  return 0;
  
  
}

  
ISR(TIMER1_OVF_vect){ //interrupt service routine for TIMER1
  
  if(count1==4){ //check whether the variable count is equal to 16 or not
    PORTB=PORTB^(1<<5); //toggle the led at pin B4
    count1=0;//assign 0 to count
    
  }else{ //if count!=16
    count1++; // increment variable count by 1
  }
}
  
  
  
  
  
  
 
