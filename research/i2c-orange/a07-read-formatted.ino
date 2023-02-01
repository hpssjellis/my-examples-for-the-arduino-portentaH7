#include <Wire.h>

bool showCount = false;  // true to show line numbers

const byte one = 0x01;
const byte zero = 0x00;
const byte sendRestart = false;


void readI2C(byte devAddr, int m, int n){
  Serial.println();
  Serial.print("Starting at address: ");
  Serial.println(devAddr, HEX);
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
      Wire.beginTransmission(devAddr);
      int nWritten = 0;
      nWritten += Wire.write(uint16_t(i*16+j));
      int error = Wire.endTransmission(sendRestart);
      if (error != 0){
        Serial.print("Transmission error, code = ");
        Serial.println(error);
      }
      int nRead = Wire.requestFrom(devAddr, one);
      if (nRead == 1){
        byte valRead = Wire.read();
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
  Wire.begin(); //Initialize the I2C bus
  Serial.begin(115200); //Initialize the serial monitor
  while (!Serial){}
  Wire.setTimeout(1000);
  byte devAddr = 0x08;
  readI2C(devAddr, 10, 16);   // 10 rows of 16 bytes
}

void loop() {
 
}
