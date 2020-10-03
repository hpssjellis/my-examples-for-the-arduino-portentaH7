Just lots of not working things in this folder.

Note: Try the new mbed board version 1.2.3 for the Nano33BLE and PortentaH7

Not official yet so will need to put in your preferences comma seperated list 

http://downloads.arduino.cc/packages/package_mbed_staging_index.json

and if you find issues put them here

https://github.com/arduino/ArduinoCore-mbed/issues


I will just do a stream of concsiousness while I fly through my examples.


## Working
[../my00-dual-clean.ino](../my00-dual-clean.ino), [../my01-BlinkM7.ino](../my01-BlinkM7.ino), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../)


## Issues

1. While not relevant to just this version: unlike most arduino boards this board install (write at the end of the installation) has something that requires admin access. At school it installs, I can compie but I think uploading to the Portenta does not work, while uploading to the Nano33BLE works.

2. Running the example RPC --> serialpassthrough_RPC

seriously needs some comments and explaining to do. I run the code on M7, it says M4 is passing reular serial (What magic is this, where is the code that magically got installed on M4). I run serial.println("hi") on M4 and nothing happens. If the first code is writing to both M7 and M$ I want to know how. also I need an example of how to print from M4 

I think I will leave this one for a bit. Need to talk to someone about it. Does look like RPC works without making any changes to files.txt anymore.

Tried one last time on M4

```
#include "RPC_internal.h"  

#define Serial RPC1  // So the M4 regular serial prints to RPC

  
void setup() {
   Serial.begin();   // RPC begin does not take an integer
}

void loop() {
  Serial.println("Hello from M4 using regular serial piped through RPC"); 
  
  delay(5000);
}


```
