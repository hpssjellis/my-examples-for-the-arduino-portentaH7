#ifdef CORE_CM7

#include "RPC_internal.h"  // comes with the mbed board installation


// Set an M7 core global variable
int myIntGlobal = 1234;
bool myWasUpdated = false;

int setVar(int a) {
  myIntGlobal = (int)a;
  myWasUpdated = true;
}

void setup() {
   RPC1.begin();   
   bootM4();  
   Serial.begin(115200);

   RPC1.bind("setVar", setVar); // do these have to be the same? 
   
  // pinMode(LEDB, OUTPUT);
}

void loop() {
   
  if (myWasUpdated){
     //digitalWrite(LEDB, !digitalRead(LEDB));  // flip LED
     myWasUpdated = false;
     int myTime7 = millis() % 10000;
     Serial.println("Now: " + String(myTime7) + ", then: " + String(myIntGlobal));

  }

}

#endif   // end all M7 core programming




///////////////////////////////// ALL M4 PROGRAMMING //////////////////////////////////////////////

#ifdef CORE_CM4 

#include "RPC_internal.h"  // comes with the mbed board installation 

void setup() {
  
   RPC1.begin(); 
  // pinMode(LEDG, OUTPUT);
   
}


void loop() {
  
   // digitalWrite(LEDG, !digitalRead(LEDG));   // flip green LED
   int myTime = millis() % 10000;               // keeps the unsigned long as an int
   RPC1.call("setVar", myTime ).as<int>();      // date time as an integer  
   delay(1000); // slow the M4 core down only
                  
}

#endif  // end all M4 core programming


