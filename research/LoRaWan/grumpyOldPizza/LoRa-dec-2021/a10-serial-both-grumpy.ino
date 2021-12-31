#include "LoRaRadio.h"
#include "TimerMillis.h"

static void myReceive(void);


// Global Variables

TimerMillis myReceivePrintTimer, mySendTimer, mySendPrintTimer;

bool mySendThreadFree = true;
bool myReceiveThreadFree = true;

String mySendString, myReceiveString;

int myIncomingInt ;
int myRssi     ;
int mySnr      ;
const int myCharMax = 64; // breaks after 64

char mySendArray[myCharMax];


void mySendTimerOn(void){
  if (myReceiveThreadFree){
    mySendThreadFree = false;
    while (Serial.available() ) {
      mySendString.concat( (char)Serial.read());  // could be BYTE
    }

    if (mySendString.length() > 0){

      strncpy(mySendArray, "", myCharMax);  // erase the array of chars
      mySendString.toCharArray(mySendArray, mySendString.length());
      
      LoRaRadio.beginPacket();  
      LoRaRadio.write(mySendArray, mySendString.length());   
      LoRaRadio.endPacket(); 
  
      mySendPrintTimer.start(mySendPrintIt, 5);  // just once 5 milliseconds later
    
  }
  LoRaRadio.receive(0);   
  mySendThreadFree = true; // thread finished
  }

}


void mySendPrintIt(void){
    Serial.println("Sending with length:"+ String(mySendString.length()));  
   // Serial.println(mySendString.length()); 
    Serial.println(mySendString);
    //Serial.println();
    LoRaRadio.receive(0); 
    mySendString = ""; 
}



void myReceivePrintIt(void){       
  Serial.println(myReceiveString);
  Serial.println("parsePacket:"+String(myIncomingInt) + ", RSSI:" + String(myRssi)+", SNR:" + String(mySnr) );
  Serial.println(); 
    
  LoRaRadio.receive(0); 
  myReceiveString = "";
}



static void myReceive(void){
  if (mySendThreadFree){
    myReceiveThreadFree = false;

   myIncomingInt = LoRaRadio.parsePacket();   // must grab before read! 
   myRssi     = LoRaRadio.packetRssi();
   mySnr      = LoRaRadio.packetSnr();

   while (LoRaRadio.available() ) {
     myReceiveString.concat( (char)LoRaRadio.read());  // could be BYTE
   }

   myReceivePrintTimer.start(myReceivePrintIt, 5);  // just once 5 milliseconds later
   myReceiveThreadFree = true;
  }
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
    mySendTimer.start(mySendTimerOn, 0, 300);   //continuous every interval
    Serial.println("LoRa Text Messaging");    
    Serial.println();
}



void loop( void ){

}
