/*   
 * Sender sends what is typed   
 * This example code is in the public domain.
 */
 
#include "LoRaRadio.h"
 







void setup( void ){
    Serial.begin(9600);
    
    while (!Serial) { }  // does not lock up code here

    LoRaRadio.begin(915000000);

    LoRaRadio.setFrequency(915000000);
    LoRaRadio.setTxPower(14);
    LoRaRadio.setBandwidth(LoRaRadio.BW_125);
    LoRaRadio.setSpreadingFactor(LoRaRadio.SF_7);
    LoRaRadio.setCodingRate(LoRaRadio.CR_4_5);
    LoRaRadio.setLnaBoost(true);

    LoRaRadio.receive(10000);
}

void loop( void ){
                             
   if (Serial.available()) {   
       LoRaRadio.beginPacket(); 
       LoRaRadio.write(Serial.read()); 
       LoRaRadio.endPacket();
   } 
 
}
