#include "mbed.h"
  mbed:: DigitalOut LD1(PK_5);
  mbed:: DigitalOut LD2(PK_6);
  mbed:: DigitalOut LD3(PK_7);

void setup() {
}

void loop() {
  LD1 = 0;
  LD2 = 0;
  LD3 = 0;
  wait_us(1000000);
  
  LD1 = 1;
  LD2 = 1;
  LD3 = 1;
  wait_us(1000000);
}

