/*
  WiFi Web Server LED Blink
  
  Enter you wifi and password in the code below 

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi module (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 9.

 If the IP address of your board is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.



 created 25 Nov 2012
 by Tom Igoe
 */


#include <Arduino.h> // Only needed by https://platformio.org/
#include "WiFi.h"

#include "SDMMCBlockDevice.h"
#include "FATFileSystem.h"

SDMMCBlockDevice block_device;
mbed::FATFileSystem fs("fs");
FILE *myFile;
char buffer[40];   // must be long enough for all data points with commas: 56,34,23,56





// Choose either the following arduino_secrets.h tab and bracket out the next 2 lines after it
// That route is more secure.
// Or just change the lines below for your Network and Password. Eaier but not as secure
// Since if you share this file it will have your info on it

//#include "arduino_secrets.h"   // more safe
#define SECRET_SSID "your SSID"
#define SECRET_PASS "your Password"



char ssid[] = SECRET_SSID;    // Changing the secret strings to a character array
char pass[] = SECRET_PASS;    
int keyIndex = 0;              

int status = WL_IDLE_STATUS;
WiFiServer server(80);


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}



void setup() {
  Serial.begin(115200);      // initialize serial communication
  delay(5000);
  Serial.println("Wait a bit to connect serial monitor");
  delay(5000);
  Serial.println("Wait a bit");
  delay(5000);
  Serial.println("Wait a bit");
  
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
  pinMode(LEDB, OUTPUT);      // set the LED pin mode
  digitalWrite(LEDB, LOW);  
  setupSdCard();


  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 5 seconds for connection:
    delay(5000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
  digitalWrite(LEDB, HIGH);  
  digitalWrite(LED_BUILTIN, LOW); 
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    int x1 = analogRead(A1);                // read A1
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
           //client.println("{answer:42}");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<input type=button value='Start Recording Data' onclick='{location=\"/L\"}'>");
            client.print("<input type=button value='Stop Recording Data' onclick='{location=\"/H\"}'>");
            client.print("<br> AnalogRead(A1); = "+ String(x1) );  

            // The HTTP response ends with another blank line:
            client.println();    
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
          writeToSdCard();  // this does it once? `
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);  
    Serial.println("");
  }
}



void setupSdCard(){

 // Serial.begin(9600);
 //while (!Serial);

  Serial.println("Mounting SDCARD...");
  int err =  fs.mount(&block_device);
  if (err) {
    // Reformat if we can't mount the filesystem
    // this should only happen on the first boot
    Serial.println("No filesystem found, please check on computer and manually format if needed.");
  //  err = fs.reformat(&block_device);  // seriously don't want to format your good data
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
 Serial.println("------------------------- Done --------------------------------"); 
}





void writeToSdCard(){

   int myTime = millis()/1000; // seconds since the sketch began
  //char myFileName[] = "fs/folder1/00000000.json";  // works if folder1 pre-made
  char myFileName[] = "fs/00000000.json";   // fs/ needs to be there think fileSystem
  int myExtensionLength = 4;  // .txt = 3 .json = 4
  // does anyone understand why the  + '0' is needed below???
  myFileName[sizeof(myFileName)- myExtensionLength - 10] = myTime/10000000 % 10 + '0';
  myFileName[sizeof(myFileName)- myExtensionLength - 9] = myTime/1000000 % 10 + '0';
  myFileName[sizeof(myFileName)- myExtensionLength - 8] = myTime/100000 % 10 + '0';
  myFileName[sizeof(myFileName)- myExtensionLength - 7] = myTime/10000 % 10 + '0';
  myFileName[sizeof(myFileName)- myExtensionLength - 6] = myTime/1000 % 10 + '0';
  myFileName[sizeof(myFileName)- myExtensionLength - 5] = myTime/100 % 10 + '0';
  myFileName[sizeof(myFileName)- myExtensionLength - 4] = myTime/10 % 10 + '0';
  myFileName[sizeof(myFileName)- myExtensionLength - 3] = myTime % 10 + '0';
  // Can make a new file but can't make a new folder
  myFile = fopen(myFileName, "a");  // "a" for append or make it if file not there
    Serial.println(myFileName);

  //  fprintf(myFile,"test \r\n");
    fprintf(myFile,"{\"protected\":{\"ver\":\"v1\",\"alg\":\"none\",\"iat\":1603914126},");
    fprintf(myFile,"\"signature\":\"0\",\"payload\":{\"device_type\":\"TEST\",\"interval_ms\":10,");
    fprintf(myFile,"\"sensors\":[{\"name\":\"W\",\"units\":\"N/A\"},{\"name\":\"X\",\"units\":\"N/A\"},{\"name\":\"Y\",\"units\":\"N/A\"},{\"name\":\"Z\",\"units\":\"N/A\"}],");
    fprintf(myFile,"\"values\":[[");
    
    // now lets get the sensor values   
    char buffer1[7]; 
    itoa( analogRead(A1), buffer1, 10);
    
    char buffer2[7]; 
    itoa( analogRead(A2), buffer2, 10);
    
    char buffer3[7]; 
    itoa( analogRead(A3), buffer3, 10);
    
    char buffer4[7]; 
    itoa( analogRead(A4), buffer4, 10);

    char myComma[] = ",";
    memcpy (buffer, "", sizeof(buffer) );  // one way to delete the old buffer
    strcat(buffer, buffer1);
    strcat(buffer, myComma);
    strcat(buffer, buffer2);
    strcat(buffer, myComma);
    strcat(buffer, buffer3);
    strcat(buffer, myComma);
    strcat(buffer, buffer4);
   
    fprintf(myFile, buffer);
    fprintf(myFile,"]]}}\r\n");

  fclose(myFile);
Serial.println("Printed data to the file: "+String(myFileName)); 
Serial.println(buffer1); 
Serial.println(buffer2);
Serial.println(buffer3); 
Serial.println(buffer4);  



}

