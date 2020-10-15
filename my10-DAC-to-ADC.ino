/* 
 *  my10-DAC-to-ADC.ino
 *  
 * DAC to ADC for the PortentaH7
 * Digital to Analog Converter (DAC) and  Analog to Digital Converter (ADC)
 * DAC converts a digital signal into analog signal.
 * ADC converts an Analog signal into a digital signal
 *
 * Connect Pin 3V3 to AREF
 * Connect Pin A0 (DAC) to A6
 * Connect Pin A0 (DAC) to Pin 6 (D6)
 *   
 *   Note: Only having luck reading DAC on A6 and D6
 *   
 *
 *  Update August 3rd, 2020
 *
 *  analogWriteResolution(10) assumed default for DAC 0 - 1023 --> 0 to 3.3 Volts
 *  
 *  By Jeremy Ellis twitter @rocksetta
 *  Webpage http://rocksetta.com
 *  Arduino High School Robotics Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 *  
 */


#include <Arduino.h>  // only needed for https://platformio.org/

void setup() {
  
  analogWriteResolution(10);
  randomSeed(A1);  // grab a random Analog reading 
  Serial.begin(115200);
  pinMode(DAC, OUTPUT);
  pinMode(6, INPUT_PULLDOWN);  // set pin D6
  // pinMode(A6, INPUT); You don't have to declare A6 for Analog input, that is the default

}

void loop() {
  
  myDac(0);
  myDac(800); 
  int myRandomNumber  = rand() % 1024;  // a random number between 0 and 1023
  myDac(myRandomNumber);
  Serial.println("----------------------");
  delay(1000); // wait a few seconds

}


void myDac(int myDacSet){
  
  analogWrite(DAC, myDacSet);
  Serial.print("DAC on A0 set to: ");
  Serial.print(myDacSet);

  Serial.print(", A6: ");
  Serial.print(analogRead(A6));

  Serial.print(", Pin(D6): ");
  Serial.println(digitalRead(6));
  
}
