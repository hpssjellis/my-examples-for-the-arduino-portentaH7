#include <Wire.h>

const byte one = 0x01;
const byte zero = 0x00;
const byte sendRestart = false;


void readI2C(byte devAddr, int m, int n)
{
  Serial.println();
  Serial.println("Starting at address: ");
  Serial.println(devAddr);
  Serial.println();
  Serial.println("#  | HEX");
  Serial.print("0");  // starting zero
  for (int i = 0; i < m; i++)
  {
    Serial.print(byte(i*16), HEX);
    Serial.print(" | 0x");
    for (int j = 0; j < n; j++)
    {
      Wire.beginTransmission(devAddr);
      int nWritten = 0;
      nWritten += Wire.write(uint16_t(i*16+j));
      int error = Wire.endTransmission(sendRestart);
      if (error != 0)
      {
        Serial.print("Transmission error, code = ");
        Serial.println(error);
      }
      int nRead = Wire.requestFrom(devAddr, one);
      if (nRead == 1)
      {
        byte valRead = Wire.read();
        if (valRead == 0){Serial.print("0");} // add an extra zero
        if (valRead <= 15 && valRead >= 1 ) {Serial.print("0");} // extra zero
        Serial.print(valRead, HEX);
        Serial.print(", 0x");
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
  readI2C(devAddr, 16, 16);
}

void loop() {
 
}
