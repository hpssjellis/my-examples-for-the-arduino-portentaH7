/*
  my01b-blink-serial.ino  for the Portenta H7

  Turns on the blue LED on for one second, then off for three seconds, repeatedly.
  also checks if Serial Printing is working

  July 22nd, 2020
  by Jeremy Ellis
  Twitter @rocksetta
  Website https://www.rocksetta.com

*/

#define myDebug   // comment out for regular




#ifdef myDebug
   
   #include <ThreadDebug.h>

      // Define SerialUSB1 as serial debug port
      // use DEBUG_BREAK_IN_SETUP to break the program at setup() entry, waiting for debugger connection.
      // use DEBUG_NO_BREAK_IN_SETUP to let the program start normally, debugger can attach later.  
   USBSerial SerialUSB1(false, "DebugPort");
   UsbDebugCommInterface  debugComm(&SerialUSB1);
   ThreadDebug            threadDebug(&debugComm, DEBUG_NO_BREAK_IN_SETUP); 

#endif

int myLoop = 6;

void setup() {
  Serial.begin(115200);
  pinMode(LEDB, OUTPUT);   // LEDB = blue, LEDG or LED_BUILTIN = green, LEDR = red (typically for errors)

}

void loop() {
   myLoop += 1;
   digitalWrite(LEDB, LOW);   // Portenta onboard LED connected to 3V3 so ground it to light

   #ifdef myDebug  
      debugBreak(); 
   #else 
      delay(1000);  
   #endif
   
   Serial.println("Serial print works on the M7 core");
   digitalWrite(LEDB, HIGH);  // turn the LED off by not grounding it, weird eh.
   
   #ifdef myDebug
      debugBreak();   
   #else 
      delay(1000);  
   #endif              
}
