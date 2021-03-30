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
MbedI2C  myI2C1(PB_7,  PB_6); 
MbedI2C  myI2C2(PH_12, PH_11); 


bool myIncoming = false;
int myLastI2C = -1;

void setup(){  
    pinMode(LEDB, OUTPUT);   // LEDB = blue, LEDG or LED_BUILTIN = green, LEDR = red 
    
    myI2C0.begin();          // join i2c bus (address optional for master)
    myI2C1.begin();          
    myI2C2.begin();         
    Serial.begin(115200);    // start serial for output
}

void loop()
{
  myI2C0.requestFrom(1, 9);      // slave device #1 request up to 9 bytes 
  myI2C1.requestFrom(1, 9);      
  myI2C2.requestFrom(1, 9);      
  
  while(myI2C0.available()){     // slave may send less than requested
    myIncoming = true;
    char myChar = myI2C0.read(); // receive a byte as character
    Serial.print(myChar);        // print the character
    myLastI2C = 0;
  }
  
  if (myIncoming) {  
      Serial.println();        // just nicely finishes the line.
      myIncoming = false;
  }
  
  while(myI2C1.available()){     // slave may send less than requested
    myIncoming = true;
    char myChar = myI2C1.read(); // receive a byte as character
    Serial.print(myChar);        // print the character
    myLastI2C = 1;
  }
  
  if (myIncoming) {  
      Serial.println();        // just nicely finishes the line.
      myIncoming = false;
  }
  
  while(myI2C2.available()){     // slave may send less than requested
    myIncoming = true;
    char myChar = myI2C2.read(); // receive a byte as character
    Serial.print(myChar);        // print the character
    myLastI2C = 2;
  }
 
  if (myIncoming) {  
      Serial.println();        // just nicely finishes the line.
      myIncoming = false;
  }

  if (myLastI2C >=0) {
     Serial.println("Last Serial message was from I2C:" + String(myLastI2C));
     myLastI2C = -1;
  }
 
  Serial.println("Waiting...");
  delay(1000);
  digitalWrite(LEDB, !digitalRead(LEDB));   //switch back and forth on, off

}
