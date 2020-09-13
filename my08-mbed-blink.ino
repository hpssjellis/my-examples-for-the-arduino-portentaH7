#include "mbed.h"
  mbed:: DigitalOut LD1(PK_5); // red
  mbed:: DigitalOut LD2(PK_6); // green
  mbed:: DigitalOut LD3(PK_7); // blue

void setup() {
}

void loop() {
  LD1 = 0;   // red on
  LD2 = 0;   // green on
  LD3 = 0;   // blue on
  wait_us(1000000);  // 1 million = 1 second delay
  
  LD1 = 1;  // off
  LD2 = 1;
  LD3 = 1;
  wait_us(2000000);
}
