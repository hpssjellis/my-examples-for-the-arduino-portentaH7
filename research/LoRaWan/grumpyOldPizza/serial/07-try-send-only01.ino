
#include "LoRaRadio.h"

//static void myScanReceiveCallback(void);
//static void myMasterTransmitCallback(void);
static void myMasterReceiveCallback(void);
//static void mySlaveTransmitCallback(void);
//static void mySlaveReceiveCallback(void);


/*
static void myScanReceiveCallback(void)
{
    if (LoRaRadio.parsePacket() == 4)
    {
        // Got a PING from a master, so we are slave ...
        
        if ((LoRaRadio.read() == 'P') &&
            (LoRaRadio.read() == 'I') &&
            (LoRaRadio.read() == 'N') &&
            (LoRaRadio.read() == 'G'))
        {
            Serial.println("= SLAVE");
            Serial.print("< PING (RSSI: ");
            Serial.print(LoRaRadio.packetRssi());
            Serial.print(", SNR: ");
            Serial.print(LoRaRadio.packetSnr());
            Serial.println(")");
            Serial.println("> PONG");
            
          //  LoRaRadio.onTransmit(mySlaveTransmitCallback);
          //  LoRaRadio.onReceive(mySlaveReceiveCallback);
            
            LoRaRadio.beginPacket();
            LoRaRadio.write('P');
            LoRaRadio.write('O');
            LoRaRadio.write('N');
            LoRaRadio.write('G');
            LoRaRadio.endPacket();
        }
    }
    else
    {
        if (!LoRaRadio.busy())
        {
            // Didn't hear anything, so we are master ...
            
            Serial.println("= MASTER");
            Serial.println("> PING");
            
           // LoRaRadio.onTransmit(myMasterTransmitCallback);
            LoRaRadio.onReceive(myMasterReceiveCallback);
            
            LoRaRadio.beginPacket();
            LoRaRadio.write('P');
            LoRaRadio.write('I');
            LoRaRadio.write('N');
            LoRaRadio.write('G');
            LoRaRadio.endPacket();
        }
    }
}



*/

/*
static void myMasterTransmitCallback(void)
{
    LoRaRadio.receive(1000);
}

*/


static void myMasterReceiveCallback(void){

        // Receive timed out, so send a PING

        Serial.println("> PING");
    
        LoRaRadio.beginPacket();
        LoRaRadio.write('P');
        LoRaRadio.write('I');
        LoRaRadio.write('N');
        LoRaRadio.write('G');
        LoRaRadio.endPacket();
    
}


/*


static void mySlaveTransmitCallback(void)
{
    LoRaRadio.receive();
}

static void mySlaveReceiveCallback(void)
{
    if (LoRaRadio.parsePacket() == 4)
    {
        // Got a PING from a master, so send a PONG as reply
        
        if ((LoRaRadio.read() == 'P') &&
            (LoRaRadio.read() == 'I') &&
            (LoRaRadio.read() == 'N') &&
            (LoRaRadio.read() == 'G'))
        {
            Serial.print("< PING (RSSI: ");
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
        }
    }
}



*/
void setup( void )
{
    Serial.begin(9600);
    
    while (!Serial) { }

    LoRaRadio.begin(915000000);

    LoRaRadio.setFrequency(915000000);
    LoRaRadio.setTxPower(1);    //default 14
    LoRaRadio.setBandwidth(LoRaRadio.BW_125);
    LoRaRadio.setSpreadingFactor(LoRaRadio.SF_7);
    LoRaRadio.setCodingRate(LoRaRadio.CR_4_5);
    LoRaRadio.setLnaBoost(true);

  //  LoRaRadio.onReceive(myScanReceiveCallback);
  

   LoRaRadio.onReceive(myMasterReceiveCallback);

  
    LoRaRadio.receive(5000);
}

void loop( void )
{
}
