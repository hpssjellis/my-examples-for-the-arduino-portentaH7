
// this does not work, but what if we specify specific locations for the SDRAM


#ifdef CORE_CM7    // Start M7 Core programming

#include "SDRAM.h"

uint8_t* myByteSDRAM;

uint8_t myCountM7; 
uint8_t myOldByte;

void setup() { 
   bootM4();  
   Serial.begin(115200);
   SDRAM.begin(); // is the same as SDRAM.begin(SDRAM_START_ADDRESS);
   myByteSDRAM = (uint8_t*)SDRAM.malloc(1);   
 }


void loop() {



  
    myCountM7 = *myByteSDRAM;
    if (myOldByte != myCountM7  ){
       myOldByte = myCountM7 ;

    }
        Serial.println(myOldByte);
        delay(200);   
}

#endif  // Done M7 core programming

// ------------------------------------------------------------------------

#ifdef CORE_CM4  // Start M4 core programming

#include "SDRAM.h"

uint8_t* myByteSDRAM;

uint8_t myCount=0;

void setup() {
   SDRAM.begin(); // is the same as SDRAM.begin(SDRAM_START_ADDRESS);
   myByteSDRAM = (uint8_t*)SDRAM.malloc(1);    
}

void loop() {
   myCount += 1;
   if (myCount >= 255) {
      myCount = 0;
   }
   *myByteSDRAM = myCount;              
   delay(50);                   // try different wait times!
   //delayMicroseconds(5000);
             
}

#endif  // end M4 Core Programming
