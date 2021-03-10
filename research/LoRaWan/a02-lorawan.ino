/*
* Lorawan continuous attempt to connect
* by @Rocksetta
* March 1st, 2021
* 
* Assumes you have done the MKRWANFWUpdate_standalone for your zone 
* US915_HYBRID
* 
*/

#include <MKRWAN.h>

LoRaModem modem;


//#include "arduino_secrets.h"
// Best to use an arduino_secrets.h file but easier here


String appEui = "0000000000000000";    // you can leave this as it is
String appKey = "11111111111111111111111111111";  // you have to change this

void setup() {
    
   pinMode(LEDR, OUTPUT);
   pinMode(LEDG, OUTPUT);
   pinMode(LEDB, OUTPUT);
   digitalWrite(LEDR, LOW);  // high off for new boards
   digitalWrite(LEDG, LOW);  
   digitalWrite(LEDB, LOW);  
   delay(10000);   // just to give time to load serial monitor
   digitalWrite(LEDR, HIGH);  // high off for new boards
   digitalWrite(LEDG, HIGH);  
   digitalWrite(LEDB, HIGH);  

  
  Serial.begin(115200);
  //while (!Serial); // we want this to run on USB charger
  
  // change this to your regional band (eg. US915, US915_HYBRID, EU868, AS923, ...)
  if (!modem.begin(US915)) {
    Serial.println("Failed to start module");
    digitalWrite(LEDR, LOW);  // high off for new boards
    digitalWrite(LEDG, HIGH);  
    digitalWrite(LEDB, HIGH);  
    while (1) {}
  };
  delay(5000);
    // For North American basic connections

  
  Serial.println("Your module version is: " + String(modem.version()) );
  Serial.println("Your device EUI is: " + String(modem.deviceEUI()) );
  Serial.println("getDataRate: " + String(modem.getDataRate()) );


  bool connected = false;
  while (connected == false) {
      digitalWrite(LEDR, HIGH);  // high off for new boards
      digitalWrite(LEDG, HIGH);  
      digitalWrite(LEDB, LOW); 
     Serial.println("[LoRaWan] Joining network...");
     connected = modem.joinOTAA(appEui, appKey);
     if (connected) {
         digitalWrite(LEDR, HIGH);  // high off for new boards
         digitalWrite(LEDG, LOW);  
         digitalWrite(LEDB, HIGH);  
         Serial.println("[LoRaWan] Joined network! " + String(connected));
     } else {
        digitalWrite(LEDR, HIGH);  // high off for new boards
        digitalWrite(LEDG, HIGH);  
        digitalWrite(LEDB, HIGH);  
        Serial.println("[LoRaWan] Joining network failed, retrying in 3 seconds... "+ String(connected));
     }
     delay(3000);
  }
  
  // For North American basic connections

  Serial.println("getDevAddr: " + String(modem.getDevAddr()) );
  Serial.println("getNwkSKey: " + String(modem.getNwkSKey()) );
  Serial.println("getAppSKey: " + String(modem.getAppSKey()) );


  
}

void loop() {
  Serial.println();
  Serial.println("Enter a message to send to network");
  Serial.println("(make sure that end-of-line 'NL' is enabled)");

  while (!Serial.available());
  String msg = Serial.readStringUntil('\n');

  Serial.println();
  Serial.print("Sending: " + msg + " - ");
  for (unsigned int i = 0; i < msg.length(); i++) {
    Serial.print(msg[i] >> 4, HEX);
    Serial.print(msg[i] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();

  int err;
  modem.beginPacket();
  modem.print(msg);
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
  digitalWrite(LEDR, HIGH);  // high off for new boards
  digitalWrite(LEDG, HIGH);  
  digitalWrite(LEDB, HIGH);  
  delay(1000);
  digitalWrite(LEDR, HIGH);  // high off for new boards
  digitalWrite(LEDG, LOW);  
  digitalWrite(LEDB, HIGH);  
  if (!modem.available()) {
    Serial.println("No downlink message received at this time.");
    digitalWrite(LEDR, HIGH);  // high off for new boards
    digitalWrite(LEDG, HIGH);  
    digitalWrite(LEDB, LOW);  
    delay(1000);
    digitalWrite(LEDR, HIGH);  // high off for new boards
    digitalWrite(LEDG, LOW);  
    digitalWrite(LEDB, HIGH);  
    return;
  }
  char rcv[64];
  int i = 0;
  while (modem.available()) {
    rcv[i++] = (char)modem.read();
  }
  Serial.print("Received: ");
  for (unsigned int j = 0; j < i; j++) {
    Serial.print(rcv[j] >> 4, HEX);
    Serial.print(rcv[j] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();
  //  delay(60000);
}
