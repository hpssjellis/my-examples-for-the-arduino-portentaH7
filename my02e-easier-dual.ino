/*
 * my02-Dual-Core for the Portenta H7
 *
 * This code can be loaded on either core.
 * The M7 core will initialize the M4 core
 * The M7 will flash Blue randomly (under 6 seconds)
 * The M7 core will serial print its own messges
 * The M7 core will serial print messages it receives from the M4 core
 * The M7 core will continuously print the "myIntGlobal" variable
 * 
 * The M4 will flash Green randomly (under 6 seconds)
 * The M4 will randomly set the M7 variable "myIntGlobal"
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
 *I have re-written this to make larger programs easier
 *by seperating the M7 and M4 code completely.
 *
*/




///////////////////////////////// ALL M7 PROGRAMMING //////////////////////////////////////////////
#ifdef CORE_CM7

  #include "RPC_internal.h"  // comes with the mbed board installation
  int myLED; 

  // Set an M7 core global variable
  int myIntGlobal = 1234;

  int setVar(int a) {
    myIntGlobal = (int)a;
    return a;
  }

void setup() {
   randomSeed(analogRead(A0));
   RPC1.begin();
    
   bootM4();  
   myLED = LEDB; // on-board blue LED
   Serial.begin(115200);

   RPC1.bind("setVar", setVar); // do these have to be the same? 
   
   pinMode(myLED, OUTPUT);
}

void loop() {
   
  // Serial.println("---------------------------------");
  // Serial.println("From M7 showing global variable: "+ String(myIntGlobal));
   while (RPC1.available()) {
     digitalWrite(myLED, LOW); // turn the Portenta on-board LED on 
     Serial.write(RPC1.read()); // check if the M4 has sent an RPC println
   }  
   delay(100); // minor slow down just for fun
   digitalWrite(myLED, HIGH); // turn the Portenta on-board LED off 
}


#endif   // end al M7 core programming






///////////////////////////////// ALL M4 PROGRAMMING //////////////////////////////////////////////
#ifdef CORE_CM4 
  #include "RPC_internal.h"  // comes with the mbed board installation
  int myLED; 

void setup() {
   randomSeed(analogRead(A0));
   RPC1.begin();
   myLED = LEDG; // on-board greeen LED
   
   pinMode(myLED, OUTPUT);
}


void loop() {
   digitalWrite(myLED, LOW); // turn the Portenta on-board LED on 
   delay(200); // wait for a second
   digitalWrite(myLED, HIGH); // turn the Portenta on-board LED off 

   int myRand = rand() % 100;  // from 0 to 99
   auto res = RPC1.call("setVar", myRand).as<int>();
   RPC1.println("From M4 core setting M7 variable to: " + String(res));
    

   delay(3000); // slow the M4 core down only
                  
}

#endif  // end all M4 core programming












