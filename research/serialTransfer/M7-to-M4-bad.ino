
#ifdef CORE_CM7   // Start M7 programming
 
#include "RPC_internal.h"  // comes with the mbed board installation

#include "SerialTransfer.h"


SerialTransfer myTransfer;

struct STRUCT {
  char z;
  float y;
} testStruct;

char arr[] = "hello";




void setup() {
   bootM4(); 
   Serial.begin(115200);
   RPC1.begin(); 
  Serial1.begin(115200);
  myTransfer.begin(Serial1);

  testStruct.z = '$';
  testStruct.y = 4.5;
}

void loop() {
  
   Serial.println("Hello from M7 regular Serial");
   while (RPC1.available()) {
      Serial.write(RPC1.read()); 
   }  
   delay(3000);

  uint16_t sendSize = 0;

  sendSize = myTransfer.txObj(testStruct, sendSize);

  sendSize = myTransfer.txObj(arr, sendSize);

  myTransfer.sendData(sendSize);
  delay(500);

   
}

#endif              // End all M7 core programming

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CORE_CM4    // Start M4 programming

#include "RPC_internal.h"  // comes with the mbed board installation

#define Serial RPC1  // So the M4 regular serial prints to RPC

#include "SerialTransfer.h"

SerialTransfer myTransfer;

struct STRUCT {
  char z;
  float y;
} testStruct;

char arr[6];

  
void setup() {
   Serial.begin();   // RPC begin does not take an integer
   Serial1.begin(115200);
   myTransfer.begin(Serial1);
}

void loop() {
  Serial.println("Hello from M4 using regular serial piped through RPC"); 
  delay(40);
  if(myTransfer.available())
  {
    // use this variable to keep track of how many
    // bytes we've processed from the receive buffer
    uint16_t recSize = 0;

    recSize = myTransfer.rxObj(testStruct, recSize);
    delay(40);
    Serial.print(testStruct.z);
    delay(40);
    Serial.print(testStruct.y);
    delay(40);
    Serial.print(" | ");
    delay(40);

    recSize = myTransfer.rxObj(arr, recSize);
    Serial.println(arr);
    delay(40);
  }
  delay(5000);
}

#endif            // End all M4 core programming
