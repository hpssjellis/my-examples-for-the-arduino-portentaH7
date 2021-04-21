#include "LoRaRadio.h"

void setup( void )
{
    Serial.begin(9600);
    
    while (!Serial) { }  // non-blocking on Portenta murata module

    LoRaRadio.begin(915000000);

    LoRaRadio.setFrequency(915000000);
    LoRaRadio.setTxPower(1);    //default 14
    LoRaRadio.setBandwidth(LoRaRadio.BW_125);
    LoRaRadio.setSpreadingFactor(LoRaRadio.SF_7);
    LoRaRadio.setCodingRate(LoRaRadio.CR_4_5);
    LoRaRadio.setLnaBoost(true);

}

void loop( void ){
   // LoRaRadio.beginPacket();
   //    LoRaRadio.write('P');
   //    LoRaRadio.write('O');
   //    LoRaRadio.write('N');
   //    LoRaRadio.write('G');
   //    LoRaRadio.endPacket();
    delay(10000);              // wait x seconds

 //String msg = Serial.readStringUntil('\n');
 String msg = "Hello-Lora";

  Serial.println();
  Serial.print("Sending: " + msg + " - ");
  for (unsigned int i = 0; i < msg.length(); i++) {
    Serial.print(msg[i] >> 4, HEX);
    Serial.print(msg[i] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();

  int err;
  LoRaRadio.beginPacket();
  LoRaRadio.print(msg);    
  LoRaRadio.endPacket(); 

  Serial.println("Message sent: "+String(msg));




    
}
