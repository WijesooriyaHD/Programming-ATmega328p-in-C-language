#include<avr/io.h>

/*

Fwave=Fosc/(256*N)

976.56=16*10^6/(256*N)

N=64 (pre scalar)


DC=(OCRO+1)*100/(256)

50=(OCRO+1)*100/256

OCRO=127



*/



int main(void){
  
 
  DDRD=DDRD|(1<<6); //configure OCOA as an ouput pin
  
  
  OCR0A=127;  //counts required for the given duty cycle
  
  
  
  //...............configure PWM settings..................//
  
  //set the timer mode to fast PWM mode
  TCCR0A=TCCR0A|((1<<WGM00)|(1<<WGM01));
  TCCR0B=TCCR0B & ~(1<<WGM02);
  
  //Set the timer mode to non-inverting mode
  
  TCCR0A=TCCR0A &~(1<<COM0A0);
  TCCR0A=TCCR0A |(1<<COM0A1);
  
  //Select the clock source with corresponding pre-scalar
  //pre-scalar=1:64
  TCCR0B=TCCR0B|(1<<CS00)|(1<<CS01);
  TCCR0B=TCCR0B &~(1<<CS02);
  
  
  
  
 
  while(1){
    
 
    

  }
  return 0;
  
  
}
 
