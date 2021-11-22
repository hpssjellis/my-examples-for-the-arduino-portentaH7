oes serial#include "mbed.h"
#include "Arduino.h"

using namespace mbed;
using namespace rtos;

#define SRAM3_START_ADDRESS       ((uint32_t) 0x30040000)
#define SRAM4_START_ADDRESS       ((uint32_t) 0x38000000)

// If false => using SRAM4
#define USING_SHARE_MEM_FROM_SRAM3        false   //true

typedef struct
{
  int M4toM7;
  int M7toM4;
} shared_data;

shared_data SRAM_Struct = { 444444, 777777 };

#if USING_SHARE_MEM_FROM_SRAM3
// Using AHB SRAM3 at 0x30040000
static shared_data * const xfr_ptr = (shared_data *) SRAM3_START_ADDRESS;
#else
// Using AHB SRAM4 at 0x38001000
static shared_data * const xfr_ptr = (shared_data *) SRAM4_START_ADDRESS;
#endif
#ifdef CORE_CM7    // Start M7 Core programming

Thread M7Thread;

void M7DelayMillis(uint32_t delayMillis)
{
  uint32_t curMillis = millis();

  while (millis() - curMillis < delayMillis)
    yield();
}

void setup()
{ 
  bootM4();

  M7DelayMillis(2000);

  Serial.begin(115200);
  //while (!Serial);

  M7DelayMillis(500);

  //Serial.println("\nStarting M7_M4_sharemem_SRAM_struct_New1 on Portenta_H7");

#if USING_SHARE_MEM_FROM_SRAM3
  //Serial.print("Using SRAM3 @ 0x"); Serial.println(SRAM3_START_ADDRESS, HEX);
#else
  //Serial.print("Using SRAM4 @ 0x"); Serial.println(SRAM4_START_ADDRESS, HEX);
#endif

  memcpy(xfr_ptr, &SRAM_Struct, sizeof(SRAM_Struct));

  M7DelayMillis(1000);

  M7Thread.start(callback(M7ThreadFunc));

  yield();
}

void M7ThreadFunc()
{
#define CHECK_INTERVAL    1000L

  static uint32_t check_timeout = 0;
  static uint32_t current_millis = 0;

  while (true)
  {
    current_millis = millis();

    if ((current_millis > check_timeout) || (check_timeout == 0))
    {
      (xfr_ptr -> M7toM4)++;

      Serial.print("Writing M7 to M4, value = "); Serial.println(xfr_ptr -> M7toM4);

      Serial.print("===>> Reading M4 to M7, value = "); Serial.println(xfr_ptr -> M4toM7);

      check_timeout = current_millis + CHECK_INTERVAL;
    }

    yield();
  }
}

void loop()
{
  yield();
}

#endif

//////////////////////////////////////////////////////////

#ifdef CORE_CM4    // Start M4 Core programming

Thread M4Thread;
int myStoreFromM7;

void setup()
{
  pinMode(LEDB, OUTPUT);  // portenta blue LED
  M4Thread.start(callback(M4ThreadFunc));
}

void M4ThreadFunc()
{
#define CHECK_INTERVAL    1000L

  static uint32_t check_timeout = 0;
  static uint32_t current_millis = 0;

  while (true )
  {
    current_millis = millis();

    if ((current_millis > check_timeout) || (check_timeout == 0))
    {
      (xfr_ptr -> M4toM7)++;

      check_timeout = current_millis + CHECK_INTERVAL;
      if (myStoreFromM7 !=  xfr_ptr -> M7toM4){
         myStoreFromM7 =  xfr_ptr -> M7toM4;
         digitalWrite(LEDB, !digitalRead(LEDB)); // flip blue LED on and off
     }
    }
  }
}

void loop()
{
  yield();
}

#endif
