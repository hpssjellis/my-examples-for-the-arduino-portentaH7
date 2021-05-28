// Easy Dual Core program setup
// If uploaded to the M7 Core erases what was on it and boots the M4 core
// If uploaded to the M4 Core erases what was on it.
// Need to connect pin TX D14 and RX D13 together.

#include <Arduino.h>

//////////////////// Start All Core M7 Programing /////////////////////
#ifdef CORE_CM7 

UART myUART3(PA_9,  PA_10, NC, NC); //TX, TR, RTS, CTS  NOTE: NC means not connected

void setup() { 
   bootM4();    
   Serial.begin(115200);
   myUART3.begin(9600);   // not 115200 does not work on Murata module
}

void loop() {
  if (myUART3.available()) {          // If anything comes in Serial3 
     Serial.write(myUART3.read());   // Read it and send it out Serial (USB)
  }




}

#endif


//////////////////// End All Core M7 Programing /////////////////////

//////////////////// Start All Core M4 Programing /////////////////////

#ifdef CORE_CM4 

int  myCount=48;  //48 = ascii 0,    58 ascii 9

UART myUART3(PA_9,  PA_10, NC, NC); //TX, TR, RTS, CTS  NOTE: NC means not connected

void setup() { 
    pinMode(LEDB, OUTPUT);   // LEDB = blue, LEDG or LED_BUILTIN = green, LEDR = red 
   // Serial.begin(115200);
    myUART3.begin(9600);   // not 115200 does not work on Murata module

}

void loop() {
    myCount++;
   if (myCount >= 58){myCount = 48;}   //48 = ascii 0,    58 ascii 9
   digitalWrite(LEDB, !digitalRead(LEDB));   //switch on / off
   char x = (char)myCount;  //random(48, 57);  // ascii code for numbers 0 to 9
   myUART3.write(x); 
   delayMicroseconds(2);  // start at 100000 and check the order. mine messes up at 2 microseconds
  
    
}

#endif

//////////////////// End All Core M4 Programing /////////////////////
