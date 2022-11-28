#include "SDMMCBlockDevice.h" // Multi Media Card APIs
#include "FATFileSystem.h"    // API to run operations on a FAT file system
SDMMCBlockDevice blockDevice;
mbed::FATFileSystem fileSystem("fs");
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

unsigned char *imageData;



// might use javascript    bitmap.image.toString('base64')

//    https://www.nayuki.io/page/png-file-chunk-inspector  



// thi sis a red dot

//R0lGODdhAQABAPAAAP8AAAAAACwAAAAAAQABAAACAkQBADs=



#include <WiFi.h>

char ssid[] = "";    // your network SSID (name)
char pass[] = "";   // your network password (use for WPA, or use as key for WEP)


int keyIndex = 0;             // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
WiFiServer server(80);



unsigned long timezero, timefin;

/**************ORDERS*******/
int mode = 0;
int pause;













void setup(){
    Serial.begin(115200);
  Serial.begin(115200);
  delay(5000);
  Serial.println("15 second delay to attach Serial monitor, if you want");
  delay(5000);
  Serial.println("10 second delay to attach Serial monitor, if you want");
  delay(5000);
  Serial.println("5 second delay to attach Serial monitor, if you want");
  delay(5000);
  Serial.println("Now starting");
  //while (!Serial);  // don't do this or it does not work when Serial is disconnected


    
    Serial.println("Mounting SD Card...");
    mountSDCard();
    Serial.println("SD Card mounted.");

    // Init the cam QVGA, 30FPS, Grayscale
    if (!cam.begin(CAMERA_R320x240, IMAGE_MODE, 30)){
        Serial.println("Unable to find the camera");
    }
    countDownBlink();
    Serial.println("Fetching camera image...");
   // unsigned char *imageData = captureImage();
    imageData = captureImage();
    digitalWrite(LEDB, HIGH);
    
    Serial.println("Saving image to SD card...");
    saveImage(imageData, IMAGE_PATH);
    
    fileSystem.unmount();
    Serial.println("Done. You can now remove the SD card.");

/****  SETUP WIFI  ****/
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDR, HIGH);
  // by default the local IP address of will be 192.168.3.1
  // you can override it with the following:
  // WiFi.config(IPAddress(10, 0, 0, 1));
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 4 seconds for connection:
    delay(4000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();




}

void loop() {

  // compare the previous status to the current status
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }

WiFiClient client = server.available();   // listen for incoming clients

  if (client)
  { // if you get a client,
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      { // if there's bytes to read from the client,

        String currentLine = client.readStringUntil('\n');

        if (currentLine.indexOf("GET /WON") > -1)
        {
          digitalWrite(LEDR, HIGH);
          digitalWrite(LEDG, HIGH);
          digitalWrite(LEDB, LOW);
          Serial.println("ON");
          //client.println("ON");
          timezero = millis();
          mode = 1;



          
        }
        else if (currentLine.indexOf("GET /WOFF") > -1)
        {
          digitalWrite(LEDR, HIGH);
          digitalWrite(LEDG, HIGH);
          digitalWrite(LEDB, HIGH);
          Serial.println("OFF");
          //client.println("OFF");
          mode = 2;
          timefin = millis();
        }
 

        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        client.print("<input type=button value='Take one picture' onclick='{location=\"/WON\"}'>");
        client.print("<input type=button value='Reset' onclick='{location=\"/\"}'>");
       
        client.print(F("<html>\n"));
        client.print(F("<head>\n"));
        client.print(F("<script>\n"));
        client.print(F("function saveFileAs() {\n"));
        client.print(F("var myFilename01 = document.getElementById('myText01').value + '.txt';\n"));
        client.print(F("var myTextBlob = new Blob([document.getElementById('myTextArea01').value], {type:'text/plain'});\n"));
        client.print(F("var myDownloadLink = document.createElement('a');\n"));
        client.print(F("myDownloadLink.download = myFilename01;\n"));
        client.print(F("myDownloadLink.innerHTML = 'Download File';\n"));
        client.print(F("myDownloadLink.href = window.URL.createObjectURL(myTextBlob);\n"));
        client.print(F("myDownloadLink.click();\n"));
        client.print(F("delete myDownloadLink;\n"));
        client.print(F("delete myTextBlob;\n"));
        client.print(F("}\n"));
        client.print(F("</script>\n"));
        client.print(F("</head>\n"));
        client.print(F("<body>\n"));
        client.print(F("<form id=\"myForm01\" target=\"_blank\" method=\"POST\"><br>\n"));
        client.print(F("FileName: <input type=text id=\"myText01\" value=\"test1\">.txt<br>\n"));
        client.print(F("<textarea id=\"myTextArea01\" rows=5 cols=70 >\n"));



        //  saveToClient(imageData, client);


        

        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, HIGH);
        
        client.print(F("</textarea><br>\n"));
        client.print(F("<input type=button value=\"Save image as web downloaded text file\" onclick=\"{saveFileAs();}\">\n<br>"));
        client.print(F("<input type=button value=\"From Text to Base64 Image\" onclick=\"{document.getElementById('myImage01').src = 'data:image/png;base64,'+document.getElementById('myTextArea01').value}\">\n"));
        client.print(F("<img id=\"myImage01\" src=\"\">\n"));

                
        client.print(F("</form>\n"));
        client.print(F("</body>\n"));
        client.print(F("</html>\n"));
        
        // Svuota il myarray in ricezione di client.
        while (client.available()) client.read();
        client.flush();
        break;
      } // end if (client.available())
    } // end while (client.connected())
    client.stop();
  
  } // end if (client)



 

} //end loop


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

// Mount File system block
void mountSDCard(){
    int error = fileSystem.mount(&blockDevice);
    if (error){
        Serial.println("Trying to reformat...");
        int formattingError = fileSystem.reformat(&blockDevice);
        if (formattingError) {            
            Serial.println("No SD Card found");
            while (1);
        }
    }
}

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


void saveToClient(unsigned char *imageData, WiFiClient  client){
    int fileSize = BITMAP_FILE_HEADER_SIZE + DIB_HEADER_SIZE + IMAGE_WIDTH * IMAGE_HEIGHT;

    // Bitmap structure (Head + DIB Head + ColorMap + binary image)
    unsigned char bitmapFileHeader[BITMAP_FILE_HEADER_SIZE];
    unsigned char bitmapDIBHeader[DIB_HEADER_SIZE];
    unsigned char colorMap[PALETTE_SIZE]; // Needed for <= 8bpp grayscale bitmaps    

    setFileHeaders(bitmapFileHeader, bitmapDIBHeader, fileSize);
    setColorMap(colorMap);

    // Write the bitmap file
    client.write(bitmapFileHeader, BITMAP_FILE_HEADER_SIZE);
    client.write(bitmapDIBHeader, DIB_HEADER_SIZE);
    client.write(colorMap, PALETTE_SIZE);
    client.write(imageData, IMAGE_HEIGHT * IMAGE_WIDTH);

    // Close the file stream
   // fclose(file);
}


void countDownBlink(){
    for (int i = 0; i < 6; i++){
        digitalWrite(LEDG, i % 2);
        delay(500);
    }
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, LOW);
}
