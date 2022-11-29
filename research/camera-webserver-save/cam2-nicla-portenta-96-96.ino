/*
*  WiFi PNG web save
*  By Jeremy Ellis
*
*/

#include "base64.hpp"





#include <Arduino.h> // Only needed by https://platformio.org/
#include "WiFi.h"



// Choose either the following arduino_secrets.h tab and bracket out the next 2 lines after it
// That route is more secure.
// Or just change the lines below for your Network and Password. Eaier but not as secure
// Since if you share this file it will have your info on it

//#include "arduino_secrets.h"     // more safe
#define SECRET_SSID ""   // your network
#define SECRET_PASS "" // your password



char ssid[] = SECRET_SSID;    // Changing the secret strings above to a character array
char pass[] = SECRET_PASS;    
int keyIndex = 0;     



#include "camera.h"

#ifdef ARDUINO_NICLA_VISION
  #include "gc2145.h"
  GC2145 galaxyCore;
  Camera cam(galaxyCore);
  #define IMAGE_MODE CAMERA_RGB565
#else
  #include "himax.h"
  HM01B0 himax;
  Camera cam(himax);
  #define IMAGE_MODE CAMERA_GRAYSCALE
#endif


/*
Other buffer instantiation options:
  FrameBuffer fb(0x30000000);
  FrameBuffer fb(320,240,2);
*/



#include <PNGenc.h>

PNG png; // static instance of the PNG encoder class
//FILE *myPngFile;

// don't forget to set the ucOut[] to be able to handle the PNG image size
#define PNG_WIDTH 96   //320  //160  96
#define PNG_HEIGHT 96    // 320 // 120  96

// don't forget to setup the camera with the correct resolution
#define CAM_WIDTH 320
#define CAM_HEIGHT 320


FrameBuffer fb;

// could use heap or Portenta SDRAM
static uint8_t frame_buffer[CAM_WIDTH*CAM_HEIGHT] __attribute__((aligned(32)));
//static uint8_t frame_buffer[160*120] __attribute__((aligned(32)));



int iDataSize;

// 86 86 works
uint8_t ucPal[768] = {0,0,0,0,255,0}; // black, green
uint8_t ucAlphaPal[256] = {0,255}; // first color (black) is fully transparent
//uint8_t ucOut[4096];
//uint8_t ucOut[8192];
//uint8_t ucOut[10240];  // works for 96x96
//uint8_t ucOut[20480];  // compiles
//uint8_t ucOut[30720];     // compiles
//uint8_t ucOut[40960];   // compiles  
//uint8_t ucOut[81920];
uint8_t ucOut[102400];  // us this for 320 x 320 Grayscale
//uint8_t ucBase64[133120];  // just testing if it van be done. activated in the function

char ucBase64[133120];  // just testing if it van be done. activated in the function





         

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
  delay(5000); // time to connect serial
  Serial.println("15 seconds to connect serial monitor if needed");
  delay(5000);
  Serial.println("10 seconds to connect serial monitor if needed");
  delay(5000);
  Serial.println("5 seconds to connect serial monitor if needed");
  delay(5000);
  //while (!Serial);  // blocking call
  
  pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDR, HIGH);


  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 3 seconds for connection:
    delay(3000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status

   
  
  
  digitalWrite(LEDR, HIGH); 
  digitalWrite(LEDB, HIGH);  
  digitalWrite(LEDG, LOW); 


fb.setBuffer(frame_buffer); 


  Serial.println("Mounting Camera...");
  // if (!cam.begin(CAMERA_R320x240, IMAGE_MODE, 30)) {
  //if (!cam.begin(CAMERA_R160x120, CAMERA_GRAYSCALE, 30)) {
  if (!cam.begin(CAMERA_R320x320, CAMERA_GRAYSCALE, 30)) {
    Serial.println("No Camera, make sure portenta Vision shield is connected");
  }


  

  Serial.println("Camera ready");


  

}








void makePNG() {
  //long l;
  //l = micros();




  
 //  myPngFile = fopen(myPngFileName, "w");          // "a" for append (add to file), "w" write, "r" read ?? 
  int rc,  x, y;
  uint8_t ucLine[PNG_WIDTH];




  rc = png.open(ucOut, sizeof(ucOut));

  if (rc == PNG_SUCCESS) {


       // rc = png.encodeBegin(WIDTH, HEIGHT, PNG_PIXEL_INDEXED, 8, ucPal, 3);
        rc = png.encodeBegin(PNG_WIDTH, PNG_HEIGHT, PNG_PIXEL_GRAYSCALE, 8, ucPal, 3);
        png.setAlphaPalette(ucAlphaPal);
        if (rc == PNG_SUCCESS) {


           if (cam.grabFrame(fb, 3000) == 0) {
              //Serial.write(fb.getBuffer(), cam.frameSize());


              // transfer camera image to PNG class
              for (int y=0; y < PNG_HEIGHT && rc == PNG_SUCCESS; y++){    
                 memset(ucLine, 0, PNG_WIDTH); // zero the storage location
                 int yMap = map(y, 0, PNG_HEIGHT, 0, CAM_HEIGHT);
                 
                 for (int x=0; x < PNG_WIDTH && rc == PNG_SUCCESS; x++){       
                    int xMap = map(x, 0, PNG_WIDTH, 0, CAM_WIDTH);
                    uint8_t myGRAY1 = frame_buffer[(yMap * CAM_WIDTH) + xMap];   
                    ucLine[x] = myGRAY1;  
                } 
                rc = png.addLine(ucLine);
              } 


           }  




          
            iDataSize = png.close();

            
            // writes it to disk
         //   fwrite(ucOut,1, iDataSize, myPngFile);
           // fwrite(ucOut,1, sizeof(ucOut), myPngFile);
                        
       //     fclose(myPngFile);


            Serial.print("Printing the raw data");
           // Serial.write(ucOut, sizeof(ucOut));
           // Serial.write(ucOut, sizeof(ucOut));
            Serial.println();
            Serial.println();
            Serial.println();
            Serial.println();
            Serial.println();
            Serial.println();

            Serial.print("Printing info:");

            Serial.println(sizeof(ucOut));
            Serial.println("  , file name: ");
        //    Serial.println(myPngFileName);
            Serial.println();
            Serial.println();
            Serial.println();
            Serial.println();
            
         //   l = micros() - l;
            Serial.print(iDataSize);
            Serial.print(" bytes of data written to file in ");
       //     Serial.print((int)l);
            Serial.print(" us\n");
         }        
  } else {
    Serial.println("Failed to create PNG");
  }
}    /* end makePNG()  */










void myWifi() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    int mode=0;
    int x1 = analogRead(A1);                // read A1
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,

        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor


        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LEDG, HIGH);               // GET /H turns the LED on
          mode=1;
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LEDG, LOW);                // GET /L turns the LED off
            mode=2;
        }

        if (currentLine.endsWith("GET /P")) {
          mode=3;         
          digitalWrite(LEDB, LOW); 
          }
        if (currentLine.endsWith("GET /R")) {
         digitalWrite(LEDB, HIGH); 
         // don't really do anything
         mode=4;
        }

        
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
            client.print("<input type=button value='LED_BUILTIN Off' onclick='{location=\"/H\"}'>");
            client.print("<input type=button value='LED_BUILTIN On' onclick='{location=\"/L\"}'>");
            
            client.print("<input type=button value='Take Picture' onclick='{location=\"/P\"}'>");
            client.print("<input type=button value='Reset Page' onclick='{location=\"/R\"}'>");
            client.print("<br> AnalogRead(A1); = "+ String(x1)+"<br>" );  


    
             if (mode == 1) {
                 client.print(F("<img src=\"data:image/png;base64,R0lGODdhAQABAPAAAP8AAAAAACwAAAAAAQABAAACAkQBADs=\" />"));
    
             }
    
             if (mode == 2) {
                String cool1 = "R0lGODdhAQABAPAAAP8AAAAAACwAAAAAAQABAAACAkQBADs=";
                client.print("<img src=\"data:image/png;base64," + cool1 + "\" />");
   
             }
    
             if (mode == 3) {
                makePNG();
               
                size_t rawLength = iDataSize;

               // char encoded[BASE64::encodeLength(rawLength)];
               // BASE64::encode((const uint8_t*)ucOut, rawLength, encoded);
                BASE64::encode((const uint8_t*)ucOut, rawLength, ucBase64);
                
      
                client.print(F("<img src=\"data:image/png;base64,"));
               // client.write( (const char *)ucOut, iDataSize);      
                client.write( (const char *)ucBase64, BASE64::encodeLength(rawLength)-1);      
                client.print(F("\" />"));    
  
              }
    
             if (mode == 4) {
        
             }

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


void loop(){
   myWifi();
}
