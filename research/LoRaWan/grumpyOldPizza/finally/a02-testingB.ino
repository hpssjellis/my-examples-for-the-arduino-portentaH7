#include "LoRaRadio.h"


const int myCharMax = 71;

void setup( void )
{
    Serial.begin(9600);
    
    while (!Serial) { }  // non-blocking on Portenta murata module

    LoRaRadio.begin(915000000);

    LoRaRadio.setFrequency(915000000);
    LoRaRadio.setTxPower(1);    //default 14,  max ~20
    LoRaRadio.setBandwidth(LoRaRadio.BW_125);
    LoRaRadio.setSpreadingFactor(LoRaRadio.SF_7);
    LoRaRadio.setCodingRate(LoRaRadio.CR_4_5);
    LoRaRadio.setLnaBoost(true);

}

void loop( void ){

    delay(10000);              // wait x seconds

 //String msg = Serial.readStringUntil('\n');

 char msg[myCharMax]  =  "1       10        20        30        40        50        60        70";    
 //char msg[myCharMax] = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";


  //Serial.println();
  //Serial.println();


  LoRaRadio.beginPacket();  
  LoRaRadio.write(msg, sizeof(msg));    
  LoRaRadio.endPacket(); 

  //Serial.println("Message sent: "+String(msg));
  
}
