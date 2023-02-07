
#include <Wire.h>

byte devAddr = 0x08; //standard I2C device address
  
bool showCount = false;  // true to show line numbers
bool myGoodI2C = false;


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


void myI2cScanner() {
  byte error, address;
  int nDevices;

  Serial.println("I2C Scanner. Note: The address shown is not needed");
  Serial.println("Just a connection is needed");
  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    Serial.print(address);
    Serial.print(", ");
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (address %20 == 0){
      Serial.println();  // every 20 addresses do a println
    }
    if (error == 0)
    {
      Serial.println();
      if (!myGoodI2C){      // if a device hasn't been found
         myGoodI2C = true;  // tell the code an address has been found
         devAddr = address;  // set it to the first found address  // probably 0x08 
      }
      Serial.print("I2C device found at address 0x");

      if (address<16){ 
        Serial.print("0"); 
      }
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) {
      Serial.print("Unknown error at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0){
    Serial.println("No I2C devices found\n");
  }else{
    Serial.println("done\n");
  }
  Serial.println("Press 'Y' for yes and click SEND for PMIC change"); 
  Serial.println("Any other key to show the PMIC data"); 
  Serial.println("Remember to give power to the receiving I2C Portenta"); 
      
  delay(5000);
}





//void writeI2C(byte devAddr, uint16_t regAddr[], byte regVal[], int n)
void writeI2cRocksetta(byte devAddr2, uint16_t myReg, byte myVal)
{
  Serial.println();
  //for (int i = 0; i < n; i++){
    Wire.beginTransmission(devAddr2);
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
    Wire.beginTransmission(devAddr2);
    nWritten = 0;
    nWritten += Wire.write(myReg);
    error = Wire.endTransmission(sendRestart);
    int nRead = Wire.requestFrom(devAddr2, one);
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
      Wire.beginTransmission(devAddr3);
      int nWritten = 0;
      nWritten += Wire.write(uint16_t(i*16+j));
      int error = Wire.endTransmission(sendRestart);
      if (error != 0){
        Serial.print("Transmission error, code = ");
        Serial.println(error);
      }
      int nRead = Wire.requestFrom(devAddr3, one);
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
  char myInChar = 'N';
  Wire.begin(); //Initialize the I2C bus
  Serial.begin(115200); //Initialize the serial monitor
  while (!Serial){}
  Wire.setTimeout(1000);

  while(!Serial.available() ) {  // continue scanning until a key is send
      myI2cScanner();
  } 
  while(Serial.available()) {  // key has been sent
     char c = Serial.read();
     if (c == 'Y' || c == 'y') {
        myInChar = 'Y';   // the last char is 'n' so this captures the 'Y'
     }
     Serial.print(c);     // echo character to terminal 
     Serial.print(myInChar); // echo character to terminal 
  }     
   Serial.println();
   Serial.print("Sent from Monitor: ");
   Serial.println(myInChar); // echo character to terminal 

  if (myGoodI2C){
  
  Serial.println("PMIC Data as on the Portenta"); 
  Serial.println();  
  readI2C(devAddr, 10, 16);   // 10 rows of 16 bytes

  if (myInChar == 'Y'){
       Serial.println("You typed Y or y so"); 
       Serial.println("The PMIC registers will be changed"); 
       Serial.println(); 

    
       //---------------------------------- Start IMPORTANT -----------------------------------------------//
       // manually change PMIC registers 
       // writeI2cRocksetta(devAddr, RegisterHex, ValueHex);
       
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
    
    //---------------------------------- End IMPORTANT -----------------------------------------------//
    
       readI2C(devAddr, 10, 16);   // 10 rows of 16 bytes
       Serial.println("Done, Hopefully the Orange LED has turned off.");
       Serial.println("Now try to reset the Bootloader");
  }
    } else {
      Serial.println("Since no I2C device(s) were found we exited the program. ");
      Serial.println("Check your wiring and make sure both Portenta's have power.");
      Serial.println("GND to GND, D11 (SDA)on Portenta, to SDA1 on breakout board broken Portenta. ");
      Serial.println("GND to GND, D12 (SCL)on Portenta, to SCL1 on breakout board broken Portenta. ");
      Serial.println();
    }
  }


void loop() {
    
}
