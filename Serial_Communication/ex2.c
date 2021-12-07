#include "ex1.c"
# include<util/delay.h>
#include<string.h>

int main (void){

   usart_init(MYUBRR); // UBRR =103


  // store member details in an array
   unsigned char  members [ ] = "E/17/407: Hasara , E/17/148: Vidurangi " ; 


    while(1){


      //loop through the array

        for(unsigned char i=0; i< strlen(members);i++){

            usart_send(members[i]); // send characters
           _delay_ms(500); // add 500ms delay
        }
    

    }
  
  return 0;
}
