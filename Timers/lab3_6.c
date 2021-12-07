#include<avr/io.h>
#include<avr/interrupt.h>

/*

	Calculations for 50ms ,using TIMER0

	pre scaler=1:1024
    T counter_clock=1024/16 micro sec =64micro sec
    
    overflow occurs at every : 64*256 =16384 micro sec =16.384ms
    number of oveflows in 100ms time interval = 50 000/16384 
    										  = 3.051
                                              
    when t=50ms, counter variable = 4
    
    
*/



/*

	Calculations for 500ms ,using TIMER1

	pre scaler=1:8
    T counter_clock=8/16 micro sec =0.5micro sec
    
    overflow occurs at every : 0.5*(2^16) =32768 micro sec =32.768ms
    number of oveflows in 100ms time interval = 500 000/32768
    										  = 15.258
                                              
    when t=500ms, counter variable = 16
    
    
*/


volatile uint8_t count1; //declare a global variable
volatile uint8_t count2; //declare a global variable   
  

int main(void){
  
  //assign 0 to variables
  count1=0;
  count2=0;
  
  DDRB=DDRB|(1<<5); // pin B5 is an output port 
  DDRB=DDRB|(1<<4);  // pin B4 is an ouput port 
  
  TCNT0=0x00; //load timer counter register in timer0 with 0
  TCNT1=0x00; //load timer counter register in timer1 with 0
  
  TCCR0A=0x00; //set the timer0 under normal mode with 1:1024 prescaler 
  TCCR0B=0x05;
  
  TCCR1A=0x00; //set the timer1 under normal mode with 1:8 prescaler 
  TCCR1B=0x02;
  
  TIMSK0=TIMSK0|(1<<TOIE0);//enable timer0 overflow interrupt
  TIMSK1=TIMSK1|(1<<TOIE1);//enable timer1 overflow interrupt
  
  sei(); //enable global interupt 
  
  while(1); 
  
  return 0;
  
  
}

ISR(TIMER0_OVF_vect){ //interrupt service routine for TIMERO
  
  if(count1==4){ //check whether the variable count is equal to 7 or not
    PORTB=PORTB^(1<<5); //toggle the led at pin B5
    count1=0;//assign 0 to count
    
  }else{ //if count!=7
    count1++; // increment variable count by 1
  }
  
  TCNT0=0x00;  //set initial value
}
  
  
ISR(TIMER1_OVF_vect){ //interrupt service routine for TIMER1
  
  if(count2==16){ //check whether the variable count is equal to 16 or not
    PORTB=PORTB^(1<<4); //toggle the led at pin B4
    count2=0;//assign 0 to count
    
  }else{ //if count!=16
    count2++; // increment variable count by 1
  }
  
  TCNT1=0x00; //set initial value
}
  
  
  
  
  
  
 
