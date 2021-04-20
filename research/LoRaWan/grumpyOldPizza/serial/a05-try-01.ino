void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                   // initialize serial
  while (!Serial);

  Serial.println("LoRa Duplex");

  // override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(433E6)) {             // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }

  //LoRa.setTxPower(20);
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(125E3);

  //LoRa.onReceive(onReceive);
  //LoRa.receive();
  Serial.println("LoRa init succeeded.");
} 
  
void loop() {
  // put your main code here, to run repeatedly:
  // send a message
  readSerialtoSend();

  // parse for a packet, and call onReceive with the result:
  //LoRa.receive();
 // onReceive(LoRa.parsePacket());
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    incoming = "";
    //Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }

    // print RSSI of packet
    //Serial.print("' with RSSI ");
    //Serial.println(LoRa.packetRssi());
  }
  Serial.println(incoming);
  delay(500);
}
