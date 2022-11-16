
// might use javascript    bitmap.image.toString('base64')

//    https://www.nayuki.io/page/png-file-chunk-inspector  

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


FrameBuffer fb;

unsigned long lastUpdate = 0;


#include <PNGenc.h>

PNG png; // static instance of the PNG encoder class


#define WIDTH 128
#define HEIGHT 128

uint8_t ucPal[768] = {0,0,0,0,255,0}; // black, green
uint8_t ucAlphaPal[256] = {0,255}; // first color (black) is fully transparent
uint8_t ucOut[4096];
uint8_t ucLine[WIDTH];

void blinkLED(uint32_t count = 0xFFFFFFFF)
{
  pinMode(LED_BUILTIN, OUTPUT);
  while (count--) {
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED off by making the voltage LOW
    delay(50);                       // wait for a second
  }
}



void setup() {
int rc, iDataSize, x, y;
long l;
    // Init the cam QVGA, 30FPS
  if (!cam.begin(CAMERA_R320x240, IMAGE_MODE, 30)) {     //CAMERA_R160x120    CAMERA_R320x240
    blinkLED();
  }

  blinkLED(5);



  /****  COMMUNICATION  ****/
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
            iDataSize = png.close();
            l = micros() - l;
           // Serial.printf("%d bytes of data written to file in %d us\n", iDataSize, (int)l);
            Serial.print(iDataSize);
            Serial.print(" bytes of data written to file in ");
            Serial.print( (int)l );
            Serial.print(" us\n");
        }
  } else {
    Serial.println("Failed to create the file on the SD card!");
  }




  
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

            
          if (cam.grabFrame(fb, 3000) == 0) {
            Serial.write(fb.getBuffer(), cam.frameSize());
          } else {
            blinkLED(20);
          }



          
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
       // client.print("<input type=button value='Stop Recording Data' onclick='{location=\"/WOFF\"}'>");
       
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

        /*
        for (k = 0; k <= j - 1; k++)
        {
          client.print(a[k]); client.print(",");
          client.print(b[k]); client.print(",");
          client.println(c[k]);
       }
   */
        int k;
        for (k = 0; k <= 20; k++){
          client.print(ucOut[k]); client.print(",");
       }




  // ucOut

   
       // client.write(fb.getBuffer(), cam.frameSize());
       
        //client.write(ucOut, sizeof(ucOut));
        // client.print(ucOut);
        //client.write(png, sizeof(png));
       // client.write(ucPal, sizeof(ucPal));
       //      Serial.printf("image specs: (%d x %d), %d bpp, pixel type: %d\n", png.getWidth(), png.getHeight(), png.getBpp(), png.getPixelType());
   /*
         client.print(", png.getWidth(): "); 
        client.print(png.getWidth());      
        client.print(", png.getHeight(): "); 
        client.print(png.getHeight());
        client.print(", png.getBpp(): "); 
        client.print(png.getBpp());
        client.print(", png.getPixelType(): "); 
        client.print(png.getPixelType());

        */
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
    mode=1;
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
