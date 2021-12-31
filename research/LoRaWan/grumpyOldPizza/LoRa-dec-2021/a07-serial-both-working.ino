#include "LoRaRadio.h"
#include "TimerMillis.h"

static void myReceive(void);



// Global Variables

TimerMillis myReceiveTimer, mySendTimer, myResetTimer;

bool mySendThreadFree = true;
bool myReceiveThreadFree = true;

String mySendString, myReceiveString;
int myIncomingInt ;
int myRssi     ;
int mySnr      ;
const int myCharMax = 64; // breaks after 64
//char myInArray[myCharMax];
char mySendArray[myCharMax];




void mySendTimerOn(void){
  if (myReceiveThreadFree){
 mySendThreadFree = false;
 while (Serial.available() ) {
         mySendString.concat( (char)Serial.read());  // could be BYTE
   }

  if (mySendString.length() > 0){
    Serial.println(mySendString); 
    Serial.println(mySendString.length()); 
    
    strncpy(mySendArray, "", myCharMax);  // erase the array of chars
    mySendString.toCharArray(mySendArray, mySendString.length());
    
    LoRaRadio.beginPacket();  
    LoRaRadio.write(mySendArray, mySendString.length());   
    LoRaRadio.endPacket(); 
    
    mySendString = ""; 
    
  }

  mySendThreadFree = true; // thread finished
  }
  LoRaRadio.receive(0); 
}


void myReceiveCallbackOn(void){
  Serial.println();         
  Serial.println();         
  Serial.println(myReceiveString);
  Serial.println("parsePacket(): "+String( myIncomingInt ) + ", RSSI: " + String(myRssi)+", SNR: " + String(mySnr) );

  myReceiveString = "";
  LoRaRadio.receive(0); 
  // LoRaRadio.onReceive(myReceive);  // just telling it about the callback 
   // LoRaRadio.receive(0);            // is zero infinite, other upto milliseconds
}


void myReset(void){
  mySendThreadFree = true;
  myReceiveThreadFree = true;
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
   
   //    LoRaRadio.setFixedPayloadLength(10);   //testing ???
  
    LoRaRadio.onReceive(myReceive);  // just telling it about the callback 
    LoRaRadio.receive(0);            // is zero infinite, other upto milliseconds
    mySendTimer.start(mySendTimerOn, 0, 100);   //continuous every interval
   // myResetTimer.start(myReset, 0, 2000);   //continuous every interval

}





void loop( void ){

}


static void myReceive(void){
  if (mySendThreadFree){
    myReceiveThreadFree = false;
  // int myI=0;  
   myIncomingInt = LoRaRadio.parsePacket();   // must grab before read! 
   myRssi     = LoRaRadio.packetRssi();
   mySnr      = LoRaRadio.packetSnr();
   
  // strncpy(myInArray, "", myCharMax);  // erase the array of chars
  
  while (LoRaRadio.available() ) {
     myReceiveString.concat( (char)LoRaRadio.read());  // could be BYTE
  }

   myReceiveTimer.start(myReceiveCallbackOn, 5);  // just once 5 milliseconds later
   myReceiveThreadFree = true;
  }
}
