/* 1. Download TRACE32 from https://www.lauterbach.com/frames.html?download_demo.html 
 *  Scroll down the long page until you see Arduino Pro 
 *  Download and unzip then create a shortcut of the bin--> windows64-->t32marm.exe file to your desktop. 
 *  
 * 2. Pro Arduino Tutorial https://www.arduino.cc/pro/tutorials/portenta-h7/por-ard-trace32
 * 
 * 3. Get Your Portenta SN from the Arduino IDE, Tools-->Board Info (plug in Portenta a select port )
 * 
 * 4. Lisense either now or later at https://www.lauterbach.com/frames.html?register_arduino.php
 * 
 * Read your replied email for a lisense code.
 * 
 * 5. Put the following Thread debug lines in your code, compile and install as usual
 * 
 * 6. Make sure your regular Arduino IDE File --> Preeferences --> Show verbose output during: 
 * set with a check for both  compilation and upload
 * 
 * 7. Find your TEMP build folder and open it in a window to look at the files.
 * note AppData is a hidden part of windows, so best to copy the link from the arduino output. 
 * 
 * 8. Load TRACE32
 * 
 * 9. Portenta H7 Demos--> T32ThreadDebug --> FILE (use the above link and choose the .elf file)
 * 
 * 10. Load Debug symbols (Do not flash as it looks for the wrong .bin file)
 * 
 * 11. reset protenta (Single click)
 * 
 * 12. Insert License data and save if asked
 * 
 * 13. On the terminal line labelled B:: type go loop
 * 
 * 14. Right click to set breakpoint. Then keep clicking "GO"
 * 
 * 15. In the Var --> Watch window type myLoop to see it changing
 * 
 * 16. Right click the Term.View window to clear it.
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */


///////////////////// Start Add thesse lines to your code //////////////////////////////


#include <ThreadDebug.h>

USBSerial              SerialUSB1(false, "DebugPort");
UsbDebugCommInterface  debugComm(&SerialUSB1);
ThreadDebug            threadDebug(&debugComm, DEBUG_NO_BREAK_IN_SETUP);



///////////////////// End Add thesse lines to your code //////////////////////////////



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
