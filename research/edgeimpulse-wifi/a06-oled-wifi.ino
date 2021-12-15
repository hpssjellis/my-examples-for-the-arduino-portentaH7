/****************************************************************************************************************************
  Async_AdvancedWebServer.ino - Dead simple AsyncWebServer for STM32 LAN8720 or built-in LAN8742A Ethernet

  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet

  Portenta_H7_AsyncWebServer is a library for the Portenta_H7 with with Vision-Shield Ethernet

  Based on and modified from ESPAsyncWebServer (https://github.com/me-no-dev/ESPAsyncWebServer)
  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_AsyncWebServer
  Licensed under GPLv3 license

  Copyright (c) 2015, Majenko Technologies
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

  Neither the name of Majenko Technologies nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************************************************************/



/* Edge Impulse Arduino examples
 * Copyright (c) 2021 EdgeImpulse Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * 
 *  FOR the GRAYSCALE Waveshare OLED 128 x 128 using library Adafruit_SSD1327.h
 *   blue  DIN (mosi) D8
 *   yellow (sck) D9                                                                                                                                                             
 *   orange (cs) D7
 *   green (dc)  D6
 *   white (reset) not needed but D14 if you did
 *
 * another reference here 
 * https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
 *
 * Note1: Should work with any Edge Impulse model just chnage the below include to your model name
 * Note2: I simplyify my model order by always using: 0unknown, 1next, 2other, etc, etc
 */


 
/* Includes ---------------------------------------------------------------- */
#include <ei-v20unknown-1popGoRight-2waterGoLeft-3fast-v2-0-0_inferencing.h>
#include "edge-impulse-advanced.h"
#include <Adafruit_SSD1327.h>

// Used for software SPI
#define OLED_CLK D9
#define OLED_MOSI D8

// Used for software or hardware SPI
#define OLED_CS D7
#define OLED_DC D6

// Used for I2C or SPI
#define OLED_RESET -1

// hardware SPI
Adafruit_SSD1327 display(128, 128, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// Global Variables
int myDelay = 0;  // delay between readings, can be zero, default 2000 = 2 seconds
int x1Map, x2Map, y1Map, y2Map;
//int myClassCount[EI_CLASSIFIER_LABEL_COUNT]; // not yet used

// the OLED uses these
#define CUTOUT_COLS                 EI_CLASSIFIER_INPUT_WIDTH
#define CUTOUT_ROWS                 EI_CLASSIFIER_INPUT_HEIGHT
const int cutout_row_start = (EI_CAMERA_RAW_FRAME_BUFFER_ROWS - CUTOUT_ROWS) / 2;
const int cutout_col_start = (EI_CAMERA_RAW_FRAME_BUFFER_COLS - CUTOUT_COLS) / 2;

// async web server code

#if !( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )
  #error For Portenta_H7 only
#endif

#define USE_WIFI_PORTENTA_H7        true

#include <WiFi.h>
#warning Using WiFi for Portenta_H7.

#include <Portenta_H7_AsyncWebServer.h>

char ssid[] = "003-LAB217-L100 7731";        // your network SSID (name)
char pass[] = "n5(7F570";         // your network password (use for WPA, or use as key for WEP), length must be 8+


int status = WL_IDLE_STATUS;

AsyncWebServer    server(80);

int myPageCount = 0;                // number of requests received

#define BUFFER_SIZE         512
char temp[BUFFER_SIZE];





/**
* @brief      Arduino setup function
*/
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Edge Impulse Inferencing Demo");

    pinMode(LEDR, OUTPUT); 
    pinMode(LEDG, OUTPUT);   // this is LED_BUILTIN
    pinMode(LEDB, OUTPUT); 
    
#ifdef EI_CAMERA_FRAME_BUFFER_SDRAM
    // initialise the SDRAM
    SDRAM.begin(SDRAM_START_ADDRESS);
#endif

    if (ei_camera_init()) {
        Serial.println("Failed to initialize Camera!");
    }
    else {
        Serial.println("Camera initialized");
    }

    for (size_t ix = 0; ix < ei_dsp_blocks_size; ix++) {
        ei_model_dsp_t block = ei_dsp_blocks[ix];
        if (block.extract_fn == &extract_image_features) {
            ei_dsp_config_image_t config = *((ei_dsp_config_image_t*)block.config);
            int16_t channel_count = strcmp(config.channels, "Grayscale") == 0 ? 1 : 3;
            if (channel_count == 3) {
                Serial.println("WARN: You've deployed a color model, but the Arduino Portenta H7 only has a monochrome image sensor. Set your DSP block to 'Grayscale' for best performance.");
                break; // only print this once
            }
        }
    }

    //////////////////////// start OLED setup //////////////////////////////////
    // Following for the Grayscale OLED

   if ( ! display.begin(0x3D) ) {   // start Grayscale OLED
     Serial.println("Unable to initialize OLED");
     while (1) yield();
  }    
    display.setTextSize(1);
    display.setTextColor(SSD1327_WHITE);

    display.setRotation(0);
    display.setCursor(0,0);

    //   map cutout of the 320 x 320   // 240 model to OLED 128 x 64 screen
    x1Map = map((int)cutout_col_start, 0, 320, 0, 127);  
    x2Map = map((int)CUTOUT_COLS, 0, 320, 0, 127);
    y1Map = map((int)cutout_row_start, 0, 320, 0, 127);
    y2Map = map((int)CUTOUT_ROWS, 0, 320, 0, 127);


////////////////////////// end OLED setup ///////////////////////////

//////////////////////////// start async webserver setup /////////////////////////////////////

pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  digitalWrite(LEDR, HIGH); // internal LED HIGH is odd, weird!
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);

  Serial.begin(115200);
  //while (!Serial);   // this blocks, better to just wait below

  delay(5000);
  Serial.println("3, is serial monitor on?" );
  delay(5000);
  Serial.println("2, is serial monitor on?" );
  delay(5000);
  Serial.println("1, is serial monitor on?" );

  Serial.println(String(BOARD_NAME)+ " with " + String(SHIELD_TYPE) );
  Serial.println(String(PORTENTA_H7_ASYNC_TCP_VERSION));
  Serial.println(String(PORTENTA_H7_ASYNC_WEBSERVER_VERSION) );

  ///////////////////////////////////

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    
    digitalWrite(LEDR, LOW);
    while (true);
  }

  Serial.print(F("Connecting to SSID: "));
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);

  delay(1000);
   
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED){
    
    digitalWrite(LEDG, LOW);
    Serial.print(".");   
    delay(2500);    
    // Connect to WPA/WPA2 network
    status = WiFi.status();
    digitalWrite(LEDG, HIGH);
    delay(2500);       
  }

  printWifiStatus();

  ////////////////////////start async area /////////////////////////////////


// NOTE: variables and printing may not work from in these functions!!!

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request){
    myServeWebpage(request);
  });


  server.on("/inline", [](AsyncWebServerRequest * request){
    request->send(200, "text/plain", "This works as well");
  });
  
  server.on("/L", [](AsyncWebServerRequest * request){
     digitalWrite(LEDB, LOW);  // blue LED on    
     myServeWebpage(request);
  });
  
  server.on("/H", [](AsyncWebServerRequest * request){
     digitalWrite(LEDB, HIGH);  // blue LED off
     myServeWebpage(request);
  });



///////////////////////////////// end async area /////////////////////////////


  //server.onNotFound(handleNotFound);

  server.begin();
  printWifiStatus();

/////////////////////////// end asyncn webserver setup ////////////////////////////////////////////////////



}

/**
* @brief      Get data and run inferencing
*
* @param[in]  debug  Get debug info if true
*/
void loop(){
  
    // instead of wait_ms, we'll wait on the signal, this allows threads to cancel us...
    if (ei_sleep(myDelay) != EI_IMPULSE_OK) {
        return;
    }
    
    Serial.println("Starting inferencing in "+String(myDelay)+" microseconds...");

    // Put the image on the OLED
    display.clearDisplay();                 // clear the internal memory for OLED
    for (int x=0; x < EI_CAMERA_RAW_FRAME_BUFFER_COLS; x++){     // EI_CAMERA_RAW_FRAME_BUFFER_COLS = 320
      for (int y=0; y < EI_CAMERA_RAW_FRAME_BUFFER_ROWS; y++){       //EI_CAMERA_RAW_FRAME_BUFFER_ROWS = 320   //240
      
        uint8_t myGRAY = ei_camera_frame_buffer[(y * (int)EI_CAMERA_RAW_FRAME_BUFFER_COLS) + x];  

          int myGrayMap = map(myGRAY, 0, 255, 0, 15);  
          int xMap = map(x, 0, 320, 0, 127);
          int yMap = map(y, 0, 320, 0, 127);
          display.drawPixel(xMap, yMap, myGrayMap );   // grayscale 0-255, 128x128  //128 x 64
      } 
    }

    display.drawRect(2, 2,   126, 126, SSD1327_WHITE );  // rectangle around outside of OLED

    display.setCursor(20,10);
    display.println("Rocksetta");





    ei::signal_t signal;
    signal.total_length = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT;
    signal.get_data = &ei_camera_cutout_get_data;

    if (ei_camera_capture((size_t)EI_CLASSIFIER_INPUT_WIDTH, (size_t)EI_CLASSIFIER_INPUT_HEIGHT, NULL) == false) {
        Serial.println("Failed to capture image\r\n");
        return;
    }

    // Run the classifier
    ei_impulse_result_t result = { 0 };

    EI_IMPULSE_ERROR err = run_classifier(&signal, &result, debug_nn);
    if (err != EI_IMPULSE_OK) {
        Serial.println("ERR: Failed to run classifier, error number: " + String(err));
        return;
    }


    int myBestClassificationNumber = -1;  
    float myBestClassificationValue = 0.25;   // lowest best allowable value
    
    
    // print the predictions
    // Serial.println("Predictions ");
    // For complex prints best to run Edge Impulse ei_printf
    ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
        result.timing.dsp, result.timing.classification, result.timing.anomaly);
    ei_printf(": \n");
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
       // ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);

        if (result.classification[ix].value > myBestClassificationValue ){
           myBestClassificationNumber = ix;                      // find the biggest array value
           myBestClassificationValue = result.classification[ix].value;  
        }

  
    }
    
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    Serial.println("    anomaly score: " + String(result.anomaly, 5));
#endif


    digitalWrite(LEDB, HIGH);   //on board LED's are turned off by HIGH    
    digitalWrite(LEDG, HIGH);   
    digitalWrite(LEDR, HIGH); 
/*
    // I find it less confusing if the 0unknown does nothing
    if (myBestClassificationNumber == 0){    // 0 unknown do nothing
        digitalWrite(LEDB, LOW);    
        digitalWrite(LEDG, LOW);   
       // Serial.println("0 unknown: " + String(myBestClassificationValue,2));
       display.setCursor(5,110);
       display.println("0 Unknown: " + String(myBestClassificationValue,2));
    }
 */

    if (myBestClassificationNumber == 1){   // 1pop: Go Right
      digitalWrite(LEDB, LOW);              // Blue LED on
      ei_printf("1Pop Go Right: %.5f\n", myBestClassificationValue);
      display.setCursor(5,110);
      display.println("1Pop Go Right:" + String(myBestClassificationValue,2));
    }
    
    if (myBestClassificationNumber == 2){   // 2water : go left
      digitalWrite(LEDG, LOW);              // Green LED on  
      ei_printf("2Water Go Left: %.5f\n", myBestClassificationValue);
      display.setCursor(5,110);
      display.println("2Water Go Left:" + String(myBestClassificationValue,2));
    }
    
    if (myBestClassificationNumber == 3){   // 3fast got straight
      digitalWrite(LEDR, LOW);              // Red LED on         
      ei_printf("3Both Go Fast: %.5f\n", myBestClassificationValue);
      display.setCursor(5,110);
      display.println("3Both Go Fast:" + String(myBestClassificationValue,2));
    }

     // put more if statements here for your model



     // Last thing is to show the 128x128 GRAYSCALE OLED
     display.display();  // OLED 4 bit 16 color GRAYSCALE update
}



void myServeWebpage(AsyncWebServerRequest *request){
  myPageCount += 1;
  Serial.println("Main Page Loaded: " + String(myPageCount)+ " times.");
  int x1 = analogRead(A1);  


  String myTemp = "<html>\
<head>\
<meta http-equiv='refresh' content='30'/>\
<title>AsyncWebServer-%s</title>\
<style>\
body { background-color: #cccccc; Color: #000088; }\
</style>\
</head>\
<body>\
<h2>AsyncWebServer_Portenta_H7!</h2>\
<h3>running WiFi on "+String(BOARD_NAME)+"</h3>\
<p>Page Views: " + String(myPageCount)+ "</p>\
<p><input type=button value='LEDB Blue LED Off' onclick='{location=\"/H\"}'></p>\
<p><input type=button value='LEDB Blue LED On' onclick='{location=\"/L\"}'></p>\
<p><br> AnalogRead(A1): = " + String(x1)+ "</p>\
<p></p>\
<p></p>\
</body>\
</html>";


  request->send(200, "text/html", myTemp);

}






void printWifiStatus(){

  digitalWrite(LEDG, HIGH); // trun off green LED
  digitalWrite(LEDB, LOW);  // trun on blue LED
  Serial.println("SSID: " + String(WiFi.SSID()) );

  IPAddress ip = WiFi.localIP();
  Serial.print("Local IP Address: " );
  Serial.println(ip);

  // long rssi = WiFi.RSSI();
  Serial.println("signal strength (RSSI):" + String(WiFi.RSSI()) + " dBm");

}
