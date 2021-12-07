
#include "ex1.c"

#include<string.h>
#include<ctype.h>


int main (void){
   
  usart_init(MYUBRR); // initialize the USART

  unsigned char text; // decalre variable text
  
  while(1){
      
     text = usart_receive();  // receive a character

    if(isalpha(text)!=0){  // checking for an alphabetic chracter

      if(text >= 'A' && text <='Z'){ // checking for an uppercase caharacter

        text=(text+3-65)%26 + 65;  // perform cieaser cipher with key=3

      }else{

        // handling lowercase characters
        text=(text+3-97)%26 + 97; // perform cieaser cipher with key=3
      } 
            
    }
            
    // sed data 
    usart_send(text);
  

  }
  
  return 0;
}