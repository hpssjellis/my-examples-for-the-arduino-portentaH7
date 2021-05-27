/*
 * Code on the Portenta looks something like
 *  Note these Portenta defines
 *
 * From the schematics for the Portenta https://content.arduino.cc/assets/Pinout-PortentaH7_latest.pdf
 * UART0 TX PA_0
 * UART0 RX PI_9
 *
 * UART1 TX PA_9
 * UART1 RX PA_10
 
 * UART2 TX PG_14
 * UART2 RX PG_9
 
 * UART3 TX PJ_8
 * UART3 RX PJ_9
 *
 * 
 *
*/


#include <Arduino.h>


#include "mbed.h"
#include "rtos.h"

//using namespace mbed;  // sometimes needed
using namespace rtos;

//int myLastUart = -1;
Thread thread;

UART mySerial3(PJ_8,  PJ_9,  NC, NC); //TX, TR, RTS, CTS  NOTE: NC means not connected




void myLedBlue_thread(){
   while (true) {
      digitalWrite(LEDB, !digitalRead(LEDB));   //switch on / off
      ThisThread::sleep_for(1000);

      Serial.println(".");

   }
}


void setup(){
    pinMode(LEDB, OUTPUT);   // LEDB = blue, LEDG or LED_BUILTIN = green, LEDR = red 
    Serial.begin(115200);
    mySerial3.begin(9600);   // not 115200 does not work on Murata module
   
    thread.start(myLedBlue_thread);
}

void loop(){

  if (mySerial3.available()) {          // If anything comes in Serial0 
     Serial.write(mySerial3.read());   // Read it and send it out Serial (USB)
  }


     
}
