/*
 * 
 * Must use portenta with Vision Shield Camera and Waveform 128x128 grayscale OLED 
 * Until then needs the 2 main library folders Portenta_Camera and Himax_HM01B0
 * 
 * 
 *
 * Purchase here https://www.waveshare.com/1.5inch-OLED-Module.htm about $29 USD
 *
 *  FOR the GRAYSCALE Waveshare OLED
 *   black GND 
 *   red 3v3     
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




void setup()   {                
  Serial.begin(115200);
  //while (! Serial) delay(100);  // blocking, messes up beginners
  Serial.println("SSD1327 OLED test");
  
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

}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Rocksetta D100 Lidar");
  for (int x=0;  x<=10; x++){
     display.drawPixel(random(128),random(128),random(255));
  }

  display.display();
  delay(100);

}


