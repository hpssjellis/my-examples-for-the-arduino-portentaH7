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

// for SD card
#include "SDMMCBlockDevice.h"
#include "FATFileSystem.h"

SDMMCBlockDevice block_device;
mbed::FATFileSystem fs("fs");


int mode = 0; 




// Choose either the following arduino_secrets.h tab and bracket out the next 2 lines after it
// That route is more secure.
// Or just change the lines below for your Network and Password. Eaier but not as secure
// Since if you share this file it will have your info on it

//#include "arduino_secrets.h"   // more safe
#define SECRET_SSID ""
#define SECRET_PASS ""



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


  Serial.println("Mounting SDCARD...");
  int err =  fs.mount(&block_device);
  if (err) {
     Serial.println("No SD Card filesystem found, please check SD Card on computer and manually format if needed.");
     // int err = fs.reformat(&block_device);  // seriously don't want to format your good data
  }




  mkdir("fs/myFolder1",0555);  
  char myFileName[] = "fs/myFolder1/index.html";   // "fs/" needs to be there, think fileSystem
  unsigned char c; 
  FILE *fp = fopen(myFileName, "r");              // "r" read only
     while (!feof(fp)){                           // while not end of file
        c=fgetc(fp);                              // get a character/byte from the file
        Serial.print((char)c);                    // show it as a text character
     }
  fclose(fp); 
  Serial.println("------------------------- Done Showing file --------------------------------");

  delay(10000);   // wait a bit
  
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

            
            if (mode == 2 ){          
              client.println("Content-Type: image/png");
              client.println();
              mkdir("fs/myFolder1",0555);  
              char myFileName[] = "fs/myFolder1/img01.png";   // "fs/" needs to be there, think fileSystem
              char buffer[128];
              FILE *fp = fopen(myFileName, "rb");              // "r" read only
              while(fread(buffer, 1, 128, fp)) {
                 client.write((uint8_t*)buffer, 128); 
                 //delayMicroseconds(200);
              }
              fclose(fp); 
              Serial.println("------------------------- Done Showing Image file --------------------------------");
              delay(1);
              client.stop();
              currentLine="";
              break;
              } 




           
            client.println("Content-type:text/html");
           //client.println("{answer:42}");
            client.println();

            if (mode == 1 ){
              mkdir("fs/myFolder1",0555);  
              char myFileName[] = "fs/myFolder1/index.html";   // "fs/" needs to be there, think fileSystem

              char buffer[128];
              FILE *fp = fopen(myFileName, "r");              // "r" read only
              while (!feof(fp)){ 
                 fgets(buffer, 128, fp);          
                 client.write((char*)buffer, 128);     
                 Serial.write((char*)buffer, 128);           
              }
              fclose(fp); 
              Serial.println("------------------------- Done Showing HTML file --------------------------------");
              delay(1);
              client.stop();
              currentLine="";
              break; 
              }




            

            // the content of the HTTP response follows the header:
            client.print("<input type=button value='LED_BUILTIN Off' onclick='{location=\"/H\"}'>");
            client.print("<input type=button value='LED_BUILTIN On' onclick='{location=\"/L\"}'>");
            client.print("<input type=button value='Load html file from SD card' onclick='{location=\"/SD-card\"}'>");
            client.print("<input type=button value='Load Image img01.png from SD card' onclick='{location=\"/image\"}'>");
            client.print("<br> AnalogRead(A1); = "+ String(x1) ); 
            client.print("<br><img width=320 height=320 src='http://192.168.137.85/image' />");    



            // The HTTP response ends with another blank line:
            client.println();    
            // break out of the while loop:
            break;
           }else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
          mode= -1;
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
          mode= -2;
        }        
        if (currentLine.endsWith("GET /SD-card")) {           // show SD card index.html
          mode=1;               
        }        
        if (currentLine.endsWith("GET /image")) {           // show SD card PNG img01.png
          mode=2;               
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
