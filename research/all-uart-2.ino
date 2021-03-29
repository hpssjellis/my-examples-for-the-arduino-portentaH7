#include <Arduino.h>

#define ENABLE_HDC_SERIAL0
#define ENABLE_HDC_SERIAL1
#define ENABLE_HDC_SERIAL2
#define ENABLE_HDC_SERIAL3

#if defined(ENABLE_HDC_SERIAL0)
#define HDC_SERIAL0_TX (PA_0)
#define HDC_SERIAL0_RX (PI_9)
UART SerialHDC0(HDC_SERIAL0_TX, HDC_SERIAL0_RX, NC, NC);
#endif

#if defined(ENABLE_HDC_SERIAL1)
#define HDC_SERIAL1_TX (PA_9)
#define HDC_SERIAL1_RX (PA_10)
UART SerialHDC1(HDC_SERIAL1_TX, HDC_SERIAL1_RX, NC, NC);
#endif

#if defined(ENABLE_HDC_SERIAL2)
#define HDC_SERIAL2_TX (PG_14)
#define HDC_SERIAL2_RX (PG_9)
UART SerialHDC2(HDC_SERIAL2_TX, HDC_SERIAL2_RX, NC, NC);
#endif

#if defined(ENABLE_HDC_SERIAL3)
#define HDC_SERIAL3_TX (PJ_8)
#define HDC_SERIAL3_RX (PJ_9)
UART SerialHDC3(HDC_SERIAL3_TX, HDC_SERIAL3_RX, NC, NC);
#endif


void setup(){
    Serial.begin(115200);
   // for (auto now = millis(); !Serial && millis() < now + 2500; delay(10));

   // Serial.println("Portenta H7 J1 and J2 Serial Ports");

#if defined(ENABLE_HDC_SERIAL0)
    SerialHDC0.begin(9600);
   // Serial.println("Printing on SerialHDC0");
   // SerialHDC0.println("Hello, World!");
#endif

#if defined(ENABLE_HDC_SERIAL1)
    SerialHDC1.begin(9600);
    //Serial.println("Printing on SerialHDC1");
    //SerialHDC1.println("Hello, World!");
#endif

#if defined(ENABLE_HDC_SERIAL2)
    SerialHDC2.begin(9600);
    //Serial.println("Printing on SerialHDC2");
    //SerialHDC2.println("Hello, World!");
#endif

#if defined(ENABLE_HDC_SERIAL3)
    SerialHDC3.begin(9600);
    //Serial.println("Printing on SerialHDC3");
   // SerialHDC3.println("Hello, World!");
#endif
}

void loop(){
  
#if defined(ENABLE_HDC_SERIAL0)
  if (SerialHDC0.available()) {     // If anything comes in Serial 
    Serial.write(SerialHDC0.read());   // read it and send it out Serial (USB)
  }
#endif 


#if defined(ENABLE_HDC_SERIAL1)
  if (SerialHDC1.available()) {     // If anything comes in Serial 
    Serial.write(SerialHDC1.read());   // read it and send it out Serial (USB)
  }
#endif 


#if defined(ENABLE_HDC_SERIAL2)
  if (SerialHDC2.available()) {     // If anything comes in Serial 
    Serial.write(SerialHDC2.read());   // read it and send it out Serial (USB)
  }
#endif 


#if defined(ENABLE_HDC_SERIAL3)
  if (SerialHDC3.available()) {     // If anything comes in Serial 
    Serial.write(SerialHDC3.read());   // read it and send it out Serial (USB)
  }
#endif 



}
