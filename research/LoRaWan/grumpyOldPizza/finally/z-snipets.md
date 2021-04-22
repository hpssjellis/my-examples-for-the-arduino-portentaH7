


 if (Serial.available()) {
     c = Serial.read();
     rf95.send((char *)c, sizeof(c));
     rf95.waitPacketSent();



 rf95.send(&c, sizeof(c));




So for the Tx you have

LoRa.beginPacket();
LoRa.write((uint8_t*)&data, sizeof(data));
LoRa.endPacket();
and for the Rx I have

int packetSize = LoRa.parsePacket ();
if (packetSize) // Only read if there is some data to read..
 {
   LoRa.readBytes((uint8_t *)&data, packetSize);
 }










  // Write packet header
  LoRa.beginPacket();
  // Send 4 bytes (sizeof(a)) starting at the location of counter
  LoRa.write((const uint8_t*)&a, sizeof(a));
  // Send 4 bytes (sizeof(counter)) starting at the location of counter
  LoRa.write((const uint8_t*)&counter, sizeof(counter));
  // Send 4 bytes (sizeof(x)) starting at the location of x
  LoRa.write((const uint8_t*)&x, sizeof(x));
  // Send 4 bytes (sizeof(z)) starting at the location of z
  LoRa.write((const uint8_t*)&z, sizeof(z));
  // End packet, send it
  LoRa.endPacket();





















 int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Read 4 bytes into a
    int a;
    for (int i = 0; i < sizeof(a); i++) {
      *(((uint8_t*)&a) + i) = (uint8_t)LoRa.read();
    }
    char abc = a;
    // Read 4 bytes into counter
    int counter;
    for (int i = 0; i < sizeof(counter); i++) {
      *(((uint8_t*)&counter) + i) = (uint8_t)LoRa.read();
    }
    // Read 4 bytes into x
    float x;
    for (int i = 0; i < sizeof(x); i++) {
      *(((uint8_t*)&x) + i) = (uint8_t)LoRa.read();
    }
    // Read 4 bytes into z
    float z;
    for (int i = 0; i < sizeof(z); i++) {
      *(((uint8_t*)&z) + i) = (uint8_t)LoRa.read();
    }
    // Display read values
    Serial.print("a = ");
    Serial.print(abc);
    Serial.print("  counter = ");
    Serial.print(counter);
    Serial.print("  x = ");
    Serial.print(x);
    Serial.print("  z = ");
    Serial.print(z);
    Serial.print("  with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}














void print_compressed(char *in, int len) {
  int l;
  byte bit;
  //Serial.write("\nCompressed bits:");
  for (l=0; l<len*8; l++) {
    bit = (in[l/8]>>(7-l%8))&0x01;
    //Serial.print((int)bit);
    //if (l%8 == 7) Serial.print(" ");
  }
}

void loop() {
  char* dump = (char)LoRa.read();
  char in[255];
  strcpy(in, dump);
  char str[] = in;
  char cbuf[300];
  char dbuf[300];

  int len = sizeof(str);

  if (len > 0) {
    memset(cbuf, 0, sizeof(cbuf));
    int ctot = shox96_0_2_compress(str, len, cbuf, NULL);
    print_compressed(cbuf, ctot);
    memset(dbuf, 0, sizeof(dbuf));
    int dlen = shox96_0_2_decompress(cbuf, ctot, dbuf, NULL);
    dbuf[dlen] = 0;

    float perc = (dlen-ctot);
    perc /= dlen;
    perc *= 100;

    Serial.print(ctot);
    Serial.write(",");
    Serial.println(dlen);
  }
  delay(1000);
}




https://lowpowerlab.com/forum/rf-range-antennas-rfm69-library/sending-first-packet-with-rfm95-lora-module/




// rf95_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf95_server
// Tested with Anarduino MiniWirelessLoRa

#include <SPI.h>
#include <RH_RF95.h>

#ifdef __AVR_ATmega1284P__
  #define LED           15 // Moteino MEGAs have LEDs on D15
  #define FLASH_SS      23 // and FLASH SS on D23
#else
  #define LED           9 // Moteinos have LEDs on D9
  #define FLASH_SS      8 // and FLASH SS on D8
#endif

// Singleton instance of the radio driver
RH_RF95 rf95;

//variables used in formatting:
byte sendLen;
char Pstr[10];
char buffer[50]; //final byte array that gets passed to radio.send

int data_to_send = 43;

void setup() 
{
  Serial.begin(115200);
  if (!rf95.init())
    Serial.println("init failed");
  else Serial.println("init OK - 915mhz");
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
  rf95.setFrequency(915);
}

void loop()
{
  Serial.println("Sending to rf95_server");
  // Send a message to rf95_server

  
  // byte data[] = "hello";
  // rf95.send(data, sizeof(data));

  // dtostrf(P, 3,2, Pstr);  // convert a double variable into a small string (byte array) (float variable to be read, length of string being created inc decimal point, number of digits after DP to print, array to store results)
    sprintf(buffer, "%d", data_to_send);
    sendLen = strlen(buffer);  //get the length of buffer

    rf95.send(buffer, sendLen); //finally pass the string (byte array) to the radio to send


  rf95.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (rf95.waitAvailableTimeout(3000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);    
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is rf95_server running?");
  }
  Blink(LED,3);
  delay(200);
}

void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}






