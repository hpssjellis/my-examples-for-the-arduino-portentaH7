/*
  my01b-blink-serial.ino  for the Portenta H7

  Turns on the blue LED on for one second, then off for three seconds, repeatedly.
  also checks if Serial Printing is working

  July 22nd, 2020
  by Jeremy Ellis
  Twitter @rocksetta
  Website https://www.rocksetta.com

*/

void setup() {
  Serial.begin(115200);
  pinMode(LEDB, OUTPUT);   // LEDB = blue, LEDG or LED_BUILTIN = green, LEDR = red (typically for errors)
  #ifdef CORE_CM7          // shows how to specifiy a specific core 
    bootM4();
  #endif
}

void loop() {
  Serial.println("Only works on the M7 core, just ignored on the M4 Core, unless you use RPC!")
  digitalWrite(LEDB, LOW);   // Portenta onboard LED connected to 3V3 so ground it to light
  delay(1000);               // wait for a second
  digitalWrite(LEDB, HIGH);  // turn the LED off by not grounding it, weird eh.
  delay(3000);               // wait for 3 seconds
}
