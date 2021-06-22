#ifdef CORE_CM7

#include "RPC_internal.h"  // comes with the Arduino mbed core installation

struct myStruct {
  bool myNewEntry;
  int x;
  float y;
  char z;
  char myCharArray[6];
};

myStruct myTestStruct;  // = {true, 5, 3.4, 'H','e','l','l','o'};





 // int myIntGlobal = 1234;
  //bool myNewData = false;

  int setVar(int a) {
    myTestStruct.x = (int)a;
    myTestStruct.myNewEntry   = true;
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
    if (myTestStruct.myNewEntry){
      Serial.println("From M7 showing global variable: "+ String(myTestStruct.x));
      myTestStruct.myNewEntry = false;

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
   int myDelay = rand() % 1000 + 1000;
 
   int myRand = rand() % 100;  // from 0 to 99
   auto res = RPC1.call("setVar", myRand).as<int>();

   delay(myDelay); 
                  
}

#endif  // end M4 Core
