#include "LoRaRadio.h"
#include "TimerMillis.h"

static void myReceive(void);

// Global Variables

TimerMillis timerOn;
   int myIncoming ;
   int myRssi     ;
   int mySnr      ;
   const int myCharMax = 11; // allows 10 bytes      //64;  code breaks if sent bigger than this
   char myInArray[myCharMax];





void callbackOn(void){
  Serial.println();         
  Serial.println();         
  Serial.println(myInArray);
  Serial.println("parsePacket(): "+String( myIncoming ) + ", RSSI: " + String(myRssi)+", SNR: " + String(mySnr) );

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
    LoRaRadio.receive(0);            // is zero infinite, other upto milliseconds
   // timerOn.start(callbackOn,  3000);
    //timerOn.start(callbackOn, 0, 3000);
}





void loop( void ){

}




static void myReceive(void){
  
   int myI=0;  
   myIncoming = LoRaRadio.parsePacket();   // must grab before read! 
   myRssi     = LoRaRadio.packetRssi();
   mySnr      = LoRaRadio.packetSnr();
   strncpy(myInArray, "", myCharMax);  // erase the array of chars
   
  while (LoRaRadio.available() ) {
    myInArray[myI++] = (char)LoRaRadio.read() ;
    if (myI >= myCharMax) {break;}
  }

  //byte lastChar = strlen(myInArray)-1;                                  
  //myInArray[lastChar]= '\0';                   

   timerOn.start(callbackOn, 5);
}
