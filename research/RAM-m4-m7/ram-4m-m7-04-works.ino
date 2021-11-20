// Note: each core can be seperated.

#ifdef CORE_CM7    // Start M7 Core programming

#include "mbed.h"
#include "Arduino.h"

using namespace mbed;
using namespace rtos;

//#define SRAM3_START_ADDRESS       ((uint32_t) 0x30040000)
#define SRAM4_START_ADDRESS       ((uint32_t) 0x38000000)

struct shared_data{
  int M4toM7;
  int M7toM4;
};

int localm7m4 = 0;
int localm4m7 = 0;


// Using AHB SRAM4 at 0x38001000
static struct shared_data * const xfr_ptr = (struct shared_data *) SRAM4_START_ADDRESS;








Thread M7Thread;

void setup(){
  bootM4();

  Serial.begin(115200);
  while (!Serial);

  Serial.println(F("\nStarting M7_M4_sharemem_SRAM on Portenta_H7"));
  Serial.print(F("Using SRAM4 @ 0x")); Serial.println(SRAM4_START_ADDRESS, HEX);


  M7Thread.start(callback(M7ThreadFunc));
}

void M7ThreadFunc(){
  localm7m4 = 777777;
  
  while (true){
    Serial.println("================");
   // digitalWrite(LEDR, LOW);
    xfr_ptr -> M7toM4 = localm7m4;
       // delay(100);
    localm7m4++;
        delay(20);
    Serial.print("Writing M7 to M4, value = "); Serial.println(xfr_ptr -> M7toM4);
    delay(20);
   // digitalWrite(LEDB, HIGH);
    Serial.print("Reading M4 to M7, value = "); Serial.println(xfr_ptr -> M4toM7);

    Serial.println("===========");
   //Serial.println();
    delay(20);
  }
}

void loop(){
  //delay(1000);
}

#endif

//////////////////////////////////////////////////////////




#ifdef CORE_CM4    // Start M4 Core programming


#include "mbed.h"
#include "Arduino.h"

using namespace mbed;
using namespace rtos;

//#define SRAM3_START_ADDRESS       ((uint32_t) 0x30040000)
#define SRAM4_START_ADDRESS       ((uint32_t) 0x38000000)

struct shared_data{
  int M4toM7;
  int M7toM4;
};

int localm7m4 = 0;
int localm4m7 = 0;


static struct shared_data * const xfr_ptr = (struct shared_data *) SRAM4_START_ADDRESS;






Thread M4Thread;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);

  M4Thread.start(callback(M4ThreadFunc));
}

void M4ThreadFunc(){
  localm4m7 = 444444;
  
  while (true){
   // digitalWrite(LEDB, LOW);
    localm4m7++;
    delay(20);   
    xfr_ptr -> M4toM7 = localm4m7;

   // digitalWrite(LEDR, HIGH);

  //  delay(20);
  }
}

void loop(){
  //delay(20);
}

#endif
