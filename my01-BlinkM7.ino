/*
  my01-BlinkM7.ino  for the Portenta H7

  Turns on the blue LED on for one second, then off for three seconds, repeatedly.

  July 22nd, 2020
  by Jeremy Ellis
  Twitter @rocksetta
  Website https://www.rocksetta.com

*/

void setup() {
  pinMode(LEDB, OUTPUT);   //LEDB = blue, LEDG or LED_BUILTIN for uploading, LEDR for error
}

void loop() {
  digitalWrite(LEDB, LOW);   // Portenta onboard LED connected to 3V3 so ground it to light
  delay(1000);               // wait for a second
  digitalWrite(LEDB, HIGH);  // turn the LED off by not grounding it, weird eh.
  delay(3000);               // wait for 3 seconds
}
