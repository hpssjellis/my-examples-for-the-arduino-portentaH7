
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

   for (int i = 0; i < LoRaRadio.parsePacket(); i++) {
        Serial.print((char)LoRaRadio.read());
   } 
   Serial.println("");
   Serial.println("Now Sending");
       LoRaRadio.beginPacket();
       LoRaRadio.write('P');
       LoRaRadio.write('O');
       LoRaRadio.write('N');
       LoRaRadio.write('G');
       LoRaRadio.endPacket();
       
   Serial.println("Done Sending PONG");
  
  // LoRaRadio.receive(0);  // not sure if we have to call this again.  test
}

