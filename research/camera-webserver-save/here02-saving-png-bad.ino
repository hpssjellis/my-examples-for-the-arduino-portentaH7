/*
  Portenta - TestSDCARD

  The sketch shows how to mount an SDCARD and list its content.
  then add a file.

  Note: SD Card seems finicky, takes a few times to load the filesystem

  The circuit:
   - Portenta H7 + Vision Shield
   or
   - Portenta H7 + Portenta Breakout

  This example code is in the public domain.
*/
#include "SDMMCBlockDevice.h"
#include "FATFileSystem.h"

SDMMCBlockDevice block_device;
mbed::FATFileSystem fs("fs");


#include <PNGenc.h>

PNG png; // static instance of the PNG encoder class
FILE *myPngFile;

#define WIDTH 128
#define HEIGHT 128

uint8_t ucPal[768] = {0,0,0,0,255,0}; // black, green
uint8_t ucAlphaPal[256] = {0,255}; // first color (black) is fully transparent
uint8_t ucOut[4096];





void makePNG() {


  
int rc, iDataSize, x, y;
uint8_t ucLine[WIDTH];
long l;

  
  l = micros();

  rc = png.open(ucOut, sizeof(ucOut));

  if (rc == PNG_SUCCESS) {


        rc = png.encodeBegin(WIDTH, HEIGHT, PNG_PIXEL_INDEXED, 8, ucPal, 3);
        png.setAlphaPalette(ucAlphaPal);
        if (rc == PNG_SUCCESS) {
            for (int y=0; y<HEIGHT && rc == PNG_SUCCESS; y++) {
              // prepare a line of image to create a red box with an x on a transparent background
              if (y==0 || y == HEIGHT-1) {
                memset(ucLine, 1, WIDTH); // top+bottom green lines 
              } else {
                memset(ucLine, 0, WIDTH);
                ucLine[0] = ucLine[WIDTH-1] = 1; // left/right border
                ucLine[y] = ucLine[WIDTH-1-y] = 1; // X in the middle
              }
                rc = png.addLine(ucLine);
            } // for y
            // write the png file to disk
            fprintf(myPngFile, (const char *)ucOut, sizeof(ucOut) );
            fclose(myPngFile);
            iDataSize = png.close();
            l = micros() - l;
            Serial.print(iDataSize);
            Serial.print(" bytes of data written to file in ");
            Serial.print((int)l);
            Serial.print(" us\n");
         }
           
  } else {
    Serial.println("Failed to create PNG");
  }



} 




void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
  delay(5000); // time to connect serial
  Serial.println("15 seconds to connect serial monitor if needed");
  delay(5000);
  Serial.println("10 seconds to connect serial monitor if needed");
  delay(5000);
  Serial.println("5 seconds to connect serial monitor if needed");
  delay(5000);
  //while (!Serial);  // blocking call

  Serial.println("Mounting SDCARD...");
  int err =  fs.mount(&block_device);
  if (err) {
     Serial.println("No SD Card filesystem found, please check SD Card on computer and manually format if needed.");
     // int err = fs.reformat(&block_device);  // seriously don't want to format your good data
  }

}




void loop() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // flips LED on and off
  
  // Make a folder if needed
  mkdir("fs/myFolder2",0777);                     // 0777 full access permissions linux style 
   
  char myFileName[] = "fs/myFolder2/test2.txt";   // "fs/" needs to be there, think fileSystem
 
  FILE *myFile = fopen(myFileName, "w");          // "a" for append (add to file), "w" write, "r" read ??
 
     Serial.println(myFileName);
     fprintf(myFile,"Test how cool this is \r\n");
     fprintf(myFile,"Also this line \r\n");
   
  fclose(myFile);

  Serial.println("------------------------- Done Writing file --------------------------------");
  delay(10);
   
  unsigned char c; 
  FILE *fp = fopen(myFileName, "r");              // "r" read only
     while (!feof(fp)){                           // while not end of file
        c=fgetc(fp);                              // get a character/byte from the file
        //printf("Read from file %02x\n\r",c);    // and show it in hex format
        Serial.print((char)c);                    // show it as a text character
     }
  fclose(fp); 
  Serial.println("------------------------- Done Showing file --------------------------------");
  Serial.println("------------------------- Making a PNG --------------------------------");
   char myPngFileName[] = "fs/myFolder2/my01.png";   // "fs/" needs to be there, think fileSystem
 
  myPngFile = fopen(myPngFileName, "w");          // "a" for append (add to file), "w" write, "r" read ??
 
  
  makePNG();
  Serial.println("------------------------- Done and waiting 20 seconds --------------------------------");
  delay(20000);   // wait a bit
  
}

