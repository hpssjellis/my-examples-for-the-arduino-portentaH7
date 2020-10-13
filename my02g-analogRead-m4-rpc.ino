/*
 * my02g-analogRead-m4-rpc.ino for the Portenta H7
 *
 * The PortentaH7 M4 core can not print to the serial monitor
 * On the M4 core if you do a Serial.Println it goes to the TX RX UART output pins
 * This program uses RPC to redirect Serial.println to the M7 core 
 * so that regular sketches still work with serial monitor output from the M4 core
 *
 * 
 * updated August 2nd, 2020
 * by Jeremy Ellis
 * Twitter @rocksetta
 * Website https://www.rocksetta.com
 *
 *I have re-written this to make larger programs easier
 *by seperating the M7 and M4 code completely.
 *
*/



#ifdef CORE_CM7   // Start M7 programming
 
#include "RPC_internal.h"  // comes with the mbed board installation

void setup() {
   bootM4(); 
   Serial.begin(115200);
   RPC1.begin();
}

void loop() {
  
  // Serial.println("Hello from M7 regular Serial");
   while (RPC1.available()) {
      Serial.write(RPC1.read()); 
   }  
  // delay(1);
}

#endif              // End all M7 core programming

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CORE_CM4    // Start M4 programming

#include "RPC_internal.h"  // comes with the mbed board installation

#define Serial RPC1  // So the M4 regular serial prints to RPC

void setup(){  
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin();
  // while (!Serial);  // Please don't do this it messes up beginners
  
}

void loop() {

  Serial.println( ); delayMicroseconds(1234);
  Serial.println("A0 Analog Read max = 1023, Actual Value: "+String(analogRead(A0)) ); delayMicroseconds(1234);
  Serial.println("A1 Analog Read max = 1023, Actual Value: "+String(analogRead(A1)) ); delayMicroseconds(1234);
  Serial.println("A2 Analog Read max = 1023, Actual Value: "+String(analogRead(A2)) ); delayMicroseconds(1234);
  Serial.println("A3 Analog Read max = 1023, Actual Value: "+String(analogRead(A3)) ); delayMicroseconds(1234);
  Serial.println("A4 Analog Read max = 1023, Actual Value: "+String(analogRead(A4)) ); delayMicroseconds(1234);
  Serial.println("A5 Analog Read max = 1023, Actual Value: "+String(analogRead(A5)) ); delayMicroseconds(1234);
  Serial.println("A6 Analog Read max = 1023, Actual Value: "+String(analogRead(A6)) ); delayMicroseconds(1234);
  Serial.println("-----------------------------------------------------------------"); delayMicroseconds(1234);
  Serial.println(); delayMicroseconds(1234);

  // Flash LED 3 times
  digitalWrite(LED_BUILTIN, LOW);   
  delay(10);                      
  digitalWrite(LED_BUILTIN, HIGH);    
  delay(10);                    

  digitalWrite(LED_BUILTIN, LOW);   
  delay(10);                      
  digitalWrite(LED_BUILTIN, HIGH);    
  delay(10);      
                
  digitalWrite(LED_BUILTIN, LOW);   
  delay(10);                      
  digitalWrite(LED_BUILTIN, HIGH);    
  delay(100);    // longer wait 
                  
}
  


#endif            // End all M4 core programming
