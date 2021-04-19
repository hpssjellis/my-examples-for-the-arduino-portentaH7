
int myLastUart = -1;



UART mySerial8(PA_2,  PA_3,  NC, NC);  // murata modem,   TX, RX, RTS, CTS  NOTE: NC means not connected


void myLedBlue_thread(){
   while (true) {
      digitalWrite(LEDB, !digitalRead(LEDB));   //switch on / off
      ThisThread::sleep_for(1000);
      if (myLastUart >=0) {
         Serial.println("Last Serial message was from UART:" + String(myLastUart));
         myLastUart = -1;
        }
      Serial.println("Waiting...");
   }
}


void setup(){
    pinMode(LEDB, OUTPUT);   // LEDB = blue, LEDG or LED_BUILTIN = green, LEDR = red 
    Serial.begin(115200);
    mySerial8.begin(9600);
    
    thread.start(myLedBlue_thread);
}

void loop(){

   if (mySerial8.available()) {    
      Serial.write(mySerial8.read()); 
      myLastUart = 8;  
   }

}
