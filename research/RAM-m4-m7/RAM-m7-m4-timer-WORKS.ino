
// Original by Khoi Hoang (Github @khoih-prog ) and Jeremy Ellis (Github @hpssjellis )
// Note: each core can be seperated to it's own IDE folder

#ifdef CORE_CM7    // Start M7 Core programming

#include "mbed.h"
#include "Arduino.h"

using namespace mbed;
using namespace rtos;

//#define SRAM4_START_ADDRESS       ((uint32_t) 0x30040000)   
#define SRAM4_START_ADDRESS       ((uint32_t) 0x38000000)

struct shared_data{
  int M4toM7;
  int M7toM4;
};

int myStuff;
int localm7m4 = 0;
int localm4m7 = 0;
unsigned long myDelay = 43210;  // microSeconds not milliSeconds
unsigned long delayStart = 0;  


// Using AHB SRAM4 at 0x38000000
static struct shared_data * const xfr_ptr = (struct shared_data *) SRAM4_START_ADDRESS;



Thread M7Thread;

void setup(){
  bootM4();

  Serial.begin(115200);

  //while (!Serial);  // still blocking when removed? 
  
  // Following line is needed, not sure why? 
  Serial.println(SRAM4_START_ADDRESS, HEX); // MUST HAVE



  yield();
  
  M7Thread.start(callback(M7ThreadFunc));
  yield();
}

void M7ThreadFunc(){
  localm7m4 = 777777;
  
  while (true) {  
   if ( (micros() - delayStart ) >= myDelay) {
    delayStart = micros(); //  reset the delay time 
    yield();
    localm7m4++;
    xfr_ptr -> M7toM4 = localm7m4;
    
    Serial.print("M7 to M4: "); Serial.println(xfr_ptr -> M7toM4);
    Serial.print("M4 to M7: "); Serial.println(xfr_ptr -> M4toM7);

    Serial.println();        
    yield();
    //delay(20);
    

   //delayMicroseconds(43210);    // Note: micro-seconds not milli-seconds
  }
 }
}

void loop(){
  yield();
}

#endif

//////////////////////////////////////////////////////////




#ifdef CORE_CM4    // Start M4 Core programming


#include "mbed.h"
#include "Arduino.h"

using namespace mbed;
using namespace rtos;


//#define SRAM4_START_ADDRESS       ((uint32_t) 0x30040000)   
#define SRAM4_START_ADDRESS       ((uint32_t) 0x38000000)

struct shared_data{
  int M4toM7;
  int M7toM4;
};

int localm7m4 = 0;
int localm4m7 = 0;
unsigned long myDelay = 43210;  // microSeconds not milliSeconds
unsigned long delayStart = 0;  


static struct shared_data * const xfr_ptr = (struct shared_data *) SRAM4_START_ADDRESS;


int myStoreFromM7;

Thread M4Thread;

void setup(){
  pinMode(LEDB, OUTPUT);  // portenta blue LED
  yield();
  M4Thread.start(callback(M4ThreadFunc));
  yield();
}

void M4ThreadFunc(){
  localm4m7 = 44444444;
  
  while (true){
    if ( (micros() - delayStart ) >= myDelay) {
    delayStart = micros(); //  reset the delay time
    localm4m7++;
 
    xfr_ptr -> M4toM7 = localm4m7;

    // test if M4 an read struct changed on M7 
    if (myStoreFromM7 !=  xfr_ptr -> M7toM4){
        myStoreFromM7 =  xfr_ptr -> M7toM4;
        digitalWrite(LEDB, !digitalRead(LEDB)); // flip blue LED on and off
     }
     yield();
    // delay(20);  
   // delayMicroseconds(43210); //Note: micro-seconds not milli-seconds
  }
 }
}

void loop(){
  yield();
}

#endif
