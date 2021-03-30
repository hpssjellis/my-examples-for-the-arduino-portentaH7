/*
*
* Master for this I2C will be the Portenta
* Portenta SDA on D11
Portneta SCL on D12
*
*
* 
* 
* I2C0 SDA PH_8
* I2C0 SCL PH_7
* 
* I2C1 SDA PB_7
* I2C1 SCL PB_6  labelled SD6 ??
* 
* I2C2 SDA PH_12
* I2C2 SCL PH_11
* 
* 
*
*/

#include <Wire.h>

MbedI2C  myI2C0(PH_8,  PH_7);  //MbedI2C(int sda, int scl);
//MbedI2C  myI2C1(PB_7,  PB_6); 
//MbedI2C  myI2C2(PH_12, PH_11); 



bool myIncoming = false;

void setup(){  
    pinMode(LEDB, OUTPUT);   // LEDB = blue, LEDG or LED_BUILTIN = green, LEDR = red 
    myI2C0.begin();          // join i2c bus (address optional for master)
    Serial.begin(115200);    // start serial for output
}

void loop()
{
  myI2C0.requestFrom(1, 9);    // request 9 bytes from slave device #1
  
  while(myI2C0.available()){    // slave may send less than requested
    myIncoming = true;
    char myChar = myI2C0.read(); // receive a byte as character
    Serial.print(myChar);      // print the character
  }
  if (myIncoming) {  
      Serial.println();        // just nicely finishes the line.
      myIncoming = false;
  }
  Serial.println("Waiting...");
  delay(1000);
  digitalWrite(LEDB, !digitalRead(LEDB));   //switch back and forth on, off

}
