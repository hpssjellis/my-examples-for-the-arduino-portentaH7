/* Original by Khoi Hoang (Github @khoih-prog ) and Jeremy Ellis (Github @hpssjellis )
*  
*  SDRAM or regular memory access from both Portenta Cores
*  For regular ram use malloc instead of SDRAM.malloc
*  Define the SDRAM memory on M7
*  Pass that memory location to M4 using RPC
*  Access / set the data in SDRAM from either core
*  Open the serial monitor to see the numbers increase
*
*  Note: Each core sketch can be seperated.
*/


#ifdef CORE_CM7    // Start M7 Core programming

#include "RPC.h"  // comes with the mbed board installation
#include "SDRAM.h"


uint32_t* mySdramM7;

void setup() {
  bootM4();
  RPC.begin();    
  Serial.begin(115200);
  
  SDRAM.begin(); // is the same as SDRAM.begin(SDRAM_START_ADDRESS);
  mySdramM7 = (uint32_t*) SDRAM.malloc(sizeof(uint32_t));

  // Good to know the memory location 
  // while (!Serial);                     // this is blocking
  // Serial.print("Address = 0x"); 
  // Serial.println((uint32_t) mySdramM7, HEX);

   //RPC.call("setVar", (uint32_t) mySdramM7);
}


void loop(){
  RPC.call("setVar", (uint32_t) mySdramM7);

  Serial.println(*mySdramM7);

}

#endif  // Done M7 core programming

// ------------------------------------------------------------------------

#ifdef CORE_CM4  // Start M4 core programming

#include "RPC.h"  // comes with the mbed board installation
#include "SDRAM.h"

int myMicroDelay = 7654;   // Slow to match the M7 RPC call
//int myMicroDelay = 34;   // Want this, much faster

uint32_t* mySdramM4 = 0;
uint32_t myCount = 0;

bool setVar(uint32_t mySentPointer){
  mySdramM4 = (uint32_t*) mySentPointer; 
  return true;
}


void setup() {
  RPC.begin();
  SDRAM.begin(); // is the same as SDRAM.begin(SDRAM_START_ADDRESS);
  RPC.bind("setVar", setVar);
}


void loop() {
  myCount++;

  // Must check to avoid crash
  if (mySdramM4 != 0){
    *mySdramM4 = myCount;
  } 
  
  delayMicroseconds(myMicroDelay);
}

#endif  // end M4 Core Programming
