/*
  Helium Send And Receive
  This sketch demonstrates how to send and receive data with the MKR WAN 1300/1310 LoRa module.
  This example code is in the public domain.
  note: Helium must be setup for what it does with the CayenneLPP encoded data
*/



#include <MKRWAN.h>

int myDelay= 20000;   // non-block delay in milliseconds
unsigned long delayStart = 0; 

LoRaModem modem;
bool connected = false;

// Please enter your sensitive data in the Secret tab or arduino_secrets.h
// Note: Best to have the App_Device hard coded. Run the program once to see the value.
//#include "arduino_secrets.h"
#define SECRET_APP_EUI "55555ggggggggggg"
#define SECRET_APP_KEY "ffffffffffffff666666666fffffffff"


String appEui = SECRET_APP_EUI;   // just strings of the above 
String appKey = SECRET_APP_KEY;





void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delayStart = millis();   // set delay
  pinMode(LEDR,OUTPUT);
  pinMode(LEDG,OUTPUT);
  pinMode(LEDB,OUTPUT);
  digitalWrite(LEDR, HIGH); // new boards HIGH = off
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
  
  //while (!Serial);       // don't wait for serial
  
  Serial.println("Wait 4");
  delay(3000);             // delay instead, so it works when disconnected
  digitalWrite(LEDG, HIGH);// allows time to connect serial monitor

  Serial.println("Wait 3");
  delay(3000);       
  digitalWrite(LEDG, LOW);
 
  Serial.println("Wait 2");
  delay(3000);       
  digitalWrite(LEDG, HIGH);

  Serial.println("Wait 1");
  delay(3000);       
  digitalWrite(LEDG, LOW);



  
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(US915)) {
    Serial.println("Failed to start module");
    while (1) {}
  };

  
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());


  Serial.println("Now Disabling all channels and enable channel 1 only for Helium ");

  modem.disableChannel(0);
  modem.enableChannel(1);    // only one enabled for Helium
  modem.disableChannel(2);
  modem.disableChannel(3);
  modem.disableChannel(4);
  modem.disableChannel(5);
  modem.disableChannel(6);

  Serial.println("Now Joining the Helium Network ");


 
}

void loop() {


  char rcv[64];
  int i = 0;
  int myIncomingData = false;
  
  while (modem.available()) {
    rcv[i++] = (char)modem.read();
    myIncomingData = true;
  }
  // Only print if data incoming
  if (myIncomingData){
      Serial.print("Received: ");
      for (unsigned int j = 0; j < i; j++) {
        Serial.print(rcv[j] >> 4, HEX);
        Serial.print(rcv[j] & 0xF, HEX);
        Serial.print(" ");
      }
      Serial.println();
      digitalWrite(LEDR, HIGH); // new boards HIGH = off
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDB, LOW);
  }




  if ( (millis() - delayStart ) >= myDelay) {       
    delayStart = millis(); //  reset the delay time

    while (!connected) {
      Serial.println("trying to reconnect");
      digitalWrite(LEDR, LOW); // new boards HIGH = off
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDB, HIGH);
      connected = modem.joinOTAA(appEui, appKey);
      delay(5000);    
      digitalWrite(LEDR, HIGH); // new boards HIGH = off
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDB, HIGH);
      delay(1000);
    }


// THE STRING TO SEND: 5 LETTERS and 5 NUMBERS 
// can be any 10 bytes but this is human readable
// String msg = "ABCDE12345";
   String msg = "Snack34567";


    Serial.println();
    Serial.print("Sending: " + msg + " - ");
  
     // This for loop just shows the base64 encoding of what gets sent
    for (unsigned int i = 0; i < msg.length(); i++) {
      Serial.print(msg[i] >> 4, HEX);
      Serial.print(msg[i] & 0xF, HEX);
      Serial.print(" ");
    }
    Serial.println();
  
    int myErrorOrBytesSent;
    modem.beginPacket();
    modem.print(msg);
    myErrorOrBytesSent = modem.endPacket(true);



  /*
   * 
   * myErrorOrBytesSent =  int a positive number indicate success and is the number of bytes transmitted
   *             -1 indicates a timeout error
   *             -2 indicates LORA_ERROR
   *             -3 indicates LORA_ERROR_PARAM
   *             -4 indicates LORA_ERROR_BUSY
   *             -5 indicates LORA_ERROR_OVERFLOW
   *             -6 indicates LORA_ERROR_NO_NETWORK
   *             -7 indicates LORA_ERROR_RX
   *             -8 indicates LORA_ERROR_UNKNOWN
   *             -20 packet exceeds max length
   * 
   */
  
    
    if (myErrorOrBytesSent > 0) {
      Serial.println("Message sent correctly! Length in bytes : " + String(myErrorOrBytesSent));
      digitalWrite(LEDR, HIGH); // new boards HIGH = off
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, LOW);
    } else {
      Serial.println("Error sending message : Error #" + String(myErrorOrBytesSent) );
      digitalWrite(LEDR, LOW); // new boards HIGH = off
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, LOW);
    }
  
  
    // Why do we only activate downlink messages after a send message????
    // Is this delay here bad after sending a message
    // perhaps a timer here
    delay(3000);
    if (!modem.available()) {
      Serial.println("No downlink message received at this time.");
      return;
    }
 
  } // end timer
}  // end main loop



