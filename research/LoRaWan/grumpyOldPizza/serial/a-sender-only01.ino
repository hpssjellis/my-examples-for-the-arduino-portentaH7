/* LED Blink via TimerMillis
 *  
 *  In setup, start the timerOn instance of the millisecond timer with no delay 
 *  and repeat every 2000 milliseconds.  CallbackOn turns on the led then calls 
 *  the second instance of the millisecond timer with delay of 250 milliseconds 
 *  to execute once per call.
 *   
 *  Net effect is that the led is on for 250 millisconds every 2000 milliseconds
 *    
 * This example code is in the public domain.
 */
           //  LoRaRadio.onTransmit(myMasterTransmitCallback);
           // LoRaRadio.onReceive(myMasterReceiveCallback);
           
#include "LoRaRadio.h"
#include "TimerMillis.h"

TimerMillis timerOff;
TimerMillis timerOn;



void callbackOff(void){
   LoRaRadio.receive(5000);  
   
    timerOn.start(callbackOff, 60000);
}

void callbackOn(void){
   
    
    Serial.println("= SLAVE");
    Serial.print("(RSSI: ");
    Serial.print(LoRaRadio.packetRssi());
    Serial.print(", SNR: ");
    Serial.print(LoRaRadio.packetSnr());
    Serial.println(")");
    Serial.println("> PONG");

    LoRaRadio.beginPacket();
    LoRaRadio.write('P');
    LoRaRadio.write('O');
    LoRaRadio.write('N');
    LoRaRadio.write('G');
    LoRaRadio.endPacket();
    
    Serial.println("Packet Sent!");
    timerOff.start(callbackOff, 250);
}

void setup( void ){
        
    Serial.begin(9600);
        
    LoRaRadio.begin(915000000);

    LoRaRadio.setFrequency(915000000);
    LoRaRadio.setTxPower(14);
    LoRaRadio.setBandwidth(LoRaRadio.BW_125);
    LoRaRadio.setSpreadingFactor(LoRaRadio.SF_7);
    LoRaRadio.setCodingRate(LoRaRadio.CR_4_5);
    LoRaRadio.setLnaBoost(true);

   // LoRaRadio.onReceive(myScanReceiveCallback);
   // LoRaRadio.receive(5000);
    timerOn.start(callbackOn, 0, 10000);
  
}

void loop( void ){


}
