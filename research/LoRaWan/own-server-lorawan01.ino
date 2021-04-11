#include "ArduinoLowPower.h"
#include <CayenneLPP.h>

LoRaModem modem;



#include "arduino_secrets.h"
// Please enter your sensitive data in the Secret tab or arduino_secrets.h
String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;



int long_sleep = 60000 * 2;
int short_sleep = 60000 * 1;

CayenneLPP lpp(51);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  // change this to your regional band (eg. US915, AS923,US915_HYBRID ...)
  if (!modem.begin(US915_HYBRID)) {
    Serial.println("Failed to start module");
    while (1) {}
  };



  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());



  int connected = modem.joinOTAA(appEui, appKey);


  Serial.println(connected);

  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }

  modem.setPort(10);
  modem.dataRate(3);
  modem.setADR(true);

}



void loop() {

  Serial.println("delay 5 seconds");
  delay(5000);


  int err;
  int sleepTime = long_sleep;

  // Prepare Cayenne LPP
  lpp.reset();
  lpp.addAnalogInput(1, -18);
  lpp.addAnalogInput(2, -46);
  lpp.addAnalogInput(2, 80);


  modem.beginPacket();
  modem.write(lpp.getBuffer(), lpp.getSize());

  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println(err);
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
  delay(5000);
  USBDevice.detach();
  LowPower.deepSleep(sleepTime);
  USBDevice.attach();

}

