
/* Simple OTAA join for a LoRaWAN network
 *  
 *  In setup() below please replace the argument to LoRaWAN.begin()
 *  with your appropriate region specific band:
 *
 *  AS923
 *  AU915
 *  EU868
 *  IN865
 *  KR920
 *  US915
 *
 *  AU915/US915 networks have 64+8 channels. Typical gateways support only
 *  8 (9) channels. Hence it's a good idea to pick the proper channel
 *  subset via select via LoRaWAN.setSubBand(),
 *    
 *  EU868/IN865 have duty cycle restrictions. For debugging it makes sense
 *  to disable those via setDutyCycle(false);
 *    
 *  For an external antenna one should set the proper antenna gain
 *  (default is 2.0) via setAntennaGain().
 *    
 *  Please edit the keys below as they are just debugging samples.
 *    
 *    
 * This example code is in the public domain.
 */

#include "LoRaWAN.h"
#include "LoRaRadio.h"

const int myCharMax = 11;   // strangley only allows 10 characters




const char *devEui = "0101010101010101";  // can be assigned by Helium
const char *appEui = "0101010101010101";
const char *appKey = "2B7E151628AED2A6ABF7158809CF4F3C";






void setupLoRa( void )
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
       
   

    
    
   //    LoRaRadio.setFixedPayloadLength(10);   //testing ???

}

void setup( void ){
  
}



void setupHelium( void )
{
    Serial.begin(9600);
    
    while (!Serial) { }

    LoRaWAN.begin(US915);

    LoRaWAN.setSubBand(2);    // 1 for TTN and 2 for Helium I think confirmed for helium
    LoRaWAN.setDutyCycle(false);
    LoRaWAN.setAntennaGain(14.0);
    
     LoRaWAN.joinOTAA(appEui, appKey, devEui);

    Serial.println("JOIN( )");
}

void loop( void ){
  

    
    setupLoRa();
    //String msg = Serial.readStringUntil('\n');


 char msg[myCharMax]  =  "1234567890";   // strangely 10 not 11   
 //char msg[myCharMax] = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";


  //Serial.println();
  //Serial.println();


  LoRaRadio.beginPacket();  
  LoRaRadio.write(msg, sizeof(msg));    
  LoRaRadio.endPacket(); 

  Serial.println(msg);
  LoRaRadio.end();
  delay(10000);              // wait x seconds  


    
    setupHelium();
     
    if (LoRaWAN.joined() && !LoRaWAN.busy())
    {
        Serial.print("TRANSMIT( ");
        Serial.println(" )");

        LoRaWAN.beginPacket();
        LoRaWAN.write(0xef);
        LoRaWAN.write(0xbe);
        LoRaWAN.write(0xad);
        LoRaWAN.write(0xde);
        LoRaWAN.endPacket();
    }
    Serial.print(".");
   // LoRaWAN.stop();
    delay(30000);

}
