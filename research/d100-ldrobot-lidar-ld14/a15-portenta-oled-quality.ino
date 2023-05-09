/*
 * RoboPeak RPLIDAR Arduino Example
 * This example shows the easy and common way to fetch data from an RPLIDAR
 * 
 * You may freely add your application code based on this template
 *
 * USAGE:
 * ---------------------------------
 * 1. Download this sketch code to your Arduino board
 * 2. Connect the RPLIDAR's serial port (RX/TX/GND) to your Arduino board (Pin 0 and Pin1)
 * 3. Connect the RPLIDAR's motor ctrl pin to the Arduino board pin 3 
 */
 
/* 
 * Copyright (c) 2014, RoboPeak 
 * All rights reserved.
 * RoboPeak.com
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 LDrobot https://www.ldrobot.com/download/en/124
 datasheet at
 https://github.com/ldrobotSensorTeam/DeveloperKit/blob/master/D100Kit.md
 
 D100 red wire to +5V
 Yellow wire to GND
 Green wire to RX1 D13 on Portenta
 black wire strangely to D3 as it is the motor PWM control.
 
 
 
 */
 
// This sketch code is based on the RPLIDAR driver library provided by RoboPeak
#include <RPLidar.h>

// You need to create an driver instance 
RPLidar lidar;

#define RPLIDAR_MOTOR D5 // The PWM pin for control the speed of RPLIDAR's motor.
                        // This pin should connected with the RPLIDAR's MOTOCTRL signal 





#include <Adafruit_SSD1327.h>


// Used for software SPI
#define OLED_CLK D9
#define OLED_MOSI D8

// Used for software or hardware SPI
#define OLED_CS D7
#define OLED_DC D6

// Used for I2C or SPI
#define OLED_RESET -1


// software SPI
//Adafruit_SSD1305 display(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
// hardware SPI
Adafruit_SSD1327 display(128, 128, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// I2C
//Adafruit_SSD1327 display(128, 128, &Wire, OLED_RESET, 1000000);


unsigned long myDelay = 10000;   // non-block delay in milliseconds
unsigned long myStart;

float  myStoreAngle;
                        
void setup() {

  Serial.begin(115200);

  myStart = millis();   // set delay

  // bind the RPLIDAR driver to the arduino hardware serial1
  lidar.begin(Serial1);

  //while (! Serial) delay(100);  // blocking, messes up beginners
  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);
  //delay(10000); //to conect serial monitor

  //Serial.println("SSD1327 OLED test");
  
  if ( ! display.begin(0x3D) ) {
     Serial.println("Unable to initialize OLED");
     while (1) yield();
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextWrap(false);
  display.setTextColor(SSD1327_WHITE);
  display.setCursor(0,0);
  display.display();

/*

  Serial.println("Stopping Lidar");
  analogWrite(RPLIDAR_MOTOR, 0);  // 255 is max
  delay(5000);

  Serial.println("medium Lidar");
  analogWrite(RPLIDAR_MOTOR, 125);  // 255 is max
  delay(5000);

  Serial.println("fast Lidar");
  analogWrite(RPLIDAR_MOTOR, 255);  // 255 is max

*/

rplidar_response_device_health_t myLidarHealth;  //    _u8   status;   _u16  error_code;

lidar.getHealth(myLidarHealth,2000);
//Serial.println(myLidarHealth);


rplidar_response_device_info_t   myLidarInfo;  
/*
    _u8   model;
    _u16  firmware_version;
    _u8   hardware_version;
    _u8   serialnum[16];
*/

lidar.getDeviceInfo(myLidarInfo, 2000);


}







void loop() {
    if ( (millis() - myStart ) >= myDelay) {       
       myStart = millis();      //  reset the delay time
       display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Rocksetta D100 Lidar");
    }










  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance; // distance value in mm unit
    float angle    = lidar.getCurrentPoint().angle;    // angle value in degree
    bool  startBit = lidar.getCurrentPoint().startBit; // whether this point is belong to a new scan
    byte  quality  = lidar.getCurrentPoint().quality;  // quality of the current measurement



/*


  if (angle > 360 ) {angle = angle - 360;}

  if (startBit) {

      myStoreAngle = angle;  
     Serial.println("----------------------- starting angle: " + String(angle, 3) + " degrees -------------------------");  
  } else {

    myStoreAngle = angle + myStoreAngle;
  }

    if (myStoreAngle > 360 ) {myStoreAngle = myStoreAngle - 360;}



 

  Serial.print("d: " + String(distance, 3) + " mm, raw angle: " + String(angle, 3) + " degrees, angle: " + String(myStoreAngle, 3) + " degrees, quality: " + String(quality, 3) +"  " );
*/

//myStoreAngle = angle;

  if (quality > 49.0) {    // random quality amount
    // any angle > 20 becomes the new base angle.
    if (angle > 30 ) {
        myStoreAngle = angle;
      } else {
        myStoreAngle = myStoreAngle + angle;    
      }
  



  /*
      byte   myShow = map((int)quality, 0, 2000, 0, 255);
        if (myShow > 255) {myShow = 255;}
        if (myShow < 50) {myShow = 50;}

        */
      //byte myShow = quality;

  /*
      if (myShow > 255) {myShow = 255;}
      if (myShow < 127) {myShow = 127;}
  */


      // ignore3 the above
      byte myShow = 255;


      ///if (quality < 55) {myShow = 127;} else {myShow = 255;}



      //int myX = (int) (distance * cos(myStoreAngle * 3.1416 / 180.0));
      //int myY = (int) (distance * sin(myStoreAngle * 3.1416 / 180.0));



    // int myX = (int) (distance * cos(angle * 3.1416 / 180.0));
    //int myY = (int) (distance * sin(angle * 3.1416 / 180.0));

    // flip sin cos
    // int myX = (int) (distance * sin(angle * 3.1416 / 180.0));
    // int myY = (int) (distance * cos(angle * 3.1416 / 180.0));

      int myX = (int) (distance * sin(myStoreAngle * M_PI / 180.0));
      int myY = (int) (distance * cos(myStoreAngle * M_PI / 180.0));



    //if (angle > 90 && angle < 180){ myX = -1 * myX; myY = -1 * myY; }
    //if (angle > 270 && angle < 360){ myX = -1 * myX; myY = -1 * myY; }

  /*
    // flip all values
    int myTemp;
    //if (angle > 90 && angle < 360){ 
      myTemp = myX;
      myX = myY;
      myY =  myTemp;
    //}

    */

    // now check the sign of the values

  // if (angle > 90 && angle <= 180){ myX = -1 * myX; myY = -1 * myY; }  

  // if (angle > 270 && angle <= 360){ myX = -1 * myX; myY = -1 * myY; }  




      int   myX1Map = map((int)myX, -15000, 15000, 0, 127);  // not sure what to map from possibly 8000 mm = 8 m
    // if (myX1Map < -64){myX1Map = -64;}
      if (myX1Map < 0){myX1Map = 0;}
      if (myX1Map > 127){myX1Map = 127;}

      int   myY1Map = map((int)myY, -15000, 15000, 0, 127);
      //if (myY1Map < -64){myY1Map = 0;}
      if (myY1Map < 0){myY1Map = 0;}
      if (myY1Map > 127){myY1Map = 127;}

      int   myMidX = 0;
      int   myMidY = 0;



  /*
    Serial.print(" X: ");  
    Serial.print(myX1Map); 
    Serial.print(",  y: ");  
    Serial.print(myY1Map); 
    Serial.println();  
    */

    // csv formated
    Serial.print(String(myStoreAngle,1)); 
    Serial.print(", ");  
    Serial.print(String(distance,1)); 
    Serial.println();  


  // for the OLED display
    display.drawPixel(myX1Map + myMidX, myY1Map + myMidY, myShow);
    display.display();
  }


  //} // end quality   
  } else {
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
    
    // try to detect RPLIDAR... 
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       // detected...
       lidar.startScan();
       
       // start motor rotating at max allowed speed
       analogWrite(RPLIDAR_MOTOR, 255);  // 255 is max
       delay(1000);
    }
  }
}
