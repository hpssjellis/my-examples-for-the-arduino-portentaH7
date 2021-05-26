/*
  Lora Send And Receive
  This sketch demonstrates how to send and receive data with the MKR WAN 1300/1310 LoRa module.
  This example code is in the public domain.
*/

#include <MKRWAN.h>
#include <CayenneLPP.h>


LoRaModem modem;
CayenneLPP lpp(51);

// Uncomment if using the Murata chip as a module
// LoRaModem modem(Serial1);

//#include "arduino_secrets.h"
//#define SECRET_APP_EUI "000"
//#define SECRET_APP_KEY "00000000"

// Please enter your sensitive data in the Secret tab or arduino_secrets.h
//String appEui = SECRET_APP_EUI;
//String appKey = SECRET_APP_KEY;

String appEui = "000000000000000";
String appKey = "0000000000000000000000000";


void myPrintMask(){
 
  Serial.println("Your module version is: " + String(modem.version()) );
  Serial.println("getDataRate: " + String(modem.getDataRate()) );
  Serial.println("getADR: " + String(modem.getADR()) );
  Serial.println("getRX2Freq: " + String(modem.getRX2Freq()) );
  Serial.println("getRX2DR(): " + String(modem.getRX2DR()) );
   
  Serial.println("getFCU: " + String(modem.getFCU()) );
  Serial.println("getFCD: " + String(modem.getFCD()) );
  Serial.println("getChannelMask: " + String(modem.getChannelMask()));
  
  Serial.println("isChannelEnabled(0): " + String(modem.isChannelEnabled(0)));
  Serial.println("isChannelEnabled(1): " + String(modem.isChannelEnabled(1)));
  Serial.println("isChannelEnabled(2): " + String(modem.isChannelEnabled(2)));
  Serial.println("isChannelEnabled(3): " + String(modem.isChannelEnabled(3)));
  Serial.println("isChannelEnabled(4): " + String(modem.isChannelEnabled(4)));
  Serial.println("isChannelEnabled(5): " + String(modem.isChannelEnabled(5)));
  Serial.println("isChannelEnabled(6): " + String(modem.isChannelEnabled(6)));
  Serial.println("-------------------------------");
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  
  //while (!Serial); // don't wait for serial
  delay(20000);  // delay instead, so it works when disconnected
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(US915)) {
    Serial.println("Failed to start module");
    while (1) {}
  };


  
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  myPrintMask();
  delay(3000);
  Serial.println("Now Disabling all channels and enable channel 0 only ");

  modem.disableChannel(0);
  modem.enableChannel(1);
  modem.disableChannel(2);
  modem.disableChannel(3);
  modem.disableChannel(4);
  modem.disableChannel(5);
  modem.disableChannel(6);
  myPrintMask(); 


  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }
  
  myPrintMask(); 

  // Set poll interval to 60 secs.
  //modem.minPollInterval(60);
  // NOTE: independent of this setting, the modem will
  // not allow sending more than one message every 2 minutes,
  // this is enforced by firmware and can not be changed.
}

void loop() {

  lpp.reset();
  float x = rand() / 10000000.0; 
  lpp.addTemperature(1, x); //analogRead(A0)

   

  
  Serial.println();
  Serial.println("Sending:" + String(x, 1));
 // Serial.println("Enter a message to send to network");
 // Serial.println("(make sure that end-of-line 'NL' is enabled)");

/*

// good for reading from serial
 // while (!Serial.available());
  //String msg = Serial.readStringUntil('\n');


  Serial.println();
  Serial.print("Sending: " + msg + " - ");
  for (unsigned int i = 0; i < msg.length(); i++) {
    Serial.print(msg[i] >> 4, HEX);
    Serial.print(msg[i] & 0xF, HEX);
    Serial.print(" ");
  }

*/
  
  Serial.println();

  int err;
  modem.beginPacket();
  modem.write(lpp.getBuffer(), lpp.getSize());
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
  delay(1000);
  if (!modem.available()) {
    Serial.println("No downlink message received at this time.");
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
  delay(30000);  // delay 30 seconds for testing
}
