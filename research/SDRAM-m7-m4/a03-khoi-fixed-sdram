// Original by Khoi Hoang (Github @khoih-prog ) and Jeremy Ellis (Github @hpssjellis )
// Note: each core can be separated to it's own IDE folder

#define STARTING_M4_VALUE         0
#define STARTING_M7_VALUE         0

#include "mbed.h"
#include "Arduino.h"

using namespace mbed;
using namespace rtos;

struct shared_data
{
  uint64_t M4toM7;
  uint64_t M7toM4;
};

#define SRAM3_START_ADDRESS       ((uint32_t) 0x30040000)
#define SRAM4_START_ADDRESS       ((uint32_t) 0x38000000)

// Using AHB SRAM4 at 0x38000000
#define SRAM_START_ADDRESS        SRAM4_START_ADDRESS

////////////////////////////////////////////////////////////////////

#ifdef CORE_CM7    // Start M7 Core programming

uint64_t localm7m4 = STARTING_M7_VALUE;

// Current 1 sec
unsigned long myDelay = 1000000;     // microSeconds not milliSeconds
unsigned long delayStart = 0;

static struct shared_data * const xfr_ptr = (struct shared_data *) SRAM_START_ADDRESS;

Thread M7Thread;

////////////////////////////////////////////

void MPU_Config()
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SDRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = D3_SRAM_BASE;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

void setup()
{
  MPU_Config();
  bootM4();

  Serial.begin(115200);

  //while (!Serial);

  // Following issue solved by starting RPC. Not sure why.
  // Following line is needed, not sure why?
  //Serial.println(SRAM_START_ADDRESS, HEX); // MUST HAVE

  M7Thread.start(callback(M7ThreadFunc));
}

////////////////////////////////////////////

void M7ThreadFunc()
{
  static uint64_t startingMicros = micros();
  static uint64_t timestamp;

  localm7m4 = STARTING_M7_VALUE;

  while (true)
  {
    timestamp = micros();

    if ( (micros() - delayStart ) >= myDelay)
    {
      delayStart = micros(); //  reset the delay time
      
      yield();
      
      localm7m4++;
      xfr_ptr -> M7toM4 = localm7m4;

      Serial.print("M7 to M4: "); Serial.println(xfr_ptr -> M7toM4);
      Serial.print("M4 to M7: "); Serial.println(xfr_ptr -> M4toM7);

      // NUmber of M4 increment per milliseconds, around max. 1970 per ms
      // No M4 RPC                => 1980 - 2600 inc / ms
      // Both M4 and M7 RPC       => 0000 - 1970 inc / ms (slower a little bit !!!)
      Serial.print("Inc_Per_mS: "); Serial.println( ( (float) xfr_ptr -> M4toM7 - STARTING_M4_VALUE) / ( ( timestamp - startingMicros ) / 1000 ) );
      Serial.println();
    }
  }
}

////////////////////////////////////////////

void loop()
{
  // yield();
}

#endif

////////////////////////////////////////////////////////////////////

#ifdef CORE_CM4    // Start M4 Core programming

uint64_t localm4m7 = STARTING_M4_VALUE;

static struct shared_data * const xfr_ptr = (struct shared_data *) SRAM_START_ADDRESS;

uint64_t myStoreFromM7 = STARTING_M7_VALUE;

Thread M4Thread;

////////////////////////////////////////////

void setup()
{
  pinMode(LEDB, OUTPUT);  // portenta blue LED
  M4Thread.start(callback(M4ThreadFunc));
}

////////////////////////////////////////////

void M4ThreadFunc()
{
  localm4m7 = STARTING_M4_VALUE;
  
  while (true)
  {
    // without this => not increase ???
    delayMicroseconds(0);
    
    localm4m7++;

    xfr_ptr -> M4toM7 = localm4m7;

    // test if M4 an read struct changed on M7
    if (myStoreFromM7 !=  xfr_ptr -> M7toM4)
    {
      myStoreFromM7 = xfr_ptr -> M7toM4;
      digitalWrite(LEDB, !digitalRead(LEDB)); // flip blue LED on and off
    }
  }
}

////////////////////////////////////////////

void loop()
{
}

#endif
