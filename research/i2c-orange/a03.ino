/*  Does not work in fact crashes the portenta.
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



bool myIncoming = false;
int myLastI2C = -1;


void scanI2C() {
  byte error, address;
  int Devices;
  Serial.println();
  Serial.println("I2C Scanner");
  Serial.println("Scanning...");
  Devices = 0;
  for(address = 1; address < 127; address++ )
  {
    Serial.println(address);
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
      Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      Devices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
      Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (Devices == 0)
    Serial.println("No I2C devices found");
  else
    Serial.println("done");
}






void setup(){  
    pinMode(LEDB, OUTPUT);   // LEDB = blue, LEDG or LED_BUILTIN = green, LEDR = red 
    digitalWrite(LEDB,LOW);
         
    Serial.begin(115200);    // start serial for output

    while (!Serial) {}  // wait for monitor
    Serial.println("yup this is running");
    scanI2C();
}

void loop(){
  
}
