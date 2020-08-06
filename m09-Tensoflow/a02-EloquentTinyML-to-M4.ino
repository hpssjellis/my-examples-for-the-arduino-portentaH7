/*
 * Machine Learning for the PortentaH7
 * uses the EloquentTinyML library
 * 
 * Connect an LED to D5 thorugh a resistor to Ground
 * 
 * Load to the M7 core to see if it works
 * Serial ploter and LED should work
 * Note: I re-compile after viewing the serial monitor
 * before viewing the serial plotter
 * 
 * Then load to M4 Core
 * only the LED should work
 * 
 * will need to upload the following to the M7 core to load the M4 core
 * 
 *  
 
void setup() {
  #ifdef CORE_CM7  
     bootM4();
  #endif
}

void loop() {
 
}

 * 
 * By Jeremy Ellis 
 * Twitter @rocksetta
 * Website https://rocksetta.com
 * created Aug 6th, 2020
 * 
*/
#include <EloquentTinyML.h>
// sine_model.h contains the array you exported from the previous step with xxd or tinymlgen
#include "sine_model.h"

#define NUMBER_OF_INPUTS 1
#define NUMBER_OF_OUTPUTS 1
// in future projects you may need to tweek this value: it's a trial and error process
#define TENSOR_ARENA_SIZE 2*1024

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml(sine_model);

int myCounter = 0;

void setup() {
    Serial.begin(115200);
}

void loop() {
    myCounter +=1;
    if (myCounter >= 360){
        myCounter = 0;
    }
    
    float x = myCounter * 3.14/180;  // degrees to radians
    float y = sin(x);
    
    float input[1] = { x };
    float predicted = ml.predict(input);

    // presently serial only works on the M7 core
    Serial.println("sin(" +String(x)+ ") = " + String(y) + "\t predicted: " + String(predicted) );

    // y=1 LED is fully on. The LED's brightness can range from 0-255.
    int brightness = (int)(127.5f * (predicted+1));

    // Set the brightness of the LED. If the specified pin does not support PWM,
    // this will result in the LED being on when y > 127, off otherwise.
    analogWrite(5, brightness);  
    delay(3); // slows the process down a bit to see the sine wave
}
