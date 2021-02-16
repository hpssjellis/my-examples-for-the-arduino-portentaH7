/*
  my01-BlinkM7.ino  for the Portenta H7

  Turns on the blue LED on for one second, then off for three seconds, repeatedly.

  July 22nd, 2020
  by Jeremy Ellis
  Twitter @rocksetta
  Website https://www.rocksetta.com
*/

#include "ArduinoLowPower.h"




void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   //LEDB = blue, LEDG or LED_BUILTIN for uploading, LEDR for error
}

void loop() {

  digitalWrite(LED_BUILTIN, LOW);   
  delay(30);  
  LowPower.deepSleep(200)             
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(1000);    
  digitalWrite(LED_BUILTIN, LOW);   
  delay(300);               
  digitalWrite(LED_BUILTIN, HIGH);
  LowPower.idle(1000);
  delay(30);     
  digitalWrite(LED_BUILTIN, LOW);   
  delay(1000);               
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(6000);  
  LowPower.sleep(2000);             
}
