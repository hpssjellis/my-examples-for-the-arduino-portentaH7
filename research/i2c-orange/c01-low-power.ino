// Use at your own risk
// I have no idea what I am doing
// Tring to turn of Portenta Chips such as BLE etc.


//#ifdef ARDUINO_PORTENTA_H7_M7

#include "Portenta_System.h"
#include "Wire.h"
#include "mbed.h"

#define PMIC_ADDRESS 0x08

arduino::Portenta_System PortentaH7;

bool myResult;

void setup(){
  Serial.begin(115200);
  while (!Serial) {}  // wait for the Serial monitor
  myResult = PortentaH7.begin();
  Serial.print("PortentaH7.begin(); activated: ");
  Serial.println(myResult);

}

void loop(){
  
}

//#endif
