#include "LoRaRadio.h"


   int myDelay = 15000;   // 1000 = 1 second
const int myCharMax = 11;  // not sure why 11 not 10

 char msg[myCharMax]  = "num6------";  // 10 bytes   
                  //  = "----------";  // must be this length




void setup( void )
{
    Serial.begin(9600);
    
    while (!Serial) { }  // non-blocking on Portenta murata module

    LoRaRadio.begin(915000000);

    LoRaRadio.setFrequency(915000000);
    LoRaRadio.setTxPower(1);                      // smallest try -1, default 14,  max ~20
 
    LoRaRadio.setBandwidth(LoRaRadio.BW_125);     // Bandwidth: B W_125   BW_250   BW_500
    LoRaRadio.setSpreadingFactor(LoRaRadio.SF_7); // Spreading Factor: SF_7   SF_8    SF_9  SF_10 SF_11 SF_12 
    LoRaRadio.setCodingRate(LoRaRadio.CR_4_5);    // Coding Rate: CR_4_5  CR_4_6  CR_4_7  CR_4_8  
    LoRaRadio.setLnaBoost(true);
    
    LoRaRadio.setIQInverted(false);  // true gateway send/receive, false node send/receive
    LoRaRadio.setPublicNetwork(false);  //false private network

}

void loop( void ){

  //String msg = Serial.readStringUntil('\n'); 
  LoRaRadio.beginPacket();  
  LoRaRadio.write(msg, sizeof(msg));    
  LoRaRadio.endPacket(); 

  Serial.println("Message sent: "+String(msg));
  
  delay(myDelay);              // wait x seconds  
}
