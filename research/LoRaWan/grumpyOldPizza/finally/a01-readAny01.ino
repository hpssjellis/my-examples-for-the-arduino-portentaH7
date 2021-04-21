

#include "LoRaRadio.h"

static void myMasterReceiveCallback(void);


static void myReceive(void){

   for (int i = 0; i < LoRaRadio.parsePacket(); i++) {
        Serial.print((char)LoRaRadio.read());
   } 
   Serial.println("");
  
   LoRaRadio.receive(5);
}


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
    LoRaRadio.receive(0);    // is zero infinite????

}

void loop( void ){

}
