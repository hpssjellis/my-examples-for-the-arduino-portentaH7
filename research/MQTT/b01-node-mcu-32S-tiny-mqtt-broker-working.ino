#include "TinyMqtt.h"   // https://github.com/hsaturn/TinyMqtt

//#include <my_credentials.h>
//#include "arduino_secrets.h"   // more safe
#define SECRET_SSID "YOUR SSID"
#define SECRET_PASS "YOU PASSWORD"

char ssid[] = SECRET_SSID;    // Changing the secret strings to a character array
char password[] = SECRET_PASS; 


#define TINY_MQTT_DEBUG
#define PORT 1883
MqttBroker broker(PORT);

/** Basic Mqtt Broker
  *
  *  +-----------------------------+
  *  | ESP                         |
  *  |       +--------+            | 
  *  |       | broker |            | 1883 <--- External client/s
  *  |       +--------+            |
  *  |                             |
  *  +-----------------------------+
  */
void setup() 
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  delay(5000);
  
  digitalWrite(LED_BUILTIN, HIGH);
  Serial << "wait "<< endl;
  delay(5000);
  
  digitalWrite(LED_BUILTIN, LOW);
  Serial << "wait "<< endl;

    
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {   
    Serial << '.';
    delay(500);
  }
  Serial << "Connected to " << ssid << "IP address: " << WiFi.localIP() << endl;  

  broker.begin();
  Serial << "Broker ready : " << WiFi.localIP() << " on port " << PORT << endl;
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
  broker.loop();
}
