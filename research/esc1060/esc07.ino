/*
 * this doesn't seem to be working
#if  defined(XIAO_ESP32S3) ||  defined(XIAO_ESP32C3)  //if esp32s3 or esp32C3
  #include <ESP32Servo.h>
#else // all other Arduino boards
//  #include <Servo.h>
#endif
*/


//#include <ESP32Servo.h> // esp32 
#include <Servo.h>   // most arduinos

Servo myServoPin01;
int servoPin = 2;  // D2

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);  //high off onboard LED

  myServoPin01.attach(servoPin, 1000, 2000); 
  delay(10000);
  digitalWrite(LED_BUILTIN, HIGH);  //high off onboard LED

  Serial.println("Time to control an ESC Motor driver"); 
}

void loop() {

  myServoPin01.writeMicroseconds(0);    // not realy needed
  delay(500);  
  myServoPin01.writeMicroseconds(1500);  // middle not really needed
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  myServoPin01.writeMicroseconds(1600);  // slow forward
  Serial.println("Slow forward");
  delay(1000);

  digitalWrite(LED_BUILTIN, HIGH);  //high off onboard LED
  myServoPin01.writeMicroseconds(0);
  delay(500);
  myServoPin01.writeMicroseconds(1500);  // middle
  delay(1000);
  myServoPin01.writeMicroseconds(1400);  // slow reverse
  
  Serial.println("Slow backward");
  delay(1000);

  
  Serial.println("Wait 5 seconds");
  delay(5000);

}
