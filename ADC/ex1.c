#include<avr/io.h>

int main(void){

    DDRC=DDRC & ~(1<<1); //dclare the input pin (ADC1)
    DDRD=DDRD | ((1<<0) | (1<<1) | (1<<2) |(1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7)); //port d -output

    ADCSRA=ADCSRA | (1<<ADEN); //turn on the ADC module

    ADCSRA=ADCSRA | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) ; //conversion speed , pre-scaler=128 , frequency=125kHz

    //select voltage reference -AVCC
    ADMUX = ADMUX | (1<<REFS0);
    ADMUX = ADMUX & ~ (1<<REFS1);

    //select ADC input channels for ADC1 , 0001
    ADMUX = ADMUX  | (1<<MUX0);
    ADMUX = ADMUX  & ~(1<<MUX1);
    ADMUX = ADMUX  & ~(1<<MUX2);
    ADMUX = ADMUX  & ~(1<<MUX3);

    //adjusting the result
    ADMUX = ADMUX & ~(1<<ADLAR); //right justified

    //activate the start conversion
    ADCSRA=ADCSRA | (1<<ADSC);

    while(1){
    
        //check whether the ADIF bit is high or 
        //wait for the conversion to complete
        if(ADCSRA & (1<<ADIF)){

            PORTD = ADCL;  //get the output of the ADC reg
        }
    }

    return 0;  
}
 
