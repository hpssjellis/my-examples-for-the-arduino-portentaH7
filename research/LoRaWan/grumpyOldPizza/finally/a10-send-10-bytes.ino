#include "LoRaRadio.h"


const int myCharMax = 11;   // strangley only allows 10 characters

void setup( void )
{
    Serial.begin(9600);
    
    while (!Serial) { }  // non-blocking on Portenta murata module

    LoRaRadio.begin(915000000);

    LoRaRadio.setFrequency(915000000);
    LoRaRadio.setTxPower(1);    // smallest try -1, default 14,  max ~20
    LoRaRadio.setBandwidth(LoRaRadio.BW_125);
    LoRaRadio.setSpreadingFactor(LoRaRadio.SF_7);
    LoRaRadio.setCodingRate(LoRaRadio.CR_4_5);
    LoRaRadio.setLnaBoost(true);

}

void loop( void ){


 //String msg = Serial.readStringUntil('\n');

 char msg[myCharMax]  =  "1234567890";   // strangely 10 not 11   
 //char msg[myCharMax] = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";


  //Serial.println();
  //Serial.println();


  LoRaRadio.beginPacket();  
  LoRaRadio.write(msg, sizeof(msg));    
  LoRaRadio.endPacket(); 

  //Serial.println("Message sent: "+String(msg));
  
  delay(10000);              // wait x seconds  
}
