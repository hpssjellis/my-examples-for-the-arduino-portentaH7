/*
  Portenta - TestSDCARD
This is a draft an might get deleted if it does not work.
Make a CSV file
----------------------------------------
Connect D6 -->push button --> 3V3 to use it as a sensor activation button
Connect A1 through A4 to voltage dividers to take 2 prong sensor readings
example GND --> 1000 ohm resistor --> A1 AND also A1 --> light sensor --> 3V3

Note: Makes MULTIPLE CSV files for edgeimpulse.com upload
------------------------------------------
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

// Global Variables
FILE *myFile;
char buffer[50];   // must be long enough for all data points with commas: 56,34,23,56
int myDelay = 14000;  // delay in milliseconds between sensor read
static unsigned long myLastMillis = 0;


void setup() {
  Serial.begin(9600);
  pinMode(D6, INPUT_PULLDOWN); // to altenatively activate a sensor read
  pinMode(LEDB, OUTPUT);
  
  while (!Serial);   // might want to get rid of this after it works

  Serial.println("Mounting SDCARD...");
  int err =  fs.mount(&block_device);
  if (err) {
    // Reformat if we can't mount the filesystem
    // this should only happen on the first boot
    Serial.println("No filesystem found, please check on computer and manually format if needed.");
    err = fs.reformat(&block_device);  // seriously don't want to format your good data
  }
  if (err) {
     Serial.println("Error formatting SDCARD ");
     while(1);
  }
  
  DIR *dir;
  struct dirent *ent;
  int dirIndex = 0;

  Serial.println("List SDCARD content: ");
  if ((dir = opendir("/fs")) != NULL) {
    // Print all the files and directories within directory (not recursively)
    while ((ent = readdir (dir)) != NULL) {
      Serial.println(ent->d_name);
      dirIndex++;
    }
    closedir (dir);
  } else {
    // Could not open directory
    Serial.println("Error opening SDCARD\n");
    while(1);
  }
  if(dirIndex == 0) {
    Serial.println("Empty SDCARD");
  }
 Serial.println("------------------------- Done SD Card Check --------------------------------"); 


}

void loop() {
   
  // Make a folder if needed
  mkdir("fs/myFolder02",0777);                     // 0777 full access permissions linux style 
   
 int myMillis = millis(); // milliseconds since the sketch began
 int myTime = millis()/1000; // seconds since the sketch began
 
 if ((millis() > myLastMillis + myDelay) || digitalRead(D6) ) {
   myLastMillis = millis();  // note if button push resets timer
   digitalWrite(LEDB, !digitalRead(LEDB)); // flip internal LED
  char myFileName[] = "fs/myFo
