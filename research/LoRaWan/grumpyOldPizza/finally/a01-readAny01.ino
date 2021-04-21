#include "LoRaRadio.h"

static void myReceive(void);



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

}





static void myReceive(void){
  


   int myI=0;

char myInArray[64];

  
  while (LoRaRadio.available()) {
    myInArray[myI++] = (char)LoRaRadio.read() ;
  }

byte lastChar = strlen(myInArray)-1;                                  
 myInArray[lastChar]= '\0';                   


Serial.println(myInArray);

/*

Serial.print( (char)LoRaRadio.read() );
Serial.print( (char)LoRaRadio.read() );
Serial.print( (char)LoRaRadio.read() );
Serial.print( (char)LoRaRadio.read() );
Serial.print( (char)LoRaRadio.read() );
Serial.print( (char)LoRaRadio.read() );
Serial.print( (char)LoRaRadio.read() );
Serial.println( (char)LoRaRadio.read() );



*/

   int myIncoming = LoRaRadio.parsePacket();
  // Serial.println("LoRaRadio.parsePacket(): "+String( myIncoming ) );
  
Serial.println("LoRaRadio.parsePacket(): "+String( myIncoming ) );
   Serial.println("Done");
   Serial.print("(RSSI: ");
   Serial.print(LoRaRadio.packetRssi());
   Serial.print(", SNR: ");
   Serial.print(LoRaRadio.packetSnr());
   Serial.println(")");
   Serial.println("");



}




