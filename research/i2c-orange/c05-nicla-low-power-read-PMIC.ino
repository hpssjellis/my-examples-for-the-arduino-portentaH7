#include "STM32H747_System.h"
#include "Nicla_Vision_System.h"
#include "Wire.h"
#define PMIC_ADDRESS 0x08

bool showCount = false;
bool myGoodI2C = false;


const byte one = 0x01;
const byte zero = 0x00;
const byte sendRestart = false;

String getString(reset_reason_t val) {
  switch (val){
  case RESET_REASON_POWER_ON:
    return "Reset Reason Power ON";
  case RESET_REASON_PIN_RESET:
    return "Reset Reason PIN Reset";
  case RESET_REASON_BROWN_OUT:
    return "Reset Reason Brown Out";
  case RESET_REASON_SOFTWARE:
    return "Reset Reason Software";
  case RESET_REASON_WATCHDOG:
    return "Reset Reason Watchdog";
  case RESET_REASON_LOCKUP:
    return "Reset Reason Lockup";
  case RESET_REASON_WAKE_LOW_POWER:
    return "Reset Reason Wake Low Power";
  case RESET_REASON_ACCESS_ERROR:
    return "Reset Reason Access Error";
  case RESET_REASON_BOOT_ERROR:
    return "Reset Reason Boot Error";
  case RESET_REASON_MULTIPLE:
    return "Reset Reason Multiple";
  case RESET_REASON_PLATFORM:
    return "Reset Reason Platform";
  case RESET_REASON_UNKNOWN:
    return "Reset Reason Unknown";
  default:
    return "N/A";
  }
}


void readI2C(byte devAddr3, int m, int n){
  Serial.println();
  Serial.print("Using I2C device address: ");
  Serial.println(devAddr3, HEX);
  Serial.println();
  if (showCount){
     Serial.println("#  | HEX VALUES");  
     Serial.print("0");  // starting zero
  } else {
     Serial.println("HEX VALUES"); 
  }
  for (int i = 0; i < m; i++){
    if (showCount){
      Serial.print(byte(i*16), HEX);
      Serial.print(" | 0x");
    } else {
      Serial.print("0x");  // starting HEX   
    }
    for (int j = 0; j < n; j++){
      Wire1.beginTransmission(devAddr3);
      int nWritten = 0;
      nWritten += Wire1.write(uint16_t(i*16+j));
      int error = Wire1.endTransmission(sendRestart);
      if (error != 0){
        Serial.print("Transmission error, code = ");
        Serial.println(error);
      }
      int nRead = Wire1.requestFrom(devAddr3, one);
      if (nRead == 1){
        byte valRead = Wire1.read();
        if (valRead == 0){Serial.print("0");} // add an extra zero
        if (valRead <= 15 && valRead >= 1 ) {Serial.print("0");} // extra zero
     
        // Serial.print(valRead, HEX);
        // want the letters in lowercase
        char tBuf[8];
        sprintf(tBuf,"%x",valRead); // lower case
        Serial.print(tBuf);
  
        if (j < n-1) {
           Serial.print(", 0x");
        } else {
           Serial.print(",");       
        }
      }
    }
    Serial.println();
  }
}



void setup() {  
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
  while (!Serial || millis() < 10000) {}
  Nicla_Vision.begin();
  
  reset_reason_t resetReason = STM32H747::getResetReason();
  Serial.println(getString(resetReason));
}


void loop() {  

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Regular power for 10 seconds");
  delay(10000);
  Serial.println("Reading the PMIC bootloader area : ");
  
  readI2C(PMIC_ADDRESS, 10, 16);   // 10 rows of 16 bytes



/*
  uint8_t subAddress = 0x00;
  char response = 0xFF;
  Wire1.beginTransmission(PMIC_ADDRESS);
  Wire1.write(subAddress);
  Wire1.endTransmission(false);
  Wire1.requestFrom(PMIC_ADDRESS, 1);
  while(!Wire1.available()) {}
  uint8_t ret= Wire1.read();
  Serial.println(ret, HEX);

*/

  delay(5000);

  
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.println("Low power for 10 seconds");
  bool myLow = Nicla_Vision.enterLowPower();
  Serial.print("Nicla_Vision.enterLowPower();  :");
  Serial.println(myLow);
  delay(10000);
  
  Serial.println("How do you exit low power?");
}
