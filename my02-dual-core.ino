/*
  my02-Dual-Core for the Portenta H7

  This code can be loaded on either core.
  The M7 core will initialize the M4 core
  M7 will flash Blue randomly (under 6 seconds)
  The M4 will flash Green randomly (under 6 seconds)

  July 22nd, 2020
  by Jeremy Ellis
  Twitter @rocksetta
  Website https://www.rocksetta.com

*/

int myLED; 

// the setup function runs once when you press reset or power the board
void setup() {
   randomSeed(analogRead(0));
  #ifdef CORE_CM7  
     LL_RCC_ForceCM4Boot();  
     myLED = LEDB; // on-board blue LED
  #endif

  #ifdef CORE_CM4  
     myLED = LEDG; // on-board greeen LED
  #endif   
   
  pinMode(myLED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
   digitalWrite(myLED, LOW); // turn the LED on (LOW is the voltage level)
   delay(200); // wait for a second
   digitalWrite(myLED, HIGH); // turn the LED off by making the voltage HIGH
   delay( rand() % 5000 + 1000); // wait for a random amount of time below 6 seconds.
}
