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

#if !( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )
  #error For Portenta_H7 only
#endif

//#define _PORTENTA_H7_AWS_LOGLEVEL_     1

#define USE_WIFI_PORTENTA_H7        true

#include <WiFi.h>
#warning Using WiFi for Portenta_H7.

#include <Portenta_H7_AsyncWebServer.h>

char ssid[] = "yourSSID";        // your network SSID (name)
char pass[] = "yourPASSWORD";         // your network password (use for WPA, or use as key for WEP), length must be 8+

int status = WL_IDLE_STATUS;

AsyncWebServer    server(80);

int reqCount = 0;                // number of requests received

#define LED_OFF             HIGH
#define LED_ON              LOW


#define BUFFER_SIZE         512
char temp[BUFFER_SIZE];

void myServeWebpage(AsyncWebServerRequest *request){

  int x1 = analogRead(A1);  
 // digitalWrite(LEDG, LED_ON);

  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  int day = hr / 24;

  snprintf(temp, BUFFER_SIZE - 1,
           "<html>\
<head>\
<meta http-equiv='refresh' content='30'/>\
<title>AsyncWebServer-%s</title>\
<style>\
body { background-color: #cccccc; Color: #000088; }\
</style>\
</head>\
<body>\
<h2>AsyncWebServer_Portenta_H7!</h2>\
<h3>running WiFi on %s</h3>\
<p>Page Views: %d</p>\
<p>Uptime: %d day(s) %02d:%02d:%02d</p>\
<p><input type=button value='LEDB Blue LED Off' onclick='{location=\"/H\"}'></p>\
<p><input type=button value='LEDB Blue LED On' onclick='{location=\"/L\"}'></p>\
<p><br> AnalogRead(A1): = %d </p>\
<p></p>\
<p></p>\
</body>\
</html>", BOARD_NAME, BOARD_NAME, reqCount, day, hr % 24, min % 60, sec % 60, x1);   

  request->send(200, "text/html", temp);

}





void printWifiStatus(){

  Serial.println("SSID: " + String(WiFi.SSID()) );

  // IPAddress ip = WiFi.localIP();
  Serial.println("Local IP Address: " + String(WiFi.localIP()) );

  // long rssi = WiFi.RSSI();
  Serial.println("signal strength (RSSI):" + String(WiFi.RSSI()) + " dBm");

}

void setup()
{
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  digitalWrite(LEDR, HIGH); // internal LED HIGH is odd, weird!
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);

  Serial.begin(115200);
  //while (!Serial);   // this blocks, better to just wait below

  delay(5000);
  Serial.println("3, serial monitor on?" );
  delay(5000);
  Serial.println("2, serial monitor on?" );
  delay(5000);
  Serial.println("1, serial monitor on?" );

  Serial.println("Start Async_AdvancedWebServer on " + String(BOARD_NAME)+ " with " + String(SHIELD_TYPE) );
  Serial.println("PORTENTA_H7_ASYNC_TCP_VERSION: " + String(PORTENTA_H7_ASYNC_TCP_VERSION));
  Serial.println("PORTENTA_H7_ASYNC_WEBSERVER_VERSION: " + String(PORTENTA_H7_ASYNC_WEBSERVER_VERSION) );

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
    delay(500);       
    // Connect to WPA/WPA2 network
    status = WiFi.status();
    digitalWrite(LEDG, HIGH);
  }

  printWifiStatus();

  ///////////////////////////////////


  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request){
    reqCount += 1;
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

  //server.onNotFound(handleNotFound);

  server.begin();
  
  Serial.print(F("HTTP EthernetWebServer is @ IP : "));
  Serial.println(WiFi.localIP());
}




void loop(){

}
