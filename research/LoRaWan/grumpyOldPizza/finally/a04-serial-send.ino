/*
*   still testing. what about hex not serial 
*/




#include "LoRaRadio.h"

void setup( void )
{
    Serial.begin(9600);
    
    while (!Serial) { }  // non-blocking on Portenta murata module

    LoRaRadio.begin(915000000);

    LoRaRadio.setFrequency(915000000);
    LoRaRadio.setTxPower(1);    //default 14
    LoRaRadio.setBandwidth(LoRaRadio.BW_125);
    LoRaRadio.setSpreadingFactor(LoRaRadio.SF_7);
    LoRaRadio.setCodingRate(LoRaRadio.CR_4_5);
    LoRaRadio.setLnaBoost(true);

}

void loop( void ){

    if (Serial.available()) {   
       LoRaRadio.beginPacket(); 
       while (Serial.available()){
          LoRaRadio.write(Serial.read()); 
       }
       LoRaRadio.endPacket();
   } 
  

}
