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
#include <EloquentTinyML_digital.h>

// sine_model.h contains the array you exported from the previous step with xxd or tinymlgen
#include "a02_digital_model.h"

#define NUMBER_OF_INPUTS 8
#define TYPE_OF_INPUTS int32
#define NUMBER_OF_OUTPUTS 4
#define TYPE_OF_OUTPUTS float
// in future projects you may need to tweek this value: it's a trial and error process

// Create an area of memory to use for input, output, and intermediate arrays.
// The size of this will depend on the model you're using, and may need to be
// determined by experimentation.
// from other examples  constexpr int kTensorArenaSize = 60 * 1024;


//#define TENSOR_ARENA_SIZE 2*1024   
#define TENSOR_ARENA_SIZE 8*1024   // ???
//#define TENSOR_ARENA_SIZE 60*1024  


Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;


void setup() {
    randomSeed(analogRead(A0));
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    ml.begin(model_tflite);  // the model inside the a02_digital_model.h file
}

void loop() {

    int myInA = rand() % 2;   // either 0 or 1
    int myInB = rand() % 2;
    int myInC = rand() % 2;
    int myInD = rand() % 2;
    int myInE = rand() % 2;
    int myInF = rand() % 2;
    int myInG = rand() % 2;
    int myInH = rand() % 2;
    int32 input[] = { myInA, myInB, myInC, myInD, myInE, myInF, myInG, myInH };   // 8 inputs. 
    float myOutput[4];   // 4 output floats
    float predicted = ml.predict(input, myOutput); // predicted is just the first of the outputs for testing. output has the array
  //  if (predicted >= 0.5){
   //    digitalWrite(LED_BUILTIN, LOW); // grounds the LED turns it on only on portenta and nano 33 BLE
  //  } else {  
   //    digitalWrite(LED_BUILTIN, HIGH); //  turns it off only on portenta and nano 33 BLE
   // }

    // presently serial only works on the M7 core
    Serial.println("All 8 inputs: " +  String(input[0])+  String(input[1])+  String(input[2])+  String(input[3])+  String(input[4])+ String(input[5])+  String(input[6])+  String(input[7]) ); 

    Serial.println("All 4 predictions: " + String(myOutput[0],4) +", "+ String(myOutput[1],4) +", "+ String(myOutput[2],4) +", "+ String(myOutput[3],4) );



    delay(6000); // slows things down
}
