/**
* Blinking example using threaded timer 
* By  : Waleed El-Badry
* Date: 20/02/2021
**/

// Threaded timer library: https://github.com/Aduen/ThreadedTimer
#include <threadedtimer.h>


// Thread Object
ThreadedTimer t1;

// Task ID
int taskBlink;

// Blue LED on RGB
int led = LEDB;

// Variable to save last LED status
volatile bool led_status = true;


// Blinking routine
void blinking()
{
  digitalWrite(led, led_status);
  led_status = !led_status;
}

void setup() 
{

  // Set LED GPIO as output
  pinMode(led, OUTPUT);

  // Create blinking task to enter every blinking() routine every 500 ms
  taskBlink = t1.every(500, blinking);
  
}

void loop() 
{
  delay(2000); //main loop delay does not affect the running Timers
}
