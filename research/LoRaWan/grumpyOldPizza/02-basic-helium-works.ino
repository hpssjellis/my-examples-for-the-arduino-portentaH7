/* Simple OTAA join for a LoRaWAN or Helium network network
 * Does nothing except connect every hour. No lights no serial print
 * The concept is that you should see some kind of connection on
 * The Helium of TTN network dashboards
 * This example code is in the public domain.
 */

#include "LoRaWAN.h"
#include <CayenneLPP.h>


// for portenta 06

const char *devEui = "1010101010101010";    // as per on helium console msb format
const char *appEui = "1010101010101010";              
const char *appKey = "101010101010101010101010101010101";

CayenneLPP lpp(51);



void setup( void ){

    LoRaWAN.begin(US915);
    LoRaWAN.setSubBand(2);    // 1 for TTN and 2 for Helium.
    LoRaWAN.setDutyCycle(false);
    LoRaWAN.setAntennaGain(2.0);
  // For North American basic connections MAYBE???
     // modem.setPort(10);   // Helium ???
     // modem.dataRate(1);
     // modem.setADR(false);
     // modem.setPort(10);   //ttn ????
     // modem.dataRate(3);
     // modem.setADR(true);


    LoRaWAN.setDataRate(1);   // not really needed
    LoRaWAN.setADR(true);     // not really needed
    
    LoRaWAN.setSaveSession(true);
    LoRaWAN.joinOTAA(appEui, appKey, devEui);

}

void loop( void ){
  
if (!LoRaWAN.busy()){
        if (!LoRaWAN.linkGateways()){
            
            LoRaWAN.rejoinOTAA();
        }
        
        if (LoRaWAN.joined())  {
               
          int err;

          // Prepare Cayenne LPP
          lpp.reset();
          lpp.addAnalogInput(1, -18);
          lpp.addAnalogInput(2, -46);
          lpp.addAnalogInput(2, 80);

          LoRaWAN.beginPacket();
          LoRaWAN.write(lpp.getBuffer(), lpp.getSize());

          err = LoRaWAN.endPacket(true);
          if (err > 0) {
             // do nothing since everything OK 
          }
        }
    }

    delay(20000);  // 1000 = 1 second, then 3660000 = 1 hour
}
