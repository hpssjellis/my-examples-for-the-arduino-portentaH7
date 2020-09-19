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
int myLoop = 0;

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
  int i; 
  myLoop ++;
  pixy.ccc.getBlocks();
  
  // are there any blocks!
  if (pixy.ccc.numBlocks){
     // pixy.ccc.blocks[0].print();     
      Serial.print("["+String(pixy.ccc.blocks[0].m_x)+","+String(pixy.ccc.blocks[0].m_y)+"],");  
      if (myLoop % 10 == 0){  
         Serial.println();
      }
  } 

  delay(200); // slow it down
}
