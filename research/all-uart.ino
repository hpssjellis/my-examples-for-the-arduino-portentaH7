/*
 * Code on the Portenta looks something like
 *  Note these Portenta defines
 * 
 * #define PIN_SERIAL_RX (13ul)
 * #define PIN_SERIAL_TX (14ul)
 * 
 * #define SERIAL2_TX      PA_15
 * #define SERIAL2_RX      PF_6
 * 
 * #define SERIAL2_RTS     PF_8
 * #define SERIAL2_CTS     PF_9
 * 
 * 
 * #define SERIAL1_TX      (digitalPinToPinName(PIN_SERIAL_TX))
 * #define SERIAL1_RX      (digitalPinToPinName(PIN_SERIAL_RX))
 *
*/


#include "mbed.h"
#include "rtos.h"

using namespace mbed;  // sometimes needed
using namespace rtos;

Thread thread;
//Serial pc(PA_2, PA_3);

void myLedBlue_thread(){
   while (true) {
      digitalWrite(LEDB, !digitalRead(LEDB));   //switch on / off
      ThisThread::sleep_for(1000);
      Serial.println("Waiting...");
   }
}

void setup() {
   pinMode(LEDB, OUTPUT);   // LEDB = blue, LEDG or LED_BUILTIN = green, LEDR = red 

   Serial.begin(115200);
   Serial1.begin(115200);
   Serial2.begin(115200);
   Serial3.begin(115200);
   
   thread.start(myLedBlue_thread);
}

void loop() {

  if (Serial.available()) {     // If anything comes in Serial 
    Serial.write(Serial.read());   // read it and send it out Serial (USB)
  }
  if (Serial1.available()) {     // If anything comes in Serial1 
    Serial.write(Serial1.read());   // read it and send it out Serial (USB)
  }
  
  if (Serial2.available()) {     // If anything comes in Serial2 
    Serial.write(Serial2.read());   // read it and send it out Serial (USB)
  }
  
  if (Serial3.available()) {     // If anything comes in Serial3 
    Serial.write(Serial3.read());   // read it and send it out Serial (USB)
  }
  
}


