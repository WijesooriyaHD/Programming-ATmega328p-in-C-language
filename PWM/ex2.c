#include<avr/io.h>
#include<util/delay.h>

#define wait 50

/*
Fwave=Fosc/(256*N)

976.56=16*10^6/(256*N)

N=64 (pre scalar)

*/



int main(void){
  
 
  DDRD=DDRD|(1<<6); //configure OCOA as an ouput pin
  
  //...............configure PWM settings..................//
  
  //set the timer mode to fast PWM mode
  TCCR0A=TCCR0A|((1<<WGM00)|(1<<WGM01));
  TCCR0B=TCCR0B & ~(1<<WGM02);
  
  //Set the timer mode to non-inverting mode
  
  TCCR0A=TCCR0A &~(1<<COM0A0);
  TCCR0A=TCCR0A |(1<<COM0A1);
  
  //Select the clock source with corresponding pre-scalar
  //pre-scalar = 1:64
  TCCR0B=TCCR0B|(1<<CS00)|(1<<CS01);
  TCCR0B=TCCR0B &~(1<<CS02);
  
  
  
  
 
  while(1){

    //fading the led from off->on
    for(int count=0;count<=255;count++){

      OCR0A=count;
      _delay_ms(wait);

    }

     //fading the led from on-->off
    for(int count=255;count>=0;count--){

      OCR0A=count;
      _delay_ms(wait);

    }
    
 }
  return 0;
  
  
}
 
