/*
  OV767X - Camera Capture Raw Bytes

  This sketch reads a frame from the OmniVision OV7670 camera
  and writes the bytes to the Serial port. Use the Procesing
  sketch in the extras folder to visualize the camera output.

  Circuit:
    - Arduino Nano 33 BLE board
    - OV7670 camera module:
      - 3.3 connected to 3.3
      - GND connected GND
      - SIOC connected to A5
      - SIOD connected to A4
      - VSYNC connected to 8
      - HREF connected to A1
      - PCLK connected to A0
      - XCLK connected to 9
      - D7 connected to 4
      - D6 connected to 6
      - D5 connected to 5
      - D4 connected to 3
      - D3 connected to 2
      - D2 connected to 0 / RX
      - D1 connected to 1 / TX
      - D0 connected to 10


these are the defines for the above

#define OV7670_VSYNC 8
#define OV7670_HREF  A1
#define OV7670_PLK   A0
#define OV7670_XCLK  9
#define OV7670_D0    10
#define OV7670_D1    1
#define OV7670_D2    0
#define OV7670_D3    2
#define OV7670_D4    3
#define OV7670_D5    5
#define OV7670_D6    6
#define OV7670_D7    4

enum
{
  YUV422 = 0,
  RGB444 = 1,
  RGB565 = 2,
  // SBGGR8 = 3
  GRAYSCALE = 4
};

enum
{
  VGA = 0,  // 640x480
  CIF = 1,  // 352x240
  QVGA = 2, // 320x240
  QCIF = 3,  // 176x144
  QQVGA = 4,  // 160x120
};


  int begin(int resolution, int format, int fps); // Supported FPS: 1, 5, 10, 15, 30


      

  This example code is in the public domain.
*/

#include <Arduino_OV767X.h>



//  - OV7670 camera module:
//  - 3.3 connected to 3.3
//  - GND connected GND
//  - SIOC/SCL connected to A5
//  - SIOD/SDA connected to A4

#define OV7670_VSYNC 8
#define OV7670_HREF  A1
#define OV7670_PLK   A0
#define OV7670_XCLK  9
#define OV7670_D0    0  // If green tint swith Do D1
#define OV7670_D1    1  // If green tint swith Do D1
#define OV7670_D2    2
#define OV7670_D3    3
#define OV7670_D4    4
#define OV7670_D5    5
#define OV7670_D6    6
#define OV7670_D7    7


const int myStartX = 0;
const int myStartY = 0;
const int myEndX = 96;
const int myEndY = 96;

const int myCroppedWidth = myEndX - myStartX;
const int myCroppedHeight = myEndY - myStartY;
const int myBytesPerPixel = 2;  // RGB565 = 2 Bytes

const int original_width = 160;  
const int original_height = 120;

int bytesPerFrame;

byte data[original_width * original_height * myBytesPerPixel]; // Original image 160 x 120 x 2 bytes RGB565 
byte myCroppedData[myCroppedWidth * myCroppedHeight * myBytesPerPixel];  // Cropped image ? x ? x 2 bytes RGB565 

void setup() {

  Serial.begin(115200);
  while (!Serial);

  if (!Camera.begin(QQVGA, RGB565, 5)) { //Resolution, Byte Format, FPS 1 or 5
    Serial.println("Failed to initialize camera!");
    while (1);
  }

  //bytesPerFrame = Camera.width() * Camera.height() * Camera.bytesPerPixel(); // test original with 
  bytesPerFrame = myCroppedWidth * myCroppedHeight * myBytesPerPixel;          // crop with

  // Optionally, enable the test pattern for testing
  // Camera.testPattern();
}

void loop() {
  Camera.readFrame(data);

  myCrop();

  // Serial.write(data, bytesPerFrame); // test original with 
  Serial.write(myCroppedData, bytesPerFrame); // crop with
}


void myCrop() {

      //int min_x = (176-96)/2;
      //int min_y = (144-96)/2;
      /*
      int original_width = 160;  
      int original_height = 120;
      int min_x = 0;     //(160-96)*2/2;  
      int min_y = 0;     //(120-96)/2;
      int max_x = 96;     //min_x+(96*2);  
      int max_y = 96;     //min_y+96;
 
int myStartX = 0;
int myStartY = 0;
int myEndX = 96;
int myEndY = 96;
       * 
       */

       
      int index = 0;


      // Crop 96x96 image
      //myCroppedData.length = 0;

      for (int y = myStartY; y < myEndY; y++) {
        for (int x = myStartX; x < (myEndX * myBytesPerPixel); x++){  
           myCroppedData[index++] = data[(y*original_width * myBytesPerPixel)+x]; 
        }
      }




/*
      // just normal
      for (int y = 0; y < 120; y++) {
        for (int x = 0; x < 160*2; x++) {
          myCroppedData[index++] = data[(y*160)+x];
        }
      }
*/
      
  
}
