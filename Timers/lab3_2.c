#include<avr/io.h>

/*
	pre scaler=1:256
    T counter_clock=256/16 micro sec =16micro sec
    Counter increments neede=2000 micro sec/16 micro sec =125
    initial counter value =1+255-125=131
    
*/
    
    

void delay_timer0(){
  

  for(int i=0;i<250;i++){
 	 TCNT0=131; //load timer counter register
  
 	 TCCR0A=0x00; //set the timer0 under normal mode with 1:256 prescaler 
  	 TCCR0B=0x04;
  
  	 while((TIFR0&0x01)==0); //wait till timer overflow bit (T0V0) is set
  
 	 TCCR0A=0x00;  //clear the timer settings
  	 TCCR0B=0x00;
  
  	 TIFR0=0x01;  //clear the timer overflow bit for the next round
    
  }
 
  
}


int main(void){
  
 int count=0;
  
 DDRB=DDRB|(1<<5); //declare pin 5 as an output port
  
  while(1){
    
 
    PORTB=PORTB^(1<<5); //toggle the bit in pin5
    
    delay_timer0(); //invoke delay_timer0 function
    
  
      

  }
  return 0;
  
  
}
 

/* question 2

    pre scaler=1:1024
    T counter_clock=1024/16 micro sec =64 micro sec
    Counter increments neede=500 000 micro sec/64micro sec =7812.5
    
    7812.5>>256 
    can't add a 500ms delay
    
*/


/*
 
 	problem 3
   
	pre scaler=1:1024
    T counter_clock=1024/16 micro sec =64 micro sec
    initial counter value =1+255-256=0 (to get the heighest possible time)
    
   	 needed  256 counter increments
    
    highest possible countable time=256*64=16384 micro sec =16.384ms
    
    
    
*/

