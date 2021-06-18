#include <ArduinoJson.h>
//#include <SoftwareSerial.h>

// Declare the "link" serial port
// Please see SoftwareSerial library for detail
//SoftwareSerial linkSerial(10, 11); // RX, TX

void setup() {
  // Initialize "debug" serial port
  // The data rate must be much higher than the "link" serial port
  Serial.begin(115200);
  //while (!Serial) continue;   // blocking
  delay(15000);
  Serial.println("Testing ArduinoJSON, using UART TX RX between t2 Portenta M7 cores");

  // Initialize the "link" serial port
  // Use the lowest possible data rate to reduce error ratio
  Serial1.begin(4800);
}
 
void loop() {
  // Values we want to transmit
  long timestamp = millis();
  int value = analogRead(A1);   // A0 is buggy

  // Print the values on the "debug" serial port
  Serial.print("timestamp = ");
  Serial.println(timestamp);
  Serial.print("value = ");
  Serial.println(value);
  Serial.println("---");

  // Create the JSON document
  StaticJsonDocument<200> doc;
  doc["timestamp"] = timestamp;
  doc["value"] = value;

  // Send the JSON document over the "link" serial port
  serializeJson(doc, Serial1);

  // Wait
  delay(5000);
}
