/*
 * for the Portenta H7
 *
 * The PortentaH7 M4 core can not print to the serial monitor
 * On the M4 core if you do a Serial.Println it goes to the TX RX UART output pins
 * This program uses RPC to redirect Serial.println to the M7 core 
 * so that regular sketches still work with serial monitor output from the M4 core
 *

 * 
 * updated August 2nd, 2020
 * by Jeremy Ellis
 * Twitter @rocksetta
 * Website https://www.rocksetta.com
 *
 *I have re-written this to make larger programs easier
 *by seperating the M7 and M4 code completely.
 *
*/

#ifdef CORE_CM7   // Start M7 programming
 
#include "RPC_internal.h"  // comes with the mbed board installation

unsigned long previousMillis = 0;        // will store last time 
unsigned  long interval = 2000;  

void setup() {
   bootM4(); 
   Serial.begin(115200);
   RPC1.begin();
}

void loop() {
  
   while (RPC1.available()) {
      Serial.write(RPC1.read()); 
   }  
  unsigned long currentMillis = millis(); 
  if(currentMillis - previousMillis > interval) {  //wait 5 seconds to run
     // save the last time you blinked the LED 
    previousMillis = currentMillis; 
    
   int myRand1 = rand() % 100;  // from 0 to 99
   int myRand2 = rand() % 100;  // from 0 to 99
   RPC1.call("setVar", (int)myRand1, (int)myRand2);    //.as<int>();
   Serial.println("From M7 core setting M4 variable to: " + String(myRand1) +", "+ String(myRand2));
   
   Serial.println("Hello from M7 regular Serial");
  }
}

#endif              // End all M7 core programming

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CORE_CM4    // Start M4 programming

#include "RPC_internal.h"  // comes with the mbed board installation

#define Serial RPC1  // So the M4 regular serial prints to RPC


  // Set an M4 core global variable
int myIntGlobal1 = 1234;
int myIntGlobal2 = 1234;

void setVar(int a, int b) {
  myIntGlobal1 = (int)a;
  myIntGlobal2 = (int)b;
 // return String(a) +", "+ String(b);
}


unsigned long previousMillis = 0;        // will store last time 
unsigned  long interval = 5000;  

void setup() {
   Serial.begin();   // RPC begin does not take an integer
     RPC1.bind("setVar", setVar); // do these have to be the same?

}

void loop() {
  

  unsigned long currentMillis = millis(); 
  if(currentMillis - previousMillis > interval) {  //wait 5 seconds to run
    previousMillis = currentMillis; 
   
    Serial.println("---------------------------------");
    Serial.println("From M4 showing global variable: "+ String(myIntGlobal1)+ ", "+ String(myIntGlobal2));
    Serial.println("Hello from M4 using regular serial piped through RPC");
  } 
}

#endif            // End all M4 core programming
