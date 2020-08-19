



#include <RocksettaTinyML.h>

namespace Rocksetta {
    namespace TinyML {

        /**
         * Rocksetta interface to Tensorflow Lite for Microcontrollers
         *
         * @tparam inputSize
         * @tparam outputSize
         * @tparam tensorArenaSize how much memory to allocate to the tensors
         */
        template<size_t inputSize, size_t outputSize, size_t tensorArenaSize>
        class TfLite {
        public:
            /**
             * Contructor
             * @param modelData a model as exported by tinymlgen
             */
            TfLite() :
                failed(false) {
            }

            bool begin(const unsigned char *modelData) {
                static tflite::MicroErrorReporter microReporter;
                static tflite::ops::micro::AllOpsResolver resolver;

                reporter = &microReporter;
                model = tflite::GetModel(modelData);

                // assert model version and runtime version match
                if (model->version() != TFLITE_SCHEMA_VERSION) {
                    failed = true;
                    Serial.println("Version mismatch");
                    reporter->Report(
                            "Model provided is schema version %d not equal "
                            "to supported version %d.",
                            model->version(), TFLITE_SCHEMA_VERSION);

                    return false;
                }

                static tflite::MicroInterpreter interpreter(model, resolver, tensorArena, tensorArenaSize, reporter);

                if (interpreter.AllocateTensors() != kTfLiteOk) {
                    failed = true;
                    Serial.println("Allocation failed");
                    reporter->Report("AllocateTensors() failed");

                    return false;
                }

                input = interpreter.input(0);
                output = interpreter.output(0);

                this->interpreter = &interpreter;

                return true;
            }



            /**
             * Test if the initialization completed fine
             */
            bool initialized() {
                return !failed;
            }



            /**
             * Run inference
             * @return output[0], so you can use it directly if it's the only output
             */

            uint8_t predict(int32 *input, float *output = NULL) {
                // abort if initialization failed
                if (!initialized())
                    return sqrt(-1);

                // copy input
                for (size_t i = 0; i < inputSize; i++)
                    this->input->data.f[i] = input[i];

                if (interpreter->Invoke() != kTfLiteOk) {
                    reporter->Report("Inference failed");

                    return sqrt(-1);
                }

                 //copy output  output is a pointer which might be a better way to deal with this
                if (output != NULL) {
                    memcpy(output, this->output->data.f, sizeof(float) * outputSize);
                }

               // return this->output->data.f[0]; // just send back the first value for testing
                return 1;  // means it worked
            }






        protected:
            bool failed;
            uint8_t tensorArena[tensorArenaSize];
            tflite::ErrorReporter *reporter;
            tflite::MicroInterpreter *interpreter;
            TfLiteTensor *input;
            TfLiteTensor *output;
            const tflite::Model *model;
        };
    }
}


















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

// sine_model.h contains the array you exported from the previous step with xxd or tinymlgen
#include "a02_digital_model.h"

#define NUMBER_OF_INPUTS 8

#define NUMBER_OF_OUTPUTS 4

// in future projects you may need to tweek this value: it's a trial and error process

// Create an area of memory to use for input, output, and intermediate arrays.
// The size of this will depend on the model you're using, and may need to be
// determined by experimentation.
// from other examples  constexpr int kTensorArenaSize = 60 * 1024;

#define TENSOR_ARENA_SIZE 20*1024   






Rocksetta::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;


void setup() {
    randomSeed(analogRead(A0));
    Serial.begin(115200);
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);
    ml.begin(model_tflite);  // the model inside the a02_digital_model.h file
}

void loop() {

    int myIn1 = rand() % 2;  // either 0 or 1
    int myIn2 = rand() % 2;  // I would do a for loop but this was easy.
    int myIn3 = rand() % 2;
    int myIn4 = rand() % 2;
    int myIn5 = rand() % 2;
    int myIn6 = rand() % 2;
    int myIn7 = rand() % 2;
    int myIn8 = rand() % 2;
    int32 input[] = { myIn1, myIn2, myIn3, myIn4, myIn5, myIn6, myIn7, myIn8 };   // 8 inputs.
     
    float myOutput[4];   // 4 output floats
   // float predicted = ml.predict(input, myOutput); // predicted is just the first of the outputs for testing. output has the array
    
    uint8_t itWorked = ml.predict(input, myOutput); // predicted is just the first of the outputs for testing. output has the array

     
  //  float itWorked = ml.predict(input, myOutput); // predicted is just the first of the outputs for testing. output has the array
   if (itWorked == 1.0){ 

       
    if (myOutput[0] >= 0.5){
       digitalWrite(LEDR, LOW);   // grounds the LED turns it on only on portenta and nano 33 BLE
       } else {  
       digitalWrite(LEDR, HIGH);  //  turns it off only on portenta and nano 33 BLE
    }
       
    if (myOutput[1] >= 0.5){
       digitalWrite(LEDG, LOW);   // grounds the LED turns it on only on portenta and nano 33 BLE
       } else {  
       digitalWrite(LEDG, HIGH);  //  turns it off only on portenta and nano 33 BLE
    }  
         
    if (myOutput[2] >= 0.5){
       digitalWrite(LEDB, LOW);   // grounds the LED turns it on only on portenta and nano 33 BLE
       } else {  
       digitalWrite(LEDB, HIGH);  //  turns it off only on portenta and nano 33 BLE
    }

    

    // presently serial only works on the M7 core

       Serial.println("All 8 inputs: " +  String(input[0])+  String(input[1])+  String(input[2])+  String(input[3])+  String(input[4])+ String(input[5])+  String(input[6])+  String(input[7]) ); 

       Serial.println("All 4 predictions, Red:" + String(myOutput[0],4) +", Green:"+ String(myOutput[1],4) +", Blue:"+ String(myOutput[2],4) +", "+ String(myOutput[3],4) );
       Serial.println("-------------------------------------------------------");
 }  else {
      Serial.println("Something bad happened during the prediction."); 
  }


    delay(6000); // slows things down
}
