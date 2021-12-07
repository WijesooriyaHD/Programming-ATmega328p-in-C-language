#include<avr/io.h>

int main(void){
  
  DDRC=DDRC & ~(1<<1); //declare the input pin (ADC1)
  DDRD=DDRD | (1<<4); //pind4 -output
  
  ADCSRA=ADCSRA | (1<<ADEN); //turn on the ADC module

  ADCSRA=ADCSRA | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) ; //conversion speed , pre-scaler=128 , frequency=125kHz

  //select voltage reference -ARef
  ADMUX = ADMUX | (1<<REFS0);
  ADMUX = ADMUX & ~(1<<REFS1);

  //select ADC input channels for ADC1 , 0001
  ADMUX = ADMUX  | (1<<MUX0);
  ADMUX = ADMUX  & ~(1<<MUX1);
  ADMUX = ADMUX  & ~(1<<MUX2);
  ADMUX = ADMUX  & ~(1<<MUX3);
  
  //adjusting result with left justify
  ADMUX = ADMUX  | (1<<ADLAR);	
  
  while(1){
    
    ADCSRA |= (1 << ADSC); // Activate the start conversion bit 
    
    //wait for the conversion
    while (!(ADCSRA & (1 << ADIF)));
    
    if(ADCH < 100){		//turn on led, if ir is dark
    	PORTD |= (1 << 4);
    }
    else if(ADCH >= 100){	//turn off led
    	PORTD &= ~(1 << 4);
    }
    
    // clear ADIF bit
    ADCSRA |= (1 << ADIF);
             
  }
}