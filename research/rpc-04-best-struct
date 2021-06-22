#ifdef CORE_CM7    // Start M7 Core programming

#include "RPC_internal.h"  // comes with the Arduino mbed core installation

// Define the structure
struct myStruct {
  bool  myNewEntry;
  int   x;
  float y;
  char  z;
  char  myCharArray[6];
};


//Activate the structure
myStruct myTestStruct;  // = {true, 5, 3.4, 'H','e','l','l','o'};


// Procedure to change the structure
int setVar(int a) {
    myTestStruct.x = (int)a;
    myTestStruct.myNewEntry   = true;
    return a;
  }


void setup() {
   RPC1.begin();
   bootM4();  
   Serial.begin(115200);

   // Allow the M4 core to change the structure
   RPC1.bind("setVar", setVar); // do these have to be the same?      
}


void loop() {
    if (myTestStruct.myNewEntry){
       Serial.println(String(myTestStruct.x));
       myTestStruct.myNewEntry = false;
    }
    
}

#endif  // Done M7 core programming

// ------------------------------------------------------------------------

#ifdef CORE_CM4  // Start M4 core programming

#include "RPC_internal.h"  // comes with the mbed board installation

int myCount=0;

void setup() {
   RPC1.begin();         
}

void loop() {
   myCount += 1;
   if (myCount >= 10000) {
      myCount = 0;
   }
   
                // important for this delay to be before the RPC call ??
                // Does not gracefully die, either works or doesn't
   delay(50);   // delay(50); CAREFUL, THIS DELAY MUST BE ENOUGH for the RPC
   auto res = RPC1.call("setVar", myCount).as<int>();
             
}

#endif  // end M4 Core Programming
