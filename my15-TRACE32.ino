/* 
 *  my15-TRACE32.ino
 *  By @rocksetta aka
 *  Jeremy Ellis
 *  Use at your own Risk! 
 *  
 *  *  This example at https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/blob/master/my15-TRACE32.ino
 *  
 *  My resources and links about Assembly languages at https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/tree/master/ASM
 *  
 *  1. Download TRACE32 from https://www.lauterbach.com/frames.html?download_demo.html 
 *  Scroll down the long page until you see Arduino Pro 
 *  Download and unzip then create a shortcut of the bin--> windows64-->t32marm.exe file to your desktop. 
 *  If you use Ubuntu Linux pre download qt5 with this command
 *  sudo apt-get install qt5-default
 *  as always with Linux expect port permissions issues.
 *  
 * 2. Pro Arduino Tutorial https://www.arduino.cc/pro/tutorials/portenta-h7/por-ard-trace32
 * 
 * 3. Get Your Portenta SN from the Arduino IDE, Tools-->Board Info (plug in Portenta a select port )
 * 
 * 4. license either now or later at https://www.lauterbach.com/frames.html?register_arduino.php
 * 
 * 5. Read your replied email for a license code. Put the long line of code in a file called license.t32
 *    Add a new line for each Portenta you own.
 *    Copy the license.t32 file into the main folder of Trac32
 * 
 * 5. Put the following Thread debug lines in your code, compile and flash as usual
 * 
 * 6. Load Trace32 and click on "Portenta H7 Projects -->Slect Your Arduino Project Directory"
 * 
 * 7. Click on "Arduino Classic IDE"--> must double click the temp file --> click OK
 * 
 * 8. go loop
 * 
 * 9. set a breakpoint if needed
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */


///////////////////// Start: Add thesse lines to your code //////////////////////////////


#include <ThreadDebug.h>

USBSerial              SerialUSB1(false, "DebugPort");
UsbDebugCommInterface  debugComm(&SerialUSB1);
//ThreadDebug            threadDebug(&debugComm, DEBUG_BREAK_IN_SETUP);
ThreadDebug            threadDebug(&debugComm, DEBUG_NO_BREAK_IN_SETUP);



///////////////////// End: Add thesse lines to your code //////////////////////////////


bool myDebug = false; // set to true to insert breakpoint.(stops your code there) 
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
  digitalWrite(LEDB, LOW);              // turn the Portenta Blue LED on 
  Serial.println("Hi from Portenta");
  delay(100);                           // wait a bit 
  digitalWrite(LEDB, HIGH);             // turn the Portenta Blue LED off 
  delay(100);                           // wait a bit 
  Serial.println("Bye from Portenta");
  if (myDebug){debugBreak();}           // if myDebug is true will stop code here
}
