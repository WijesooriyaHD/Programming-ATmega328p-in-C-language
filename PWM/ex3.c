#include<avr/io.h>
#include<util/delay.h>
#define d 10000

int main(void){
  
 
  DDRD=DDRD|(1<<6); //configure OCOA as an ouput pin
      
  OCR0A=191;// duty cycle =75% 
    
     //...............configure PWM settings..................//
  
  //set the timer mode to fast PWM mode
  TCCR0A=TCCR0A|((1<<WGM01)|(1<<WGM00));
  TCCR0B=TCCR0B & ~(1<<WGM02);
  
  //Set the timer mode to non-inverting mode
  
  TCCR0A=TCCR0A &~(1<<COM0A0);
  TCCR0A=TCCR0A |(1<<COM0A1);
  
  
  
  while(1){




 //Select the clock source with corresponding pre-scalar
    //pre-scalar 1:1024
    // frequency =61.035Hz

    TCCR0B=TCCR0B|(1<<CS02)|(1<<CS00);
    TCCR0B=TCCR0B &~(1<<CS01);
    _delay_ms(d);

    //Select the clock source with corresponding pre-scalar
    //pre-scalar 1:256
    // frequency =244.14Hz

    TCCR0B=TCCR0B &~(1<<CS00);
    TCCR0B=TCCR0B &~(1<<CS01);
    TCCR0B=TCCR0B|(1<<CS02);
    _delay_ms(d);


    //Select the clock source with corresponding pre-scalar
    //pre-scalar 1:64
    // frequency =976.56Hz
  
    TCCR0B=TCCR0B|(1<<CS01)|(1<<CS00);
    TCCR0B=TCCR0B &~(1<<CS02);
     _delay_ms(d);


    //Select the clock source with corresponding pre-scalar
    //pre-scalar 1:8
    // frequency =7812.5Hz

    TCCR0B=TCCR0B &~(1<<CS00);
    TCCR0B=TCCR0B|(1<<CS01);
    TCCR0B=TCCR0B &~(1<<CS02);
     _delay_ms(d);

   
    
 }

  return 0;
  
  
}
 
