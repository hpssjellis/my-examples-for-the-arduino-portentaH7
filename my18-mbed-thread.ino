#include "mbed.h"
#include "rtos.h"

//using namespace mbed;  // sometimes needed
using namespace rtos;

Thread thread;

void myLedBlue_thread(){
   while (true) {
      digitalWrite(LEDB, !digitalRead(LEDB));   //switch on / off
      ThisThread::sleep_for(1000);
   }
}

void setup() {
   pinMode(LEDB, OUTPUT);   // LEDB = blue, LEDG or LED_BUILTIN = green, LEDR = red 
   thread.start(myLedBlue_thread);
}

void loop() {
  // put your main code here, to run repeatedly:

}
