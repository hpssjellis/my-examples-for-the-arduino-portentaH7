/****************************************************************************************************************************
  LittleFS_Test.ino - Filesystem wrapper for LittleFS on the Mbed

  For MBED  boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/LittleFS_
  Licensed under MIT license
*****************************************************************************************************************************/

#define LFS_MBED_PORTENTA_H7_VERSION_MIN_TARGET      "LittleFS_Portenta_H7 v1.2.0"
#define LFS_MBED_PORTENTA_H7_VERSION_MIN             1002000

#define _LFS_LOGLEVEL_          1

#define FORCE_REFORMAT          false

#include <LittleFS_Portenta_H7.h>

LittleFS_MBED *myFS;

uint32_t FILE_SIZE_KB = 64;



//#include "SDMMCBlockDevice.h" // Multi Media Card APIs
//#include "FATFileSystem.h"    // API to run operations on a FAT file system
//SDMMCBlockDevice blockDevice;
//mbed::FATFileSystem fileSystem("fs");

#include "camera.h" // Arduino Mbed Core Camera APIs
#include "himax.h"  // API to read from the Himax camera found on the Portenta Vision Shield
HM01B0 himax;
Camera cam(himax);

FrameBuffer frameBuffer; // Buffer to save the camera stream

// Settings for our setup
#define IMAGE_HEIGHT (unsigned int)240
#define IMAGE_WIDTH (unsigned int)320
#define IMAGE_MODE CAMERA_GRAYSCALE
#define BITS_PER_PIXEL (unsigned int)8
#define PALETTE_COLORS_AMOUNT (unsigned int)(pow(2, BITS_PER_PIXEL))
#define PALETTE_SIZE  (unsigned int)(PALETTE_COLORS_AMOUNT * 4) // 4 bytes = 32bit per color (3 bytes RGB and 1 byte 0x00)
#define IMAGE_PATH "/fs/image.bmp"

// Headers info
#define BITMAP_FILE_HEADER_SIZE (unsigned int)14 // For storing general information about the bitmap image file
#define DIB_HEADER_SIZE (unsigned int)40 // For storing information about the image and define the pixel format
#define HEADER_SIZE (BITMAP_FILE_HEADER_SIZE + DIB_HEADER_SIZE)



// Get the raw image data (8bpp grayscale)
unsigned char * captureImage(){
    if (cam.grabFrame(frameBuffer, 3000) == 0){
        return frameBuffer.getBuffer();
    } else {
        Serial.println("could not grab the frame");
        while (1);
    }
}



// Set the headers data
void setFileHeaders(unsigned char *bitmapFileHeader, unsigned char *bitmapDIBHeader, int fileSize){
    // Set the headers to 0
    memset(bitmapFileHeader, (unsigned char)(0), BITMAP_FILE_HEADER_SIZE);
    memset(bitmapDIBHeader, (unsigned char)(0), DIB_HEADER_SIZE);

    // File header
    bitmapFileHeader[0] = 'B';
    bitmapFileHeader[1] = 'M';
    bitmapFileHeader[2] = (unsigned char)(fileSize);
    bitmapFileHeader[3] = (unsigned char)(fileSize >> 8);
    bitmapFileHeader[4] = (unsigned char)(fileSize >> 16);
    bitmapFileHeader[5] = (unsigned char)(fileSize >> 24);
    bitmapFileHeader[10] = (unsigned char)HEADER_SIZE + PALETTE_SIZE;

    // Info header
    bitmapDIBHeader[0] = (unsigned char)(DIB_HEADER_SIZE);
    bitmapDIBHeader[4] = (unsigned char)(IMAGE_WIDTH);
    bitmapDIBHeader[5] = (unsigned char)(IMAGE_WIDTH >> 8);
    bitmapDIBHeader[8] = (unsigned char)(IMAGE_HEIGHT);
    bitmapDIBHeader[9] = (unsigned char)(IMAGE_HEIGHT >> 8);
    bitmapDIBHeader[14] = (unsigned char)(BITS_PER_PIXEL);
}

void setColorMap(unsigned char *colorMap){
    //Init the palette with zeroes
    memset(colorMap, (unsigned char)(0), PALETTE_SIZE);
    
    // Gray scale color palette, 4 bytes per color (R, G, B, 0x00)
    for (int i = 0; i < PALETTE_COLORS_AMOUNT; i++) {
        colorMap[i * 4] = i;
        colorMap[i * 4 + 1] = i;
        colorMap[i * 4 + 2] = i;
    }
}

// Save the headers and the image data into the .bmp file
void saveImage(unsigned char *imageData, const char* imagePath){
    int fileSize = BITMAP_FILE_HEADER_SIZE + DIB_HEADER_SIZE + IMAGE_WIDTH * IMAGE_HEIGHT;
    FILE *file = fopen(imagePath, "w");

    // Bitmap structure (Head + DIB Head + ColorMap + binary image)
    unsigned char bitmapFileHeader[BITMAP_FILE_HEADER_SIZE];
    unsigned char bitmapDIBHeader[DIB_HEADER_SIZE];
    unsigned char colorMap[PALETTE_SIZE]; // Needed for <= 8bpp grayscale bitmaps    

    setFileHeaders(bitmapFileHeader, bitmapDIBHeader, fileSize);
    setColorMap(colorMap);

    // Write the bitmap file
    fwrite(bitmapFileHeader, 1, BITMAP_FILE_HEADER_SIZE, file);
    fwrite(bitmapDIBHeader, 1, DIB_HEADER_SIZE, file);
    fwrite(colorMap, 1, PALETTE_SIZE, file);
    fwrite(imageData, 1, IMAGE_HEIGHT * IMAGE_WIDTH, file);

    // Close the file stream
    fclose(file);
}

void countDownBlink(){
    for (int i = 0; i < 6; i++){
        digitalWrite(LEDG, i % 2);
        delay(500);
    }
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, LOW);
}





void readCharsFromFile(const char * path)
{
  Serial.print("readCharsFromFile: "); Serial.print(path);

  FILE *file = fopen(path, "r");

  if (file)
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  char c;

  while (true)
  {
    c = fgetc(file);

    if ( feof(file) )
    {
      break;
    }
    else
      Serial.print(c);
  }

  fclose(file);
}

void readFile(const char * path)
{
  Serial.print("Reading file: "); Serial.print(path);

  FILE *file = fopen(path, "r");

  if (file)
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  char c;
  uint32_t numRead = 1;

  while (numRead)
  {
    numRead = fread((uint8_t *) &c, sizeof(c), 1, file);

    if (numRead)
      Serial.print(c);
  }

  fclose(file);
}

void writeFile(const char * path, const char * message, size_t messageSize)
{
  Serial.print("Writing file: "); Serial.print(path);

  FILE *file = fopen(path, "w");

  if (file)
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  if (fwrite((uint8_t *) message, 1, messageSize, file))
  {
    Serial.println("* Writing OK");
  }
  else
  {
    Serial.println("* Writing failed");
  }

  fclose(file);
}

void appendFile(const char * path, const char * message, size_t messageSize)
{
  Serial.print("Appending file: "); Serial.print(path);

  FILE *file = fopen(path, "a");

  if (file)
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  if (fwrite((uint8_t *) message, 1, messageSize, file))
  {
    Serial.println("* Appending OK");
  }
  else
  {
    Serial.println("* Appending failed");
  }

  fclose(file);
}

void deleteFile(const char * path)
{
  Serial.print("Deleting file: "); Serial.print(path);

  if (remove(path) == 0)
  {
    Serial.println(" => OK");
  }
  else
  {
    Serial.println(" => Failed");
    return;
  }
}

void renameFile(const char * path1, const char * path2)
{
  Serial.print("Renaming file: "); Serial.print(path1);
  Serial.print(" to: "); Serial.print(path2);

  if (rename(path1, path2) == 0)
  {
    Serial.println(" => OK");
  }
  else
  {
    Serial.println(" => Failed");
    return;
  }
}

void testFileIO(const char * path)
{
  Serial.print("Testing file I/O with: "); Serial.print(path);

#define BUFF_SIZE     512

  static uint8_t buf[BUFF_SIZE];

  FILE *file = fopen(path, "w");

  if (file)
  {
    Serial.println(" => Open OK");
  }
  else
  {
    Serial.println(" => Open Failed");
    return;
  }

  size_t i;
  Serial.println("- writing" );

  uint32_t start = millis();

  size_t result = 0;

  // Write a file with FILE_SIZE_KB
  for (i = 0; i < FILE_SIZE_KB * 2; i++)
  {
    result = fwrite(buf, BUFF_SIZE, 1, file);

    if ( result != 1)
    {
      Serial.print("Write result = "); Serial.println(result);
      Serial.print("Write error, i = "); Serial.println(i);

      break;
    }
  }

  Serial.println("");
  uint32_t end = millis() - start;

  Serial.print(i / 2);
  Serial.print(" Kbytes written in (ms) ");
  Serial.println(end);

  fclose(file);

  printLine();

  /////////////////////////////////

  file = fopen(path, "r");

  start = millis();
  end = start;
  i = 0;

  if (file)
  {
    start = millis();
    Serial.println("- reading" );

    result = 0;

    fseek(file, 0, SEEK_SET);

    // Read a file with FILE_SIZE_KB
    for (i = 0; i < FILE_SIZE_KB * 2; i++)
    {
      result = fread(buf, BUFF_SIZE, 1, file);

      if ( result != 1 )
      {
        Serial.print("Read result = "); Serial.println(result);
        Serial.print("Read error, i = "); Serial.println(i);

        break;
      }
    }

    Serial.println("");
    end = millis() - start;

    Serial.print((i * BUFF_SIZE) / 1024);
    Serial.print(" Kbytes read in (ms) ");
    Serial.println(end);

    fclose(file);
  }
  else
  {
    Serial.println("- failed to open file for reading");
  }
}

void printLine()
{
  Serial.println("====================================================");
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)

    delay(1000);

  Serial.print("\nStart LittleFS_Test on "); Serial.println(BOARD_NAME);
  Serial.println(LFS_MBED_PORTENTA_H7_VERSION);
  
#if defined(LFS_MBED_PORTENTA_H7_VERSION_MIN)
  if (LFS_MBED_PORTENTA_H7_VERSION_INT < LFS_MBED_PORTENTA_H7_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(LFS_MBED_PORTENTA_H7_VERSION_MIN_TARGET);
  }
#endif

  myFS = new LittleFS_MBED();

  if (!myFS->init())
  {
    Serial.println("LITTLEFS Mount Failed");

    return;
  }

  char fileName1[] = MBED_LITTLEFS_FILE_PREFIX "/hello1.txt";
  char fileName2[] = MBED_LITTLEFS_FILE_PREFIX "/hello2.txt";

  char message[]  = "Hello from " BOARD_NAME "\n";

  printLine();
  writeFile(fileName1, message, sizeof(message));
  printLine();
  readFile(fileName1);
  printLine();

  appendFile(fileName1, message, sizeof(message));
  printLine();
  readFile(fileName1);
  printLine();

  renameFile(fileName1, fileName2);
  printLine();
  readCharsFromFile(fileName2);
  printLine();

  deleteFile(fileName2);
  printLine();
  readFile(fileName2);
  printLine();

  testFileIO(fileName1);
  printLine();
  testFileIO(fileName2);
  printLine();
  deleteFile(fileName1);
  printLine();
  deleteFile(fileName2);
  printLine();

  Serial.println( "\nTest complete" );


    // Init the cam QVGA, 30FPS, Grayscale
    if (!cam.begin(CAMERA_R320x240, IMAGE_MODE, 30)){
        Serial.println("Unable to find the camera");
    }
    countDownBlink();
    Serial.println("Fetching camera image...");
    unsigned char *imageData = captureImage();
    digitalWrite(LEDB, HIGH);




  
}

void loop()
{
}
