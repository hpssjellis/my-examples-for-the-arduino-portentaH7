#include <ThreadDebug.h>
// Define SerialUSB1 as serial debug port
// use DEBUG_BREAK_IN_SETUP to break the program at setup() entry, waiting for debugger connection.
// use DEBUG_NO_BREAK_IN_SETUP to let the program start normally, debugger can attach later.
USBSerial SerialUSB1(false, "DebugPort");
UsbDebugCommInterface  debugComm(&SerialUSB1);
ThreadDebug            threadDebug(&debugComm, DEBUG_NO_BREAK_IN_SETUP);

int myLoop = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LEDB, OUTPUT);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  myLoop += 1;
  digitalWrite(LEDB, LOW);   // turn the LED on (HIGH is the voltage level)
  Serial.println("Hi from Portenta");
  delay(100);                       // wait for a second
  digitalWrite(LEDB, HIGH);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
  Serial.println("Bye from Portenta");
  //debugBreak();
}
