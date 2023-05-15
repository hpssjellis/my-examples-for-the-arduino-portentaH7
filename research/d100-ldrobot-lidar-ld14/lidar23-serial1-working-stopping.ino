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
 *   red 3v3  on Portenta must be 5V pin on ESP32   
 *   blue  DIN (mosi) D8 on Portenta  // D10 on XIAO
 *   yellow (sck) D9  on Portenta     // D8 on XIAO
 *   orange (cs) D7    // used by lidar lets try D1
 *   green (dc)  D6    // used by lidar lets try D0
 *   white (reset) not needed but D14 if you did
 *
 * another reference here 
 * https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
 *

*/




#include <Adafruit_SSD1327.h>

// Used for software SPI
#define OLED_CLK D9   // D9 portenta,  D8 XIAO    // on XIAO yellow wire
#define OLED_MOSI D8  // D8 Portenta,   D10 XIAO  // on XIAO blue wire

// Used for software or hardware SPI
#define OLED_CS D7   // orange (cs) D7 Portenta,   try D0 on XIAO
#define OLED_DC D6   // green D6 Portenta,  try D1 on XIAO 


// Used for I2C or SPI
#define OLED_RESET -1

// software SPI
//Adafruit_SSD1305 display(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
// hardware SPI
Adafruit_SSD1327 display(128, 128, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// I2C
//Adafruit_SSD1327 display(128, 128, &Wire, OLED_RESET, 1000000);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2



unsigned long myDelay = 2000;   // non-block delay in milliseconds
unsigned long myStart;


// Zoom can be about 10 m = 10000 mm. Device should do about 8 m = 8000 mm. I like to zoom in to 500
#define MY_ZOOM_NEG_X  -500
#define MY_ZOOM_POS_X  500

#define MY_ZOOM_NEG_Y  -500
#define MY_ZOOM_POS_Y  500




#ifndef LD06_FOR_ARDUINO
#define LD06_FOR_ARDUINO
#include <vector>

class LD06forArduino
{
  private:
    // note: 12 data *3 Byte
    const int DATA_BYTE = 36;
    // note: 1(Start)+2(Datalen)+2(Speed)+2(SAngle)+36(DataByte)+2(EAngle)+2(TimeStamp)+1(CRC)
    const int TOTAL_DATA_BYTE = 48;

    void calc_lidar_data(std::vector<char> &values);
  public:
    std::vector<float> angles;
    std::vector<float> distances;
    std::vector<int> confidences;

    char start_byte;
    char data_length;
    float Speed;
    float FSA;
    float LSA;
    int time_stamp;
    int CS;
    float angle_step;

    void Init(const int pin);
    void read_lidar_data();
};

#endif



LD06forArduino ld06;

void setup() {
 // M5.begin(true, false, true);
  delay(10);
 // Serial.begin(115200);
  myStart = millis();   // set delay
  ld06.Init(19);  // pin not used 


  
  if ( ! display.begin(0x3D) ) {
    // Serial.println("Unable to initialize OLED");
     while (1) yield();
  }    
  display.setTextSize(1);
  display.setTextColor(SSD1327_WHITE);

  display.setRotation(0);
  display.setCursor(0,0);

  display.setCursor(0, 0);
  display.println("Rocksetta D100 Lidar");
  // Draw a triangle to show the Lidar device
  display.drawTriangle(64,62,60,66,68,66,  255);

  float myScreenWidthMeters = (MY_ZOOM_POS_X - MY_ZOOM_NEG_X) / 1000.0;
  display.setCursor(3, 120);  // near bottom
  display.print("Sceen Width: ");
  display.print(String(myScreenWidthMeters,1));
  display.println(" m");

}

void loop() {
  
    if ( (millis() - myStart ) >= myDelay) {       
      myStart = millis();      //  reset the delay time
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Rocksetta D100 Lidar");
      // Draw a triangle to show the Lidar device
      display.drawTriangle(64,62,60,66,68,66,  255);

      // Measurements
     
      float myScreenWidthMeters = (MY_ZOOM_POS_X - MY_ZOOM_NEG_X) / 1000.0;
      display.setCursor(3, 120);  // near bottom
      display.print("Sceen Width: ");
      display.print(String(myScreenWidthMeters,1));
      display.println(" m");
    }



  // put your main code here, to run repeatedly:
 // M5.update();

  //Serial.println("data start");
  ld06.read_lidar_data();

 // Serial.printf("start_bytet:%d, data_length:%d, Speed:%f, FSA:%f, LSA:%f, time_stamp:%d, CS:%d",  ld06.start_byte, ld06.data_length, ld06.Speed, ld06.FSA, ld06.LSA, ld06.time_stamp, ld06.CS);
   
 // Serial.print(ld06.data_length,HEX);
 // Serial.print(", ");
/*

  Serial.print( ld06.distances.size() );
  Serial.print(", ");
  Serial.print( ld06.angles.size() );
  Serial.print(", ");

// Serial printing the vector array seems to not work well.

  Serial.println();
*/

  for (int i = 0; i < ld06.data_length; i++) {
/*
    if (ld06.angles[i] > -3 && ld06.angles[i] < 3 && ld06.distances[i] < 300)
      Serial.print("Hit!");
      display.setCursor(3,30);
      display.println(ld06.distances[i]);
      display.setCursor(3,90);
      display.println(ld06.angles[i]);
*/

      byte myShow = 255;


      // lidar going counterclockwise so flip sin and cos
      int myX = round(-1 * ld06.distances[i] * sin(ld06.angles[i] * M_PI / 180.0));  // -1 to flip left right
      int myY = round(ld06.distances[i] * cos(ld06.angles[i] * M_PI / 180.0));


      int   myX1Map = map((int)myX, MY_ZOOM_NEG_X, MY_ZOOM_POS_X, 0, 127);  // not sure what to map from possibly 8000 mm = 8 m
    // if (myX1Map < -64){myX1Map = -64;}
      if (myX1Map < 0){myX1Map = 0;}
      if (myX1Map > 127){myX1Map = 127;}

      int   myY1Map = map((int)myY, MY_ZOOM_NEG_Y, MY_ZOOM_POS_Y, 0, 127);
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


    // csv formated
    Serial.print(String(myStoreAngle,1)); 
    Serial.print(", ");  
    Serial.print(String(myStoreDistance,1)); 
    Serial.println();  
*/

  // for the OLED display
    display.drawPixel(myX1Map + myMidX, myY1Map + myMidY, myShow);

  }
  

    
  display.display();



// can't have a delay cause it wrecks the serial input?
 // delay(2000);
}


//UART myUART0(PA_0,  PI_9,  NC, NC); //TX, RX, RTS, CTS  NOTE: NC means not connected

//UART SerialLIDAR_UART1(PA_9,  PA_10, NC, NC); 

//UART myUART6(PC_6,  PC_7, NC, NC);    // pin D5 TX, pin D4 RX
UART myUART1(PA_9,  PA_10, NC, NC);   // pin D14 TX, pin D13 RX same as pre-defined Serial1


void LD06forArduino::Init(const int pin) {
 // Serial2.begin(230400, SERIAL_8N1, pin);
  //Serial2.begin(230400);
  //Serial2.begin(230400);
 // Serial.begin(115200);
  //Serial.begin(230400);
 // Serial1.begin(115200, SERIAL_8N1, D7, D6); //  XIAO Rx=D7, Tx=D6, others Rx = 4, Tx = 5 will work for ESP32, S2, S3 and C3
 // Serial1.begin(115200); // NOPE!  
 
 // Serial1.begin(230400, SERIAL_8N1, D7, D6); // NOPE! 

   myUART1.begin(230400, SERIAL_8N1);

}

void LD06forArduino::calc_lidar_data(std::vector<char> &values) {

  start_byte = values[0];
  data_length = 0x1F & values[1];
  Speed = float(values[3] << 8 | values[2]) / 100;
  FSA = float(values[5] << 8 | values[4]) / 100;
  LSA = float(values[values.size() - 4] << 8 | values[values.size() - 5]) / 100;
  time_stamp = int(values[values.size() - 2] << 8 | values[values.size() - 3]);
  CS = int(values[values.size() - 1]);

  if (LSA - FSA > 0) {
    angle_step = (LSA - FSA) / (data_length - 1);
  } else {
    angle_step = (LSA + (360 - FSA)) / (data_length - 1);
  }


  if (angle_step > 20) {
    return;
  }

  // note: 過去のデータを初期化
  angles.clear();
  confidences.clear();
  distances.clear();

  for (int i = 0; i < data_length; i++) {
    float raw_deg = FSA + i * angle_step;
    angles.push_back(raw_deg <= 360 ? raw_deg : raw_deg - 360);
    confidences.push_back(values[8 + i * 3]);
    distances.push_back(int(values[8 + i * 3 - 1] << 8 | values[8 + i * 3 - 2]));

  }
}

std::vector<char> tmpChars;

void LD06forArduino::read_lidar_data() {

  // note: Serial２が機能していない場合はスキップ
  if (!myUART1.available()) {
    return;
  }

  bool loopFlag = true;
  char tmpInt;

  while (loopFlag) {
    tmpInt = myUART1.read();

    if (tmpInt == 0x54 && tmpChars.empty()) {
      tmpChars.push_back(tmpInt);
      continue;
    } else if (tmpChars.size() == TOTAL_DATA_BYTE - 1 ) {

      loopFlag = false;
      calc_lidar_data(tmpChars);
      tmpChars.clear();
      continue;

    } else if (tmpChars.size() > 0) {
      if (tmpChars[0] == 0x54) {
        tmpChars.push_back(tmpInt);
      }
      if (tmpChars.size() > 1) {
        if (tmpChars[1] != 0x2C) {
          tmpChars.clear();
        }
      }
    }
  }
}
