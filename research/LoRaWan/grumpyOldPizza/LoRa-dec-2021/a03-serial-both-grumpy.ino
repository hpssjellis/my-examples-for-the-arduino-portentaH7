#include "LoRaRadio.h"
#include "TimerMillis.h"

static void myReceive(void);



// Global Variables

TimerMillis myReceiveTimer;
TimerMillis mySendTimer;

String myIncomingStr;
int myIncomingInt ;
int myRssi     ;
int mySnr      ;
const int myCharMax = 64; // breaks after 64
char myInArray[myCharMax];
char mySendArray[myCharMax];




void mySendTimerOn(void){
 while (Serial.available() ) {
         myIncomingStr.concat( (char)Serial.read());  // could be BYTE
   }

  if (myIncomingStr.length() > 0){
    Serial.println(myIncomingStr); 
    Serial.println(myIncomingStr.length()); 

    myIncomingStr.toCharArray(mySendArray,myIncomingStr.length() );
    LoRaRadio.beginPacket();  
    LoRaRadio.write(mySendArray, myIncomingStr.length());   
    LoRaRadio.endPacket(); 
    
    myIncomingStr = ""; 

    
  }
}


void myReceiveCallbackOn(void){
  Serial.println();         
  Serial.println();         
  Serial.println(myInArray);
  Serial.println("parsePacket(): "+String( myIncomingInt ) + ", RSSI: " + String(myRssi)+", SNR: " + String(mySnr) );

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
    mySendTimer.start(mySendTimerOn, 0, 1000);   //continuous every second

}





void loop( void ){

}


static void myReceive(void){
  
   int myI=0;  
   myIncomingInt = LoRaRadio.parsePacket();   // must grab before read! 
   myRssi     = LoRaRadio.packetRssi();
   mySnr      = LoRaRadio.packetSnr();
   strncpy(myInArray, "", myCharMax);  // erase the array of chars
   
  while (LoRaRadio.available() ) {
    myInArray[myI++] = (char)LoRaRadio.read() ;
    if (myI >= myCharMax) {break;}
  }
                

   myReceiveTimer.start(myReceiveCallbackOn, 5);
}
