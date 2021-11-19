/* Original by Khoi Hoang (Github @khoih-prog ) and Jeremy Ellis (Github @hpssjellis )
*  
*  SDRAM or regular memory access from both Portenta Cores
*  For regular ram use malloc instead of SDRAM.malloc
*  Define the SDRAM memory on M7
*  Pass that memory location to M4 using RPC
*  Access / set the data in SDRAM from either core
*  Open the serial monitor to see the numbers increase
*
*/

#include "RPC.h"  // comes with the mbed board installation
#include "SDRAM.h"

#ifdef CORE_CM7    // Start M7 Core programming

int myMicroDelay = 5;   // set same for both cores, and try smaller
uint32_t* myByteSDRAM;
uint32_t myInt32;

void setup() {
  bootM4();
  RPC.begin();    
  Serial.begin(115200);
  
  SDRAM.begin(); // is the same as SDRAM.begin(SDRAM_START_ADDRESS);
  myByteSDRAM = (uint32_t*) SDRAM.malloc(sizeof(myInt32));

  // Good to know the memory location 
  // while (!Serial);                     // this is blocking
  // Serial.print("Address = 0x"); 
  // Serial.println((uint32_t) myByteSDRAM, HEX);

   //RPC.call("setVar", (uint32_t) myByteSDRAM);
}


void loop(){
  RPC.call("setVar", (uint32_t) myByteSDRAM);

  if (myInt32 != *myByteSDRAM ) {
    myInt32 = *myByteSDRAM ;   
  }
  Serial.println(myInt32);
  delayMicroseconds(myMicroDelay);
}

#endif  // Done M7 core programming

// ------------------------------------------------------------------------

#ifdef CORE_CM4  // Start M4 core programming

int myMicroDelay = 5;   // set same for both cores, and try smaller

uint32_t* myByteSDRAM = 0;
uint32_t myCount = 0;


bool setVar(uint32_t mySentPointer){
  myByteSDRAM = (uint32_t*) mySentPointer; 
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
  if (myByteSDRAM != 0){
    *myByteSDRAM = myCount;
  } 
  
  delayMicroseconds(myMicroDelay);
}

#endif  // end M4 Core Programming
