
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
    LoRaRadio.beginPacket();
       LoRaRadio.write('P');
       LoRaRadio.write('O');
       LoRaRadio.write('N');
       LoRaRadio.write('G');
       LoRaRadio.endPacket();
    delay(20000);              // wait x seconds
}
