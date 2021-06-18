#include <ArduinoJson.h>
//#include <SoftwareSerial.h>

// Declare the "link" serial port
// Please see SoftwareSerial library for detail
//SoftwareSerial linkSerial(10, 11); // RX, TX

void setup() {
  // Initialize "debug" serial port
  // The data rate must be much higher than the "link" serial port
  Serial.begin(115200);
 // while (!Serial) continue; //blocking
  delay(15000);
  Serial.print("Testing ArduoJSON receive UART RX TX between 2 Portenta M7 cores");

  // Initialize the "link" serial port
  // Use the lowest possible data rate to reduce error ratio
  Serial1.begin(4800);
}
 
void loop() {
  // Check if the other Arduino is transmitting
  if (Serial1.available()) 
  {
    // Allocate the JSON document
    // This one must be bigger than for the sender because it must store the strings
    StaticJsonDocument<300> doc;

    // Read the JSON document from the "link" serial port
    DeserializationError err = deserializeJson(doc, Serial1);

    if (err == DeserializationError::Ok) 
    {
      // Print the values
      // (we must use as<T>() to resolve the ambiguity)
      Serial.print("timestamp = ");
      Serial.println(doc["timestamp"].as<long>());
      Serial.print("value = ");
      Serial.println(doc["value"].as<int>());
    } 
    else 
    {
      // Print error to the "debug" serial port
      Serial.print("deserializeJson() returned ");
      Serial.println(err.c_str());
  
      // Flush all bytes in the "link" serial port buffer
      // Is this needed ??
      while (Serial1.available() > 0)
        Serial1.read();
    }
  }
}
