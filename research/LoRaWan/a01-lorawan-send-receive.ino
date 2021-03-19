/*
  Lora Send And Receive
  This sketch demonstrates how to send and receive data with the MKR WAN 1300/1310 LoRa module.
  This example code is in the public domain.
*/

#include <MKRWAN.h>

LoRaModem modem;

////////////  Set this either true = reciever or false = sender
bool myReceiver = false;  // set to false to send message
bool myExitSendLoop = false;
String inString = "";
int val = 0;


void myPrintMask(){
 
  Serial.println("-------------------------------");
  Serial.println("Your module version is: " + String(modem.version()) );
  Serial.println("getDataRate: " + String(modem.getDataRate()) );
  Serial.println("getADR: " + String(modem.getADR()) );
  Serial.println("getRX2Freq: " + String(modem.getRX2Freq()) );
  Serial.println("getRX2DR(): " + String(modem.getRX2DR()) );
   
  Serial.println("getDevAddr: " + String(modem.getDevAddr()) );
  Serial.println("getNwkSKey: " + String(modem.getNwkSKey()) );
  Serial.println("getAppSKey: " + String(modem.getAppSKey()) );
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
  //while (!Serial); //allow start without serial
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(US915)) {
    Serial.println("Failed to start module");
    while (1) {}
  };

  myPrintMask(); 
  
  Serial.println("Now Disabling all channels and enable channel 2 ");
  modem.disableChannel(0);
  modem.disableChannel(1);
  modem.enableChannel(2);
  modem.disableChannel(3);
  modem.disableChannel(4);
  modem.disableChannel(5);
  modem.disableChannel(6);

  modem.setPort(10);
  modem.dataRate(1);
  modem.setADR(false);
  
  myPrintMask(); 

 // modem.minPollInterval(10);

}

void loop() {
  myExitSendLoop = false;
  delay(20000);
  myPrintMask();
 
  if (myReceiver){

    
////// all receiver code here
    Serial.println("This code is the receiver!");
    int packetSize = modem.parsePacket();
    if (packetSize){
         while (modem.available()) {
             int inChar = modem.read();
             inString += (char)inChar;
             val = inString.toInt(); 
          }
          inString = ""; 
          
      }
      Serial.println("Received message: ");
      Serial.println(val);
    } else {

////// all sender code here
  delay(5000);      
  Serial.println("This is the sender code activated");
  //Serial.println("Enter a message to send to network");
 // Serial.println("(make sure that end-of-line 'NL' is enabled)");

 // while (!Serial.available());
 // String msg = Serial.readStringUntil('\n');

 // String msg = "Hello Lora\n";
  
  String msg = "231";   // program expecting numbers!

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
  delay(5000);
  if (!modem.available() || !myExitSendLoop ) {
    Serial.println("No downlink message received at this time.");
    myExitSendLoop = true;
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
  if (myExitSendLoop){
     myExitSendLoop = false;
     return;
    }
  }


}
