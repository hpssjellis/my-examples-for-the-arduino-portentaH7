
#include "LoRaRadio.h"

static void myReceive(void);



void setup( void ){
    Serial.begin(9600);
    
    while (!Serial) { }   // non-blocking for the murata module on the Portenta

    LoRaRadio.begin(915000000);

    LoRaRadio.setFrequency(915000000);
    LoRaRadio.setTxPower(1);    //default 14
    LoRaRadio.setBandwidth(LoRaRadio.BW_125);
    LoRaRadio.setSpreadingFactor(LoRaRadio.SF_7);
    LoRaRadio.setCodingRate(LoRaRadio.CR_4_5);
    LoRaRadio.setLnaBoost(true);
  
    LoRaRadio.onReceive(myReceive);  // just telling it about the callback 
    LoRaRadio.receive(0);            // is zero infinite, other upto milliseconds

}





void loop( void ){

}





static void myReceive(void){
  
   Serial.println("Incoming");
   int myIncoming = LoRaRadio.parsePacket();
   Serial.println("LoRaRadio.parsePacket(): "+String( myIncoming ) );

  char myInArray[64];
  

  while (LoRaRadio.available()) {
    myInArray[myIncoming++] = (char)LoRaRadio.read();
  }
  Serial.print("Received: ");
  for (unsigned int j = 0; j < myIncoming; j++) {
    Serial.print(myInArray[j] >> 4, HEX);
    Serial.print(myInArray[j] & 0xF, HEX);
  }
   //Serial.print(myInArray);
  

   Serial.println("");

  
  // LoRaRadio.receive(0);  // not sure if we have to call this again.  test
}






/*

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

*/

