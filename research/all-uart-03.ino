#include <Arduino.h>


#include "mbed.h"
#include "rtos.h"

//using namespace mbed;  // sometimes needed
using namespace rtos;

int myLastUart = -1;
Thread thread;

UART mySerial0(PA_0,  PI_9,  NC, NC); //TX, RX, RTS, CTS  NOTE: NC means not connected
UART mySerial1(PA_9,  PA_10, NC, NC);
UART mySerial2(PG_14, PG_9,  NC, NC);
UART mySerial3(PJ_8,  PJ_9,  NC, NC);
UART mySerial8(PA_2,  PA_3,  NC, NC);  // murata modem


void myLedBlue_thread(){
   while (true) {
      digitalWrite(LEDB, !digitalRead(LEDB));   //switch on / off
      ThisThread::sleep_for(1000);
      if (myLastUart >=0) {
         Serial.println("Last Serial message was from UART:" + String(myLastUart));
         myLastUart = -1;
        }
      Serial.println("Waiting...");
   }
}


void setup(){
    pinMode(LEDB, OUTPUT);   // LEDB = blue, LEDG or LED_BUILTIN = green, LEDR = red 
    Serial.begin(115200);
    
    mySerial0.begin(9600);
    mySerial1.begin(9600);
    mySerial2.begin(9600);
    mySerial3.begin(9600);
    mySerial8.begin(9600);
    
    thread.start(myLedBlue_thread);
}

void loop(){
  
  if (mySerial0.available()) {         // If anything comes in Serial0 
     Serial.write(mySerial0.read());   // Read it and send it out Serial (USB)
     myLastUart = 0;                   // Helps to know which UART sent the last message
  }

  if (mySerial1.available()) {     
     Serial.write(mySerial1.read());
     myLastUart = 1;   
  }

  if (mySerial2.available()) {     
     Serial.write(mySerial2.read());
     myLastUart = 2;   
  }

  if (mySerial3.available()) {    
     Serial.write(mySerial3.read()); 
     myLastUart = 3;  
  }

    if (mySerial8.available()) {    
     Serial.write(mySerial8.read()); 
     myLastUart = 8;  
  }

}
