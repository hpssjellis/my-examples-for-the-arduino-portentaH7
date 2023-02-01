#include <Wire.h>

const int nTJaekel = 160;
byte regValTJaekel[nTJaekel] = 
 {0x7c ,0x00 ,0x11 ,0x00 ,0x00 ,0x00 ,0x88 ,0x00 ,0x00 ,0x07 ,0x00 ,0x04 ,0x07 ,0x04 ,0x00 ,0x03
 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x07 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00
 ,0x00 ,0x05 ,0x00 ,0x00 ,0x00 ,0x3f ,0x00 ,0x00 ,0x08 ,0x1f ,0x04 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00
 ,0x00 ,0x00 ,0x06 ,0x06 ,0x06 ,0x0f ,0x00 ,0x00 ,0x0a ,0x0a ,0x0a ,0x0f ,0x00 ,0x00 ,0x0d ,0x0d
 ,0x0d ,0x03 ,0x01 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x05 ,0x03 ,0x00 ,0x00
 ,0x0f ,0x00 ,0x09 ,0x0f ,0x00 ,0x00 ,0x00 ,0x00 ,0x21 ,0x80 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x01
 ,0x02 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x0c ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00
 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00
 ,0x68 ,0x00 ,0xff ,0x00 ,0xac ,0x00 ,0x20 ,0x03 ,0x04 ,0x02 ,0x00 ,0x00 ,0x00 ,0x40 ,0x05 ,0x6b
 ,0x00 ,0x00 ,0x00 ,0x00 ,0xa0 ,0x06 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x80 ,0x00 ,0x20 ,0x00};

uint16_t regAddrTJaekel[nTJaekel] = {
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
  10,11,12,13,14,15,16,17,18,19,
  20,21,22,23,24,25,26,27,28,29,
  30,31,32,33,34,35,36,37,38,39,
  40,41,42,43,44,45,46,47,48,49,
  50,51,52,53,54,55,56,57,58,59,
  60,61,62,63,64,65,66,67,68,69,
  70,71,72,73,74,75,76,77,78,79,
  80,81,82,83,84,85,86,87,88,89,
  90,91,92,93,94,95,96,97,98,99,
  100,101,102,103,104,105,106,107,108,109,
  110,111,112,113,114,115,116,117,118,119,
  120,121,122,123,124,125,126,127,128,129,
  130,131,132,133,134,135,136,137,138,139,
  140,141,142,143,144,145,146,147,148,149,
  150,151,152,153,154,155,156,157,158,159
};




bool showCount = false;  // true to show line numbers



const byte one = 0x01;
const byte zero = 0x00;
const byte sendRestart = false;


/* slave address PMIC */
#define PMIC_I2C_SLAVE_ADDR  (0x08 << 1)



/*
  //check if we can read the PMIC ChipID (should be 0x7C)
  uint8_t data[2];
  int err;



  err = I2CUser_MemReadEx(PMIC_I2C_SLAVE_ADDR, 0, data, 1);
  if (err)
    return err;       //ERROR

  if (data[0] != 0x7C)
  {
    print_log(UART_OUT, "*E: external PMIC not found\r\n");
    return 0;       //ERROR - incorrect ChipID
  }


  */








//void writeI2C(byte devAddr, uint16_t regAddr[], byte regVal[], int n)
void writeI2cRocksetta(byte devAddr, uint16_t myReg, byte myVal)
{
  Serial.println();
  //for (int i = 0; i < n; i++){
    Wire.beginTransmission(devAddr);
    int nWritten = 0;
    nWritten += Wire.write(myReg);
    nWritten += Wire.write(myVal);
    int error = Wire.endTransmission();
    if (error != 0)
    {
      Serial.print("Transmission error, code = ");
      Serial.println(error);
    } else {
      Serial.print("Wrote ");
      Serial.print(nWritten);
    }
    Wire.beginTransmission(devAddr);
    nWritten = 0;
    nWritten += Wire.write(myReg);
    error = Wire.endTransmission(sendRestart);
    int nRead = Wire.requestFrom(devAddr, one);
    if (nRead == 1)
    {
      byte valRead = Wire.read();
      Serial.print(" bytes to register ");
      Serial.print(myReg, HEX);
      Serial.print(": wrote ");
      Serial.print(myVal, HEX);
      Serial.print(", read ");
      if (valRead != myVal) {
        Serial.print(valRead, HEX);
        Serial.println(" *** ERROR ***");
      } else {
        Serial.println(valRead, HEX);
      }
    } else {
      Serial.print("Error in reception, bytes received = ");
      Serial.println(nRead);
    }
  //}
  
}




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

  
  Serial.println("PMIC unchanged but broken"); 
  Serial.println();  
  readI2C(devAddr, 10, 16);   // 10 rows of 16 bytes

  Serial.println("One PMIC register changed"); 
  Serial.println(); 
  //writeI2C(devAddr, regAddrTJaekel, regValTJaekel, nTJaekel);
  writeI2cRocksetta(devAddr, 0x4f, 0x0);// LDO2 to 1.8V //initialize the PMIC registers:
  writeI2cRocksetta(devAddr, 0x4c, 0xf);// LDO1 to 1.0V
  writeI2cRocksetta(devAddr, 0x4d, 0xf);
  writeI2cRocksetta(devAddr, 0x52, 0x9);// LDO3 to 1.2V
  writeI2cRocksetta(devAddr, 0x53, 0xf);
  osDelay(10);
  writeI2cRocksetta(devAddr, 0x9c, (1 << 7) );//0x80 //charger LED off - duty cycle
  writeI2cRocksetta(devAddr, 0x9e, (1 << 5) );//0x20 // Disable charger led
  osDelay(10);
  writeI2cRocksetta(devAddr, 0x42, 2);    // SW3: set 2A as current limit // Helps keeping the rail up at wifi startup
  osDelay(10);
  writeI2cRocksetta(devAddr, 0x94, (20 << 3) );//0xA0 // Change VBUS INPUT CURRENT LIMIT to 1.5A
  writeI2cRocksetta(devAddr, 0x3b, 0xf);// SW2 to 3.3V (SW2_VOLT)
  
  /* ATTENTION: if I write this register - the I2C is dead, read ChipID does not work anymore
   * write this register as the last one!
   */
  writeI2cRocksetta(devAddr, 0x35, 0xf);// SW1 to 3.0V (SW1_VOLT)

  readI2C(devAddr, 10, 16);   // 10 rows of 16 bytes
 
}

void loop() {
    
}
