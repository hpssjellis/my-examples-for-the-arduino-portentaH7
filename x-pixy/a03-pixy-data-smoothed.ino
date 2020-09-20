//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with 
// Pixy and Arduino.  This program simply prints the detected object blocks 
// (including color codes) through the serial console.  It uses the Arduino's 
// ICSP SPI port.  For more information go here:
//
// https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:hooking_up_pixy_to_a_microcontroller_-28like_an_arduino-29
//
  
#include <Pixy2.h>

// This is the main Pixy object 
Pixy2 pixy;
int myLoopDataPoints = 0;
int myNumberDataPoints = 20;
int myDelaySpeed = 100;
int myPlusMinus = 5;
int myX, myY, myOldX, myOldY;
bool myShowZeros = true;

void setup()
{
  Serial.begin(115200);
  pixy.init();
  delay(2000); // wait for serial to get going
  Serial.println("Pixy2 data colection, only interested in main block #0 ");
  Serial.println("Results printed as an array for loading into a Machine Learning model");
}

void loop()
{ 
 // int i; 
  pixy.ccc.getBlocks();
  
  // are there any blocks!
  if (pixy.ccc.numBlocks){   // main if
    if (myShowZeros){
    myLoopDataPoints ++;
    }
    // pixy.ccc.blocks[0].print();  

    int myX = pixy.ccc.blocks[0].m_x;
    int myY = pixy.ccc.blocks[0].m_y;
    if ( myX < myOldX + myPlusMinus && myX > myOldX - myPlusMinus      && myY < myOldY + myPlusMinus && myY > myOldY - myPlusMinus ){
        if (myShowZeros){
           Serial.print("[0,0],"); 
           if (myLoopDataPoints == 2){
               myShowZeros = false;   // until movement
            }       
        } 

    } else {           
       Serial.print("["+String(pixy.ccc.blocks[0].m_x)+","+String(pixy.ccc.blocks[0].m_y)+"],"); 
       myShowZeros = true;
    }
    if (myLoopDataPoints % myNumberDataPoints == 0){  
       Serial.println();
       myLoopDataPoints = 0;
    } 
    myOldX = myX;
    myOldY = myY;

  } // end main if
  delay(myDelaySpeed); // slow it down
}
