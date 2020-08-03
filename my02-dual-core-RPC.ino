/*
 * my02-Dual-Core-RPC for the Portenta H7
 *
 * This code can be loaded on either core.
 * The M7 core will initialize the M4 core
 * The M7 will flash Blue randomly (under 6 seconds)
 * The M7 core will serial print its own messges
 * The M7 core will serial print messages it receives from the M4 core
 * The M4 will flash Green randomly (under 6 seconds)
 *
 * Note: The M4 core will not compile unless -fexceptions is added 
 * to the bottom of the files: 
 * cflags.txt
 * cxxflags.txt 
 * at
 * C:\Users\<USER>\AppData\Local\Arduino15\packages\arduino-beta\hardware\mbed\1.2.2\variants\PORTENTA_H7_M4
 *
 * Note: AppData is hidden so find it directly
 * 
 * updated August 2nd, 2020
 * by Jeremy Ellis
 * Twitter @rocksetta
 * Website https://www.rocksetta.com
 *
*/

#include "RPC_internal.h"  // comes with the mbed board installation

int myLED; 

void setup() {
   randomSeed(analogRead(A0));
   RPC1.begin();
   
  #ifdef CORE_CM7  
     LL_RCC_ForceCM4Boot();  
     myLED = LEDB; // on-board blue LED
     Serial.begin(115200);
  #endif

  #ifdef CORE_CM4  
     myLED = LEDG; // on-board greeen LED
  #endif   
   
  pinMode(myLED, OUTPUT);
}

void loop() {
   digitalWrite(myLED, LOW); // turn the Portenta on-board LED on 
   delay(200); // wait for a second
   digitalWrite(myLED, HIGH); // turn the Portenta on-board LED off 
   int myDelay = rand() % 5000 + 1000;
   
   #ifdef CORE_CM4  
     RPC1.println("Blinking Green From M4 Core, then delaying " + String(myDelay) + " milliseconds");
   #endif   
  
   #ifdef CORE_CM7  
     Serial.println("Blinking Blue From M7 Core, then delaying " + String(myDelay) + " milliseconds");
     while (RPC1.available()) {
       Serial.write(RPC1.read()); // check if the M4 has sent an RPC println
     }
   #endif  

  delay(myDelay); // Wait for a random amount of time below 6 seconds.
                  // Code would be better using a timer instead of a delay
}
