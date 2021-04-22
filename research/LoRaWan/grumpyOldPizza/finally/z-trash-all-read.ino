#include "LoRaRadio.h"

static void myReceive(void);

  const int myMaxChar = 25;
  
  char myInArray[myMaxChar];
  char myInArrayOld[myMaxChar];

 
  int myIncoming = LoRaRadio.parsePacket();   // must grab before read! 
  int myRssi = LoRaRadio.packetRssi();
  int mySnr = LoRaRadio.packetSnr();

  

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

}





void loop( void ){

//if (myInArray != myInArrayOld) {
 if(strcmp(myInArray, myInArrayOld) == 1){
  Serial.println("------");
  Serial.println(myInArray);
  Serial.println("parsePacket(): "+String( myIncoming ) + ", RSSI: " + String(myRssi)+", R: " + String(mySnr) );
  Serial.println("------");
  Serial.println();
  //myInArrayOld = myInArray;
  delay(1000);
  memcpy( myInArrayOld, myInArray, sizeof(myInArray) );
}

}





static void myReceive(void){
  


  int myI=0;

  
  while (LoRaRadio.available()) {
    myInArray[myI++] = (char)LoRaRadio.read() ;
  }

  byte lastChar = strlen(myInArray)-1;                                  
  myInArray[lastChar]= '\0';                   




}

