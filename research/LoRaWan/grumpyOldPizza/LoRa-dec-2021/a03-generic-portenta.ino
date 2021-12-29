//char rx_buf[512];
//char tx_buf[512];
char rx_buf[64];
char tx_buf[64];

//int baud = 115200;
uint8_t parity = 0;

int rx = 0;
int tx = 0;

bool mySent = false;


void setup() {
   SerialLoRa.begin(9600); // for LoRa must be 9600
   Serial.begin(115200);
     
    pinMode(LEDR, OUTPUT); 
    pinMode(LEDG, OUTPUT);   
    pinMode(LEDB, OUTPUT);  
    
    digitalWrite(LEDR, HIGH); 
    digitalWrite(LEDG, HIGH); 
    digitalWrite(LEDB, HIGH); 
  // put your setup code here, to run once:

}

void loop() {

  delay(10);

  // Back and forth to the Murata module
  while (Serial.available()) {      // If anything comes in Serial (USB),
    tx_buf[tx++] = Serial.read();   // read it and send it out Serial1 (pins 0 & 1)
  }

  if (tx > 0 ) {
    SerialLoRa.write(tx_buf, tx);
    tx = 0;
  }

  while (SerialLoRa.available()) {      // If anything comes in Serial (USB),
    rx_buf[rx++] = SerialLoRa.read();   // read it and send it out Serial1 (pins 0 & 1)
  }

  if (rx > 0) {
    Serial.write(rx_buf, rx);
    rx = 0;
  }



}
