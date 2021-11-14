#include "LoRaRadio.h"
//#include "TimerMillis.h"

//TimerMillis timerOn;

int myIncoming ;
int myRssi     ;
int mySnr      ;

const int myCharMax = 10; // allows 10 bytes      //64;  code breaks if sent bigger than this
char myInArray[myCharMax];

//static void myReceive(void);




//void callbackOn(void){

//}



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
    
    LoRaRadio.setIQInverted(false);  // true gateway send/receive, false node send/receive
    LoRaRadio.setPublicNetwork(false);  //false private network

  
    LoRaRadio.onReceive(myReceive);  // just telling it about the callback 
    LoRaRadio.receive(0);            // is zero infinite, other upto milliseconds
   // timerOn.start(callbackOn,  3000);
    //timerOn.start(callbackOn, 0, 3000);
}


void loop( void ){

}


static void myReceive(void){  // constantly set to receive
  
   int myI=0;  
   myIncoming = LoRaRadio.parsePacket();   // must grab before read! 
   myRssi     = LoRaRadio.packetRssi();
   mySnr      = LoRaRadio.packetSnr();
   strncpy(myInArray, "", myCharMax);  // erase the array of chars
   
   while (LoRaRadio.available() ) {
      myInArray[myI++] = (char)LoRaRadio.read() ;
      if (myI >= myCharMax) {break;}
   }
                         
   Serial.println();         
   Serial.println(myInArray);
   Serial.println("parsePacket(): "+String( myIncoming ) + ", RSSI: " + String(myRssi)+", SNR: " + String(mySnr) );

}
