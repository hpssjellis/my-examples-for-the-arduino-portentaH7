/*  
 *   my11-servo.ino
 *
 * MUST HAVE A 6 VOLT EXTERNAL BATTERY
 * Note: REMEMBER 2 WIRES GO TO THE SERVO GROUND (Battery Neg and Board GND)
 * Servos run from 0 to 180 degrees, test 20 - 160 first
 * 
 * servo red to 6V battery positive
 * servo ground (brown or black) to 6V battery negative
 * servo ground (brown or black) to board GND
 * servo controller (orange or the other color) to board PWM pin A4   
 * 
 * Note For PWM pins check your boards Pinout diagram.
 * 
 *  By Jeremy Ellis twitter @rocksetta
 *  Webpage http://rocksetta.com
 *  Arduino High School Robotics Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 * 
 *  Update Aug 7th, 2020
 * 
 */

#include <Arduino.h>  // only needed for https://platformio.org/
#include <Servo.h>

Servo myServo4;

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  myServo4.attach(5);   // D5 should do PWM

}

void loop() {
 
  digitalWrite(LED_BUILTIN, LOW); // Portenta onboard LED on    
    
  myServo4.write(20);           // servo at 20 degrees try 0
  delay(2000);
    
  myServo4.write(160);         // servo at 160 degrees try 180
  delay(2000);

  myServo4.write(90);          // servo at 90 degrees
  delay(2000);   
    
    
  for (int myLoop = 20; myLoop <= 160; myLoop++){
    myServo4.write(myLoop);
    delay(25);  // short delay 25 ms
  }

  digitalWrite(LED_BUILTIN, HIGH);     // Portenta onboard LED off
  delay(5000);            // 5 second delay

}
