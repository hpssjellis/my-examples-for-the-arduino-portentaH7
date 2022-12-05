/*
*  WiFi PNG web save
*  By Jeremy Ellis
*
*/






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





// don't forget to set the ucOut[] to be able to handle the PNG image size
#define PNG_WIDTH 16     //320  //160  96
#define PNG_HEIGHT 16    // 320 // 120  96

// don't forget to setup the camera with the correct resolution
#define CAM_WIDTH 320
#define CAM_HEIGHT 320


FrameBuffer fb;

// could use heap or Portenta SDRAM
static uint8_t frame_buffer[CAM_WIDTH*CAM_HEIGHT] __attribute__((aligned(32)));
//static uint8_t frame_buffer[160*120] __attribute__((aligned(32)));





// Settings for our setup
#define IMAGE_HEIGHT (unsigned int)CAM_WIDTH  //      240
#define IMAGE_WIDTH (unsigned int)CAM_HEIGHT  //    320
#define IMAGE_MODE CAMERA_GRAYSCALE
#define BITS_PER_PIXEL (unsigned int)8
#define PALETTE_COLORS_AMOUNT (unsigned int)(pow(2, BITS_PER_PIXEL))
#define PALETTE_SIZE  (unsigned int)(PALETTE_COLORS_AMOUNT * 4) // 4 bytes = 32bit per color (3 bytes RGB and 1 byte 0x00)
//#define IMAGE_PATH "/fs/image.bmp"

// Headers info
#define BITMAP_FILE_HEADER_SIZE (unsigned int)14 // For storing general information about the bitmap image file
#define DIB_HEADER_SIZE (unsigned int)40 // For storing information about the image and define the pixel format
#define HEADER_SIZE (BITMAP_FILE_HEADER_SIZE + DIB_HEADER_SIZE)

//   unsigned char *imageData;   //??????????????????????????? might be important












//int iDataSize;





         

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
            client.print("<input type=button value='LED_BUILTIN Off' onclick='{location=\"/H\"}'>\n");
            client.print("<input type=button value='LED_BUILTIN On' onclick='{location=\"/L\"}'>\n");
            
            client.print("<input type=button value='Take Picture' onclick='{location=\"/P\"}'>\n");
            client.print("<input type=button value='Reset Page' onclick='{location=\"/R\"}'>\n");
            client.print("<br> AnalogRead(A1); = "+ String(x1)+"<br>\n" );  

    
             if (mode == 1) {
                 client.print("<img src=\"data:image/png;base64,R0lGODdhAQABAPAAAP8AAAAAACwAAAAAAQABAAACAkQBADs=\" />");
    
             }
    
             if (mode == 2) {
                String cool1 = "R0lGODdhAQABAPAAAP8AAAAAACwAAAAAAQABAAACAkQBADs=";
                client.print("<img src=\"data:image/png;base64," + cool1 + "\" />");
   
             }
    
             if (mode == 3) {

         
               client.print("<input type=button value=now onclick=\"{\nlet myFile=new File([" );       

///////////////////////////////////////////////////////////////////////////////////////

    int fileSize = BITMAP_FILE_HEADER_SIZE + DIB_HEADER_SIZE + IMAGE_WIDTH * IMAGE_HEIGHT;


    // Bitmap structure (Head + DIB Head + ColorMap + binary image)
    unsigned char bitmapFileHeader[BITMAP_FILE_HEADER_SIZE];
    unsigned char bitmapDIBHeader[DIB_HEADER_SIZE];
    unsigned char colorMap[PALETTE_SIZE]; // Needed for <= 8bpp grayscale bitmaps    

    setFileHeaders(bitmapFileHeader, bitmapDIBHeader, fileSize);
    setColorMap(colorMap);

    // Write the bitmap file
   client.write( bitmapFileHeader, BITMAP_FILE_HEADER_SIZE);
   client.write(bitmapFileHeader, BITMAP_FILE_HEADER_SIZE);
   client.write(bitmapDIBHeader, DIB_HEADER_SIZE);
   client.write(colorMap, PALETTE_SIZE);
  // client.write(imageData, IMAGE_HEIGHT * IMAGE_WIDTH);






/////////////////////////////////////////////////////////////////////////////////////// 




               client.print("],'myinfo.bmp',{type:'image/bmp'});\nlet myUrl = webkitURL.createObjectURL(myFile);\nlet a = document.createElement('a');\na.href=myUrl;\n" );
               client.print("a.download=myFile.name;\na.textContent=`Download ${myFile.name}`;\ndocument.getElementById('myDiv01').append(a);\n}\">\n<div id=\"myDiv01\">...</div>\n" );  
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





void loop(){
   myWifi();
}
