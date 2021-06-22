#ifdef CORE_CM7

#include "RPC_internal.h"  // comes with the Arduino mbed core installation

  int myIntGlobal = 1234;
  bool myNewData = false;

  int setVar(int a) {
    myIntGlobal = (int)a;
    myNewData   = true;
    return a;
  }


void setup() {
   randomSeed(analogRead(A0));
   RPC1.begin();
   bootM4();  
   Serial.begin(115200);

   RPC1.bind("setVar", setVar); // do these have to be the same?
       
}


void loop() {
    delay(200);
    int myDelay = rand() % 5000 + 1000;
    if (myNewData){
      Serial.println("From M7 showing global variable: "+ String(myIntGlobal));
      myNewData = false;
      //delay(myDelay); 
    }
}

#endif  // M7 core

// ------------------------------------------------------------------------

#ifdef CORE_CM4

#include "RPC_internal.h"  // comes with the mbed board installation

void setup() {
   randomSeed(analogRead(A0));
   RPC1.begin();
          
}


void loop() {
   delay(200); // wait for a second
   int myDelay = rand() % 5000 + 1000;
 
   int myRand = rand() % 100;  // from 0 to 99
   auto res = RPC1.call("setVar", myRand).as<int>();

   delay(myDelay); 
                  
}

#endif  // end M4 Core
