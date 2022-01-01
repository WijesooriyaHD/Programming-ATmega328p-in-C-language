/*
CO 321 - Lab7 Exercise 3

*/
#include <avr/io.h>
#include <LiquidCrystal.h>
#include <util/delay.h>

#define max_length 10

// initialize the library with the numbers of the interface pins
// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  

// Array to store Keypad characters
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//Function to read character of keypad
char readKeyPad() {
  
  // loop until an user input key is found
  while (1) {
    
    // First, when no buttons are pressed, all of the column pins 
    // are held HIGH, and all of the row pins are held LOW:
    for (int row = 0; row < 4; row++){
      
      PORTC &= 0b11110000;   // setting low to all rows 
      PORTC |= (1 << row);     // Setting High the ith row
    
      // sequentially scaning jth row 
      for (int column = 0; column < 4; column++) {
        
        if ((PINB >> column) & 1){
        	_delay_ms(300);
            return(keys[row][column]);
        }
      }
    }
  }
}


// function to return the cipher encrypted key
void cipher(char *ch, int key){
  	// to position the cursor
    int position = 0;       
    char *p = ch, output;

    while(*p != '#'){

        // set the new cursor position
        lcd.setCursor(position, 1);

        // encryption for A,B,C,D
        if(*p > 64 && *p < 69){
            output = (*p - 65 + key)%4 + 65;
            lcd.print(output);
        }
        // encryption for 0 - 9
        else if(*p > 47 && *p < 58){
            output = (*p - 48 + key)%10 + 48;
            lcd.print(output);
        }
        // encryption for '*'
        else{
            lcd.print(*p);
        }

        //increment the pointers
        position++;
        p++;
    }
}

//........... EEPROM ...............//
// Function to write EEPROM
void EEPROMwrite(unsigned int address , char data){

    //wait for completion of previous write
    while(EECR & (1 << EEPE)); 

    //set up address and data regs
    EEAR = address;
    EEDR = data;

    EECR = EECR | (1 << EEMPE); //write logical 1 to EEMPE

    EECR = EECR | (1 << EEPE); // start eeprom write
}

// Function to read from EEPROM
char  EEPROMread(unsigned int address){

    // wait for completion of writes
    while( EECR & (1 << EEPE)); 

    EEAR = address; //set up address

    EECR = EECR | (1 << EERE); //start eeprom read

    return EEDR; //return data
}

int main(){
	// initiate LCD's number of columns and rows:
    lcd.begin(16, 2);         
    
  	// PC0, PC1, PC2, PC3 as rows of keypad
  	DDRC |= 0b00001111;	
  	// PB0, PB1, PB2, PB3 as columns of keypad
  	DDRB &= ~(0b00001111);
  
  	// to store key value
    char index, buffer;
  
  	// to get user inputs
  	char plain_text[max_length];
    
  	// to set cursor position
    int coodinate = 0;
  
  	// read from EEPROM
    int key = EEPROMread(0);
    
    while(1){
      	// select option to encrpt or change key
        lcd.setCursor(0, 0);
        lcd.print("Encrypt Text : 1");
        lcd.setCursor(0, 1);
        lcd.print("Change key : 2");
        
      	// read option and put it into buffer
        buffer = readKeyPad();
      	//clear the screen
        lcd.clear();
        
      	// When option is Encrpt text    
        if(buffer == '1'){   
        	// get user input
            lcd.setCursor(0, 0);
            lcd.print("Enter Plain Text:");
            
            buffer = '0';
            coodinate = 0;
            
            index = 0;
            lcd.setCursor(0, 1);
            
            // Get characters until it is #
            while(buffer != '#' && index != max_length){
                buffer = readKeyPad();
                lcd.print(buffer);
                coodinate++;
                
                // add each character to plain text array
                plain_text[index] = buffer;
                index++;                
                lcd.setCursor(coodinate, 1);
            }
			
          	// Set last element of array as #
            plain_text[index] = '#';
            lcd.clear();
            
          	// Display encrypt text
            lcd.setCursor(0, 0);
            lcd.print("Cipher Text : "); 
            lcd.setCursor(0, 1);
            cipher(plain_text, key);
          
            // press any key to go for options again
            readKeyPad();  
            lcd.clear();
            
        } 
      	// when option is "change key"
        else if(buffer == '2'){ 
            // set key
            key = 0;
            lcd.setCursor(0, 0);
            lcd.print("Enter key:");
            lcd.setCursor(0, 1);
            lcd.print("__");
            
            // read new key
            buffer = readKeyPad();
            lcd.setCursor(0, 1);
            lcd.print(buffer);
            
            // get the first digit for key
            key += (buffer - '0') * 10;
                
            _delay_ms(250);
            
            // get input for second digit
            buffer = readKeyPad();
            lcd.setCursor(1, 1);
            lcd.print(buffer);
            key += (buffer - '0');
          	// write to EEPROM
            EEPROMwrite(0,key);    

          	_delay_ms(500);
            lcd.clear();
            lcd.print("  Key changed ");
            lcd.setCursor(1, 1);
            lcd.print("Successfully!!");
          
            // enter any key to clear the screen 
            readKeyPad();  
            lcd.clear();
                
        }else{
            // When user input is invalid
            lcd.setCursor(1, 0);
            lcd.write(" Invalid input!! ");
          	lcd.setCursor(4, 1);
            lcd.print("Try Again.");
            _delay_ms(900);
            lcd.clear();
        }
        _delay_ms(150);
    
    }
    return 0;
}