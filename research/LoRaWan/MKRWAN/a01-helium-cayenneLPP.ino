#include <MKRWAN.h>
#include <CayenneLPP.h>

LoRaModem modem;

bool myConnected = false;

String devEui = "1010101010101010";    // get from https://console.helium.com/devices
String appEui = "0101010101010101";              
String appKey = "11001100110011001100110011001100";  

void myPrintMask(){
 
  Serial.println("-------------------------------");
  Serial.println("Your module version is: " + String(modem.version()) );
  Serial.println("getDataRate: " + String(modem.getDataRate()) );
  Serial.println("getADR: " + String(modem.getADR()) );
  Serial.println("getRX2Freq: " + String(modem.getRX2Freq()) );
  Serial.println("getRX2DR(): " + String(modem.getRX2DR()) );
   
  Serial.println("getDevAddr: " + String(modem.getDevAddr()) );
  Serial.println("getNwkSKey: " + String(modem.getNwkSKey()) );
  Serial.println("getAppSKey: " + String(modem.getAppSKey()) );
  Serial.println("getFCU: " + String(modem.getFCU()) );
  Serial.println("getFCD: " + String(modem.getFCD()) );
  Serial.println("getChannelMask: " + String(modem.getChannelMask()));
  
  Serial.println("isChannelEnabled(0): " + String(modem.isChannelEnabled(0)));
  Serial.println("isChannelEnabled(1): " + String(modem.isChannelEnabled(1)));
  Serial.println("isChannelEnabled(2): " + String(modem.isChannelEnabled(2)));
  Serial.println("isChannelEnabled(3): " + String(modem.isChannelEnabled(3)));
  Serial.println("isChannelEnabled(4): " + String(modem.isChannelEnabled(4)));
  Serial.println("isChannelEnabled(5): " + String(modem.isChannelEnabled(5)));
  Serial.println("isChannelEnabled(6): " + String(modem.isChannelEnabled(6)));
  Serial.println("-------------------------------");
}






void myGetConnected(){

  // For North American basic connections
    //  modem.setPort(10);
    //  modem.dataRate(1);
    //  modem.setADR(false);

   while (myConnected == false) {
      digitalWrite(LEDR, LOW);  // high off for new boards
      digitalWrite(LEDG, HIGH);  
      digitalWrite(LEDB, LOW); 
      Serial.println("[LoRaWan] Joining network...");
      myConnected = modem.joinOTAA(appEui, appKey, devEui);
      if (myConnected) {
         digitalWrite(LEDR, HIGH);  // high off for new boards
         digitalWrite(LEDG, LOW);  
         digitalWrite(LEDB, HIGH);  
         Serial.println("[LoRaWan] Joined network! Connected: " + String(myConnected));
     } else {
        digitalWrite(LEDR, HIGH);  // high off for new boards
        digitalWrite(LEDG, HIGH);  
        digitalWrite(LEDB, HIGH);  
        Serial.println("[LoRaWan] Joining network failed, retrying in 3 seconds... Connected: "+ String(myConnected));
     }
     delay(3000);
  }
  
myPrintMask();

  
  }













void setup() {
  Serial.begin(115200);
 // while (!Serial);  // This might be fine as the murata module doesn't use it???
  
  if (!modem.begin(US915_HYBRID)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  delay(10000);  // some people say this is needed
  Serial.println("For modem.begin(US915_HYBRID)");
  Serial.println("Now Showing default Channels ");
  myPrintMask();

 
  
}

void loop() {

  if ((myConnected == false)) {
       myGetConnected();
  } else {   // show LED blue that connected 
       digitalWrite(LEDR, HIGH);  // high off for new boards
       digitalWrite(LEDG, HIGH);  
       digitalWrite(LEDB, LOW); 
    }


  DynamicJsonDocument jsonBuffer(4096);
 //DynamicJsonDocument doc(1024);
  CayenneLPP lpp(160);

  JsonArray myJsonArray = jsonBuffer.to<JsonArray>();

  Serial.begin(115200);
  Serial.println();

  lpp.reset();
  lpp.addDigitalInput(1, 0);
  lpp.addDigitalOutput(2, 1);
  lpp.addAnalogInput(3, 1.23f);
  //lpp.addAnalogOutput(4, 3.45f);
  lpp.addAnalogOutput(1, (float)analogRead(A0));
  lpp.addLuminosity(5, 20304);
  lpp.addPresence(6, 1);
  lpp.addTemperature(7, 26.5f);
  lpp.addRelativeHumidity(8, 86.6f);
  lpp.addAccelerometer(9, 1.234f, -1.234f, 0.567f);
  lpp.addBarometricPressure(10, 1023.4f);
  lpp.addGyrometer(1, -12.34f, 45.56f, 89.01f);
  lpp.addGPS(1, -12.34f, 45.56f, 9.01f);

  lpp.addUnixTime(1, 135005160);
  
  lpp.addGenericSensor(1, 4294967295);
  //lpp.addGenericSensor(1, model_tflite );
  lpp.addVoltage(1, 3.35); 
  lpp.addCurrent(1, 0.321);
  lpp.addFrequency(1, 50);
  lpp.addPercentage(1, 100);
  lpp.addAltitude(1 , 50);
  lpp.addPower(1 , 50000);
  lpp.addDistance(1 , 10.555);
  lpp.addEnergy(1 , 19.055);
  lpp.addDirection(1 , 90);
  lpp.addSwitch(1 , 0);
  
  lpp.addConcentration(1 , 512);
  lpp.addColour(1 , 64, 128, 255);


  lpp.decode(lpp.getBuffer(), lpp.getSize(), myJsonArray);
  
  serializeJsonPretty(myJsonArray, Serial);
  Serial.println();
  myPrintMask();

  delay(3000);
  digitalWrite(LEDR, HIGH);  // high off for new boards
  digitalWrite(LEDG, HIGH);  
  digitalWrite(LEDB, HIGH); 
  delay(30000);  // 1000 = 1 second
}
