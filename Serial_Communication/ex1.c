#include <avr/io.h>
# include<util/delay.h>

// Clock Speed
# define FOSC 16000000 
# define BAUD 9600

// MYUBRR = (FOSC/(16*BAUD))-1 =103
# define MYUBRR  103



void usart_init( unsigned int ubrr){
  
 /*Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);


//set the frame size : 8 bits
UCSR0C = UCSR0C | ((1<<UCSZ00) | (1<<UCSZ01));
UCSR0B = UCSR0B & ~(1<<UCSZ02);


//set the parity bits - no parity
// disable parity modes
UCSR0C = UCSR0C & ~(1<<UPM00);
UCSR0C = UCSR0C & ~(1<<UPM01);


// one stop bit
UCSR0C = UCSR0C & ~(1<<USBS0);

 //asynchronus mode
UCSR0C = UCSR0C & ~(1<<UMSEL00);
UCSR0C = UCSR0C & ~(1<<UMSEL01);
  
/*Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;




}

void usart_send( unsigned  char data ){

/* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );

/* Put data into buffer, sends the data */
    UDR0 = data;

}



unsigned char usart_receive( void ){

/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );

/* Get and return received data from buffer */
	return UDR0;

}

