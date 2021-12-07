#include<avr/io.h>
#include<avr/interrupt.h>

/*
	pre scaler=1:1024
    T counter_clock=1024/16 micro sec =64micro sec
    
    timer will overflow in every : 64*256 =16384 micro sec =16.384ms
    number of oveflows in 100ms time interval = 100000/16384 
    										  = 6.1035
                                              
    when t=100ms, counter variable = 7
    
    
*/


volatile uint8_t count; //declare a global variable
    
  

int main(void){
  
  count=0; //assign 0 to variable count
  
  DDRB=DDRB|(1<<5); // pin B5 in an output port
  
  TCNT0=0x00; //load timer counter register with 0
  
  TCCR0A=0x00; //set the timer0 under normal mode with 1:1024 prescaler 
  TCCR0B=0x05;
  
  TIMSK0=TIMSK0|(1<<TOIE0);//enable timer0 overflow interrupt
  sei(); //enable global interupt 
  
  while(1);
  
  return 0;
  
  
}

ISR(TIMER0_OVF_vect){ //interrupt service routine
 
  
  if(count==7){ //check whether the variable count is equal to 7 or not
    PORTB=PORTB^(1<<5); //toggle the led
    count=0;//assign 0 to count
    
  }else{ //if count!=7
    count++; // increment variable count by 1
  }
  
   TCNT0=0x00; //set initil value
  
}
  
  
  
  
  
  
  
 
