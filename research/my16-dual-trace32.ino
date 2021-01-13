/*
 * my02f_easy_m4_rpc_print.ino for the Portenta H7
 *
 * The PortentaH7 M4 core can not print to the serial monitor
 * On the M4 core if you do a Serial.Println it goes to the TX RX UART output pins
 * This program uses RPC to redirect Serial.println to the M7 core 
 * so that regular sketches still work with serial monitor output from the M4 core
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










#ifdef CORE_CM7             // Start M7 programming
 
#include "RPC_internal.h"  // comes with the mbed board installation

#include <ThreadDebug.h>
 
USBSerial              SerialUSB1(false, "DebugPort");
UsbDebugCommInterface  debugComm(&SerialUSB1);
ThreadDebug            threadDebug(&debugComm, DEBUG_NO_BREAK_IN_SETUP);


int myLED; 

void setup() {
   bootM4(); 
   Serial.begin(115200);
   RPC1.begin();
   myLED = LEDB; // on-board blue LED
   pinMode(myLED, OUTPUT);
}

void loop() {
  
   Serial.println("Hello from M7 regular Serial");
   while (RPC1.available()) {
      Serial.write(RPC1.read()); 
   }  
   digitalWrite(myLED, LOW); 
   delay(200); 
   digitalWrite(myLED, HIGH); 
   delay( rand() % 5000 + 1000); 
}

#endif              // End all M7 core programming

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CORE_CM4             // Start M4 programming

#include "RPC_internal.h"  // comes with the mbed board installation

#define Serial RPC1       // So the M4 regular serial prints to RPC

#include <ThreadDebug.h>

UartDebugCommInterface debugComm(SERIAL1_TX, SERIAL1_RX, 230400);
ThreadDebug            threadDebug(&debugComm, DEBUG_NO_BREAK_IN_SETUP);  



int myLED; 
  
void setup() {   
   randomSeed(analogRead(A0));
   Serial.begin();   // RPC begin does not take an integer
   myLED = LEDG;     // on-board greeen LED
   pinMode(myLED, OUTPUT);
}

void loop() {
   Serial.println("Hello from M4 using regular serial piped through RPC"); 
  
   digitalWrite(myLED, LOW); 
   delay(200); 
   digitalWrite(myLED, HIGH); 
   delay( rand() % 5000 + 1000); // wait for a random amount of time below 6 seconds.
}

#endif            // End all M4 core programming
