/*
 * 
 * Must use portenta with Vision camerera and Grove OLED 
 * Should be implemented with MBED version greater than 1.4.2
 * Until then needs the 2 main library folders Portenta_Camera and Himax_HM01B0
 * 
 * 
 *
 * Purchase here https://www.waveshare.com/1.5inch-OLED-Module.htm about $29 USD
 *
 * Note u8g2 is an arduino search caplble library, easy to install
 *
 *  using 128 x 64 seeeduino OLED
 *  black GND 
 *  red 3v3      so do not need the protective resistors below
 *  //white SDA    D11 // on portenta
 *  //yellow SCL   D12 // on portenta
 *  
 *  FOR the GRAYSCALE Waveshare OLED
 *   blue  DIN (mosi) D8
 *   yellow (sck) D9 
 *   orange (cs) D7
 *   green (dc)  D6
 *   white (reset) not needed but D14 if you did
 *
 * another reference here 
 * https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
 *
 */

 
 
#include <Arduino.h>  // only needed for https://platformio.org/

#include <Adafruit_SSD1327.h>

// Used for software SPI
#define OLED_CLK D9  //yellow wire
#define OLED_MOSI D8 // blue wire 

// Used for software or hardware SPI
#define OLED_CS D7  // orange wire
#define OLED_DC D6   // green wire 

// Used for I2C or SPI
#define OLED_RESET -1

// hardware SPI
Adafruit_SSD1327 display(128, 128, &SPI, OLED_DC, OLED_RESET, OLED_CS);




#include "camera.h"

CameraClass cam;
uint8_t frame_buffer[320*240];

void setup() {
  //Serial.begin(921600);  
  Serial.begin(115200);  

  // Init the cam QVGA, 30FPS
  cam.begin(CAMERA_R320x240, 30);

 // display.clearDisplay();                 // clear the internal memory


    if ( ! display.begin(0x3D) ) {
     Serial.println("Unable to initialize OLED");
     while (1) yield();
  }    
    display.setTextSize(1);
    display.setTextColor(SSD1327_WHITE);

    display.setRotation(0);
    display.setCursor(0,0);

    display.drawRect(5,5,120,120, SSD1327_WHITE );

    display.setCursor(10,10);
    display.println("Rocksetta");
    display.display();
        
    delay(100); 
    
}

void loop() {
  // put your main code here, to run repeatedly:
  
   //  display.drawPixel(random(128), random(128), random(512)); 
  // Wait until the receiver acknowledges
  // that they are ready to receive new data
  //while(Serial.read() != 1){};
  
  // Grab frame and write to serial
  if (cam.grab(frame_buffer) == 0) {
     //Serial.write(frame_buffer, 320*240);     


    for (int x=0; x < 320; x++){     // FRAME_BUFFER_COLS = 320
       for (int y=0; y < 240; y++){       //FRAME_BUFFER_ROWS = 240

          uint16_t myGRAY = frame_buffer[(y * 320) + x] * 2;  
          int xMap = map(x, 0, 320, 0, 127);
          int yMap = map(y, 0, 240, 0, 127);
          display.drawPixel(xMap, yMap, random(512)); 
       //   display.drawPixel(xMap, yMap, myGRAY);   // grayscale 0-255, 128x128  //128 x 64
         // delay(1);
      } 
    }     
  }
  display.display();
        
  delay(100); 
}



/*


      for (int x=0; x < FRAME_BUFFER_COLS; x++){     // FRAME_BUFFER_COLS = 320
        for (int y=0; y < FRAME_BUFFER_ROWS; y++){       //FRAME_BUFFER_ROWS = 240
          //frame_buffer[FRAME_BUFFER_COLS * FRAME_BUFFER_ROWS]
          
          uint8_t myGRAY = frame_buffer[(y * (int)FRAME_BUFFER_COLS) + x];  
         // if (myGRAY > 100){  // if brightish then put pixel on OLED 0 to 255
          //  u8g2.SetDrawColor(myGRAY)
            int xMap = map(x, 0, 320, 0, 127);
            int yMap = map(y, 0, 240, 0, 127);
            display.drawPixel(xMap, yMap, myGRAY);   // grayscale 0-255, 128x128  //128 x 64
          //  display.drawPixel(xMap, yMap, (int)myGRAY*255);   // grayscale 0-255, 128x128  //128 x 64
           // display.drawPixel(x, y, (int)myGRAY);   // grayscale 0-255, 128x128  //128 x 64
           // display.drawPixel(xMap, yMap, SSD1327_WHITE);   // grayscale 0-255, 128x128  //128 x 64
            
           // display.drawRect(xMap, yMap, xMap+1, yMap+1, SSD1327_WHITE );
         //}
      } 
   }

   // display.display();

    //u8g2.setDrawColor(2);  // XOR OLED  
    display.drawRect(x1Map, y1Map, x2Map, y2Map, SSD1327_WHITE );

   // u8g2.setDrawColor(1);               // regular OLED
  //  u8g2.drawStr(20,10,"Rocksetta");    // write something to the internal memory
    display.setCursor(0,0);
    display.println("Rocksetta");


    */
