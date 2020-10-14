/*
  LED Control

  This example scans for BLE peripherals until one with the advertised service
  "19b10000-e8f2-537e-4f6c-d104768a1214" UUID is found. Once discovered and connected,
  it will remotely control the BLE Peripheral's LED, when the button is pressed or released.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense, PortentaH7 board.
  - Button with pull-up resistor connected to pin 2.

  You can use it with another board that is compatible with this library and the
  Peripherals -> LED example.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>

// variables for button

void setup() {
  pinMode(LEDB, OUTPUT);
  Serial.begin(9600);
 // while (!Serial);  //This is not useful when it is self powered

  // initialize the BLE hardware
  BLE.begin();
  Serial.println("BLE Central - LED control");

  // start scanning for LED BLE peripherals
  BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
}

void loop() {
  Serial.print(".");
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // discovered a peripheral, print out address, local name, and advertised service
    Serial.print("Found ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();

    if (peripheral.localName().indexOf("LED") < 0) {
          Serial.println("No 'LED' in name");
      return;  // If the name doeshn't have "LED" in it then ignore it
    }

    // stop scanning
    BLE.stopScan();

    controlLed(peripheral);

    // peripheral disconnected, start scanning again
    BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
  }
}

void controlLed(BLEDevice peripheral) {
  // connect to the peripheral
  Serial.println("Connecting ...");

  if (peripheral.connect()) {
    Serial.println("Connected");
  } else {
    Serial.println("Failed to connect!");
    return;
  }

  // discover peripheral attributes
  Serial.println("Discovering attributes ...");
  if (peripheral.discoverAttributes()) {
    Serial.println("Attributes discovered");
  } else {
    Serial.println("Attribute discovery failed!");
    peripheral.disconnect();
    return;
  }

  // retrieve the LED characteristic
  //BLECharacteristic ledCharacteristic = peripheral.characteristic("19b10001-e8f2-537e-4f6c-d104768a1214");  //weird this broke it
  BLECharacteristic ledCharacteristic = peripheral.characteristic("19b10000-e8f2-537e-4f6c-d104768a1214"); 
                                                                 

  if (!ledCharacteristic) {
    Serial.println("Peripheral does not have LED characteristic!");
    peripheral.disconnect();
    return;
  } else if (!ledCharacteristic.canWrite()) {
    Serial.println("Peripheral does not have a writable LED characteristic!");
    peripheral.disconnect();
    return;
  }

  while (peripheral.connected()) {
    // while the peripheral is connected
        
        digitalWrite(LEDB, LOW); //weird turns blue on
        Serial.print("flashing the LED on the device: ");
        Serial.println(peripheral.localName());
        ledCharacteristic.writeValue((byte)0x01);
        delay(500);
        ledCharacteristic.writeValue((byte)0x00);
        delay(500);        
        ledCharacteristic.writeValue((byte)0x01);
        delay(500);
        ledCharacteristic.writeValue((byte)0x00);
        delay(500);
        
        peripheral.disconnect();       
       digitalWrite(LEDB, HIGH); // weird turns blue off
    
  }

  Serial.println("Peripheral disconnected");
}
