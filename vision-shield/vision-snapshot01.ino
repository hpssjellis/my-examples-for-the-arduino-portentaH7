
#include "camera.h"
//#include "himax.h"

#include <ThreadDebug.h>

USBSerial              SerialUSB1(false, "DebugPort");
UsbDebugCommInterface  debugComm(&SerialUSB1);
ThreadDebug            threadDebug(&debugComm, DEBUG_NO_BREAK_IN_SETUP);


CameraClass cam;

void setup() {
  pinMode(LEDB, OUTPUT);
  
  digitalWrite(LEDB,LOW);
  Serial.begin(115200);
  
  cam.begin(324, 244);
  cam.start(5000);  
 
  //cam.testPattern(true); 
  digitalWrite(LEDB,HIGH);
}

void loop() {
  digitalWrite(LEDB,HIGH);
  delay(2000);  
  
  uint8_t* myImage = cam.grab();
  Serial.write(myImage, 324 * 244);
  
  digitalWrite(LEDB,LOW);
  delay(2000);  

}
