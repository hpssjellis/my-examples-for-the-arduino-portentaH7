
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
   String myTemp = "";
   for (int i = 0; i < LoRaRadio.parsePacket(); i++) {
       myTemp += (char)LoRaRadio.read();
   } 
   Serial.println(myTemp);

   
   Serial.println("Now Sending the same packet");
   LoRaRadio.beginPacket();
   for (int j = 0; j < myTemp.length(); j++) {
       LoRaRadio.write((char)myTemp[j]);
   } 
   LoRaRadio.endPacket();      
   Serial.println("Same packet sent");
  
  // LoRaRadio.receive(0);  // not sure if we have to call this again.  test
}

