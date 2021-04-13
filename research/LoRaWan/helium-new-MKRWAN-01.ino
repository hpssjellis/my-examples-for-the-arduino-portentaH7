/*
* Lorawan continuous attempt to connect
* by @Rocksetta
* March 1st, 2021
* 
* Assumes you have done the MKRWANFWUpdate_standalone for your zone 
* US915_HYBRID
* 
*/

#include <MKRWAN.h>
#include <CayenneLPP.h>


LoRaModem modem;

bool myConnected = false;


//#include "arduino_secrets.h"
// Best to use an arduino_secrets.h file but easier here

// Note: Don't let Helium generate your Device EUI, That must come from each arduino device. See serial printout

String appEui = "11111111111111111";    // get from https://console.helium.com/devices
String appKey = "2222222222222222222222222222222";  // you have to change this from https://console.helium.com/devices

//const char *devEui = "0101010101010101";  // preset on arduino see other apps for it


CayenneLPP lpp(51);


void setup() {
   
  // change this to your regional band (eg. US915, US915_HYBRID, EU868, AS923, ...)
  // use US915_HYBRID for Helium
  if (!modem.begin(US915_HYBRID)) { // bad, did not startup
     // freeze it here then
    while (1) {}
  }
  delay(10000);
  
}

void loop() {

  if ( !modem.available() ){

  // For North American basic connections MAYBE???
     // modem.setPort(10);   // Helium ???
     // modem.dataRate(1);
     // modem.setADR(false);
     // modem.setPort(10);   //ttn ????
     // modem.dataRate(3);
     // modem.setADR(true);
    while (myConnected == false) {
      myConnected = modem.joinOTAA(appEui, appKey);
      delay(10000);
    } 
 
    int err;

    // Prepare Cayenne LPP
    lpp.reset();
    lpp.addAnalogInput(1, -55);
    lpp.addAnalogInput(2, -66);
    lpp.addAnalogInput(2, 11);

    modem.beginPacket();
    modem.write(lpp.getBuffer(), lpp.getSize());

    err = modem.endPacket(true);
    if (err > 0) {
       // do nothing since everything OK 
    }

    delay(7320000);  // 1000 = 1 second, then 3660000 = 1 hour 7320000 = every 2 hours

  }
}
