#include "LoRaRadio.h"
#include "TimerMillis.h"



TimerMillis myTimer02;    //, myTimer01;  //, myTimer03;

int myBestTx = 1;  // default  14; max 20???
bool mySentIQFalse = false;



const int myCharMax = 11; // allows 10 bytes and extra signal //64;  code breaks if sent bigger than this
char myInArray[myCharMax];
char myOutArray[myCharMax];


/*
void myIQFalseTimeout(void){
   // reset to IQ-true right away
   LoRaRadio.onReceive(myReceiveIQTrue);      // just telling it about the callback 
   LoRaRadio.receive(0); 
   if (mySentIQFalse){
     Serial.println("Timeout, things need to be reset or fixed ");  
     delay(20);       
     Serial.println();  
     delay(20);
      
     // reset the boolean, since this only happens once 
     mySentIQFalse = true;
     
   } else { 
     Serial.print("IQ false a response was received (This is good): ");  
     delay(20);   
     Serial.println(myOutArray);
     delay(20);    
   } 
   

}

*/


void setup( void ){
    Serial.begin(9600);
    
    while (!Serial) { }   // non-blocking for the murata module on the Portenta

    LoRaRadio.begin(915000000);

    LoRaRadio.setFrequency(915000000);
    LoRaRadio.setTxPower(myBestTx);    //default 14
    
    LoRaRadio.setBandwidth(LoRaRadio.BW_125);
    LoRaRadio.setSpreadingFactor(LoRaRadio.SF_7);
    LoRaRadio.setCodingRate(LoRaRadio.CR_4_5);
    LoRaRadio.setLnaBoost(true); 
    
    LoRaRadio.setIQInverted(true);       // true gateway receive, false node receive etc

    LoRaRadio.onReceive(myReceiveIQTrue);      // just telling it about the callback 
    LoRaRadio.onTransmit(myTransmitEnd);   // resets to IQ true
    LoRaRadio.receive(0);                // is zero infinite, other upto milliseconds

   // myTimer01.start(mySerialRead, 0, 200);  // 0 means continuous


}


void loop( void ){
   
}


void myTransmitEnd(void){
       LoRaRadio.setIQInverted(true);  // false switch to nodes
       LoRaRadio.receive(0); 
       Serial.println("OK transmit done");
       delay(20); 
  }

void mySendAsNode(void){ // sends "OK" on Node network to every Gateway message

       char myOkReply[11]  = "----OK----";  // 10 bytes  

       LoRaRadio.setIQInverted(false);  // false switch to nodes
       LoRaRadio.beginPacket();  
       LoRaRadio.write(myOkReply, sizeof(myOkReply));    
       LoRaRadio.endPacket(); 

       // Communicate what you did
       Serial.print("OK packet sent on IQ false: ");  
       delay(20);  
       Serial.println(myOkReply);
       delay(20); 
       
     // auto set to onTransmit back to IQ true
   }



/*
static void mySendIQTrueDone(void){
   Serial.print("packet sent on IQ true: ");  
   delay(20);  
   Serial.println(myInArray);
   delay(20); 
   LoRaRadio.onReceive(myReceiveIQFalse);      // just telling it about the callback 
   LoRaRadio.receive(5000);              // only for 5000 ms}
   
   mySentIQFalse = false;
   myTimer01.start(myIQFalseTimeout, 5000);
}
static void mySendIQFalseDone(void){
   mySentIQFalse = true;
   Serial.print("packet sent on IQ false: ");  
   delay(20);  
   Serial.println(myOutArray);
   delay(20); 
   LoRaRadio.onReceive(myReceiveIQTrue);      // just telling it about the callback 
   LoRaRadio.receive(0);                // is zero infinite, other upto milliseconds
}
*/
static void myReceiveIQTrue(void){  // constantly set to receive

   LoRaRadio.setIQInverted(true);       // true gateway receive, false node receive etc

   int myI=0;  
   int myIncoming = LoRaRadio.parsePacket();   // must grab before read! 
   int myRssi     = LoRaRadio.packetRssi();
   int mySnr      = LoRaRadio.packetSnr();
   strncpy(myInArray, "", myCharMax);  // erase the array of chars
   
   while (LoRaRadio.available() ) {
      myInArray[myI++] = (char)LoRaRadio.read() ;
      if (myI >= myCharMax) {break;}
   }

   if (myI == 11){    // if something came in send it out again
      //  Good so send OK message received on IQ false
      myTimer02.start(mySendAsNode, 20);  // 0 means continuous

   //strcpy(myOutArray, myInArray);  // copy in to out

   //LoRaRadio.onTransmit(mySendIQTrueDone);   // should happen once transmitting is over

  // LoRaRadio.beginPacket();  
 //  LoRaRadio.write(myInArray, sizeof(myInArray));    
 //  LoRaRadio.endPacket(); 


  // LoRaRadio.onReceive(myReceiveIQFalse);      // just telling it about the callback 
  // LoRaRadio.receive(5000);                   // only for 5000 ms}
   
   //mySentIQFalse = false;
   //myTimer01.start(myIQFalseTimeout, 5000);
      
      
   // Now that important stuff is done, print the information   
   
      
 //  Serial.print("packet sent on IQ true: ");  
 //  delay(20);  
 //  Serial.println(myInArray);
  // delay(20); 
   }

   Serial.print("Incoming, IQ True: ");  
   delay(20);       
   Serial.println(myInArray);
   delay(20);
   Serial.println("parsePacket(): "+String( myIncoming ) + ", RSSI: " + String(myRssi)+", SNR: " + String(mySnr) );      
   delay(20);  
}


/*
static void myReceiveIQFalse(void){  // constantly set to receive

   LoRaRadio.setIQInverted(false);       // true gateway receive, false node receive etc

   int myI=0;  
   int myIncoming = LoRaRadio.parsePacket();   // must grab before read! 
   int myRssi     = LoRaRadio.packetRssi();
   int mySnr      = LoRaRadio.packetSnr();
   strncpy(myOutArray, "", myCharMax);  // erase the array of chars
   
   while (LoRaRadio.available() ) {
      myOutArray[myI++] = (char)LoRaRadio.read() ;
      if (myI >= myCharMax) {break;}
   }

   if (myI == 11){
      
   // If you got 10 characters then send it out again.   
   LoRaRadio.beginPacket();  
   LoRaRadio.write(myOutArray, sizeof(myOutArray));    
   LoRaRadio.endPacket(); 
   
   mySentIQFalse = true;       
   LoRaRadio.onReceive(myReceiveIQTrue);      // just telling it about the callback 
   LoRaRadio.receive(0);                // is zero infinite, other upto milliseconds
      
   // Now that info sent you can print what you got   
   Serial.print("Incoming, IQ false: ");  
   delay(20);       
   Serial.println(myOutArray);
   delay(20);
   Serial.println("parsePacket(): "+String( myIncoming ) + ", RSSI: " + String(myRssi)+", SNR: " + String(mySnr) );      
   delay(20);

  // strcpy(myOutArray, myInArray);  // copy in to out

  // LoRaRadio.onTransmit(mySendIQFalseDone);   // should happen once transmitting is over


   Serial.print("packet sent on IQ false: ");  
   delay(20);  
   Serial.println(myOutArray);
   delay(20); 
  }
// A wrong size IQ false response will leave you in IQ false mode until timer sets things back
}

*/
