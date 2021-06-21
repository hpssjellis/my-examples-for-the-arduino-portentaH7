

#include "RPC_internal.h"  // comes with the mbed board installation

int myLED; 
int myDelay;
unsigned long delayStart = 0;  

#ifdef CORE_CM7
struct myStruct {
  bool myNewEntry;
  int x;
  float y;
  char z;
  char myCharArray[6];
};

myStruct myTestStruct = {true, 5, 3.4, 'H','e','l','l','o'};



int setVar(int a) {
  myTestStruct.x = (int)a;
  myTestStruct.myNewEntry = true;
  return a;
}


#endif

void setup() {
   randomSeed(analogRead(A0));
   delayStart = millis();   // set delay
   myDelay = rand() % 5000 + 1000;
   RPC1.begin();
   
  #ifdef CORE_CM7  
     bootM4();  
     myLED = LEDB; // on-board blue LED
     Serial.begin(115200);

     RPC1.bind("setVar", setVar); // do these have to be the same?
  
  #endif

  #ifdef CORE_CM4  
     myLED = LEDG; // on-board greeen LED
  #endif   
   
  pinMode(myLED, OUTPUT);
}

void loop() {
    if ( (millis() - delayStart ) < 200) { 
   digitalWrite(myLED, LOW); // turn the Portenta on-board LED on 
    } else {
     digitalWrite(myLED, HIGH); // turn the Portenta on-board LED off
   }
 
  if ( (millis() - delayStart ) >= myDelay) {
   delayStart = millis(); //  reset the delay time
   myDelay = rand() % 5000 + 1000; // reset delay
    
   #ifdef CORE_CM4  
     RPC1.println("Blinking Green From M4 Core, then delaying " + String(myDelay) + " milliseconds");
  
     int myRand = rand() % 100;  // from 0 to 99
     auto res = RPC1.call("setVar", myRand).as<int>();
     RPC1.println("From M4 core setting M7 variable to: " + String(res));
   
   #endif   
  
   #ifdef CORE_CM7   
     Serial.println("---------------------------------");
     Serial.println("From M7 showing global variable: "+ String(myTestStruct.x));
     Serial.println("Blinking Blue From M7 Core, then delaying " + String(myDelay) + " milliseconds");
     while (RPC1.available()) {
       Serial.write(RPC1.read()); // check if the M4 has sent an RPC println
     }
   #endif  
  } // end main interval if
   //delay(myDelay); // Wait for a random amount of time below 6 seconds.
                  // Code would be better using a timer instead of a delay
}
