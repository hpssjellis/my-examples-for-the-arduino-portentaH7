/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/


#include <TensorFlowLite.h>
#include "model.h"
#include "Arduino.h"



/*================= Start Really Advanced Area ===============================*/


#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
//#include "tensorflow/lite/c/c_api.h"












#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_HELLO_WORLD_OUTPUT_HANDLER_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_HELLO_WORLD_OUTPUT_HANDLER_H_



// Called by the main loop to produce some output based on the x and y values
void HandleOutput(tflite::ErrorReporter* error_reporter, float x_value,
                  float y_value);

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_HELLO_WORLD_OUTPUT_HANDLER_H_



#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_HELLO_WORLD_MAIN_FUNCTIONS_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_HELLO_WORLD_MAIN_FUNCTIONS_H_

// Expose a C friendly interface for main functions.
#ifdef __cplusplus
extern "C" {
#endif

// Initializes all data needed for the example. The name is important, and needs
// to be setup() for Arduino compatibility.
void setup();

// Runs one iteration of data gathering and inference. This should be called
// repeatedly from the application code. The name needs to be loop() for Arduino
// compatibility.
void loop();

#ifdef __cplusplus
}
#endif

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_HELLO_WORLD_MAIN_FUNCTIONS_H_




/*================= End Really Advanced Area ===============================*/







/*================= Start Advanced Area ===============================*/


// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;
int inference_count = 0;

// Create an area of memory to use for input, output, and intermediate arrays.
// Minimum arena size, at the time of writing. After allocating tensors
// you can retrieve this value by invoking interpreter.arena_used_bytes().
const int kModelArenaSize = 2468;
// Extra headroom for model + alignment + future interpreter changes.
const int kExtraArenaSize = 560 + 16 + 100;
const int kTensorArenaSize = kModelArenaSize + kExtraArenaSize;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace





/*================= End Advanced Area ===============================*/





// The pin of the Arduino's built-in LED
int led = LED_BUILTIN;

// Track whether the function has run at least once
bool initialized = false;

// Animates a dot across the screen to represent the current x and y values
void HandleOutput(tflite::ErrorReporter* error_reporter, float x_value,
                  float y_value) {
  // Do this only once
  if (!initialized) {
    // Set the LED pin to output
    pinMode(led, OUTPUT);
    initialized = true;
  }

  // Calculate the brightness of the LED such that y=-1 is fully off
  // and y=1 is fully on. The LED's brightness can range from 0-255.
  //int brightness = (int)(127.5f * (y_value + 1));

  // Set the brightness of the LED. If the specified pin does not support PWM,
  // this will result in the LED being on when y > 127, off otherwise.
 // analogWrite(led, brightness);

  // Log the current brightness value for display in the Arduino plotter
 // TF_LITE_REPORT_ERROR(error_reporter, "%d\n", brightness);
}


#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_HELLO_WORLD_CONSTANTS_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_HELLO_WORLD_CONSTANTS_H_

// This constant represents the range of x values our model was trained on,
// which is from 0 to (2 * Pi). We approximate Pi to avoid requiring additional
// libraries.
const float kXrange = 2.f * 3.14159265359f;

// This constant determines the number of inferences to perform across the range
// of x values defined above. Since each inference takes time, the higher this
// number, the more time it will take to run through the entire range. The value
// of this constant can be tuned so that one full cycle takes a desired amount
// of time. Since different devices take different amounts of time to perform
// inference, this value should be defined per-device.
extern const int kInferencesPerCycle;

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_HELLO_WORLD_CONSTANTS_H_


// This is tuned so that a full cycle takes ~4 seconds on an Arduino MKRZERO.
const int kInferencesPerCycle = 1000;










// The name of this function is important for Arduino compatibility.
void setup() {
  Serial.begin(9600);
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.


  
 // model = tflite::GetModel(g_model);  // name important
  model = tflite::GetModel(model_tflite);  // name from the tflite converter


  
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // This pulls in all the operation implementations we need.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::AllOpsResolver resolver;

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);

  // Keep track of how many inferences we have performed.
  inference_count = 0;
}








// The name of this function is important for Arduino compatibility.
void loop() {
  // Calculate an x value to feed into the model. We compare the current
  // inference_count to the number of inferences per cycle to determine
  // our position within the range of possible x values the model was
  // trained on, and use this to calculate a value.


/*

  
  float position = static_cast<float>(inference_count) /
                   static_cast<float>(kInferencesPerCycle);
  float x_val = position * kXrange;

  // Place our calculated x value in the model's input tensor
  input->data.f[0] = x_val;

  // Run inference, and report any error
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on x_val: %f\n",
                         static_cast<double>(x_val));
    return;  
  } 

*/

//TfLiteTensor* input_tensor = TfLiteInterpreterGetInputTensor(interpreter, 0);
 

   
//   Serial.println("  interpreter.get_input_details(): " + String(input_tensor) );


 size_t myUsedArena =  interpreter->arena_used_bytes();

 int myType =  input->type; 
 String myTensorType = "Not Set";    
   if (myType == 0){myTensorType  = "kTfLiteNoType"; }  
   if (myType == 1){myTensorType  = "kTfLiteFloat32"; }  
   if (myType == 2){myTensorType  = "kTfLiteInt32"; }   
   if (myType == 3){myTensorType  = "kTfLiteUInt8"; }   
   if (myType == 4){myTensorType  = "kTfLiteInt64"; }   
   if (myType == 5){myTensorType  = "kTfLiteString"; }  
   if (myType == 6){myTensorType  = "kTfLiteBool"; }    
   if (myType == 7){myTensorType  = "kTfLiteInt16"; }    
   if (myType == 8){myTensorType  = "kTfLiteComplex64"; }    
   if (myType == 9){myTensorType  = "kTfLiteInt8"; }    
   if (myType == 10){myTensorType = "kTfLiteFloat16"; }    
   if (myType == 11){myTensorType = "kTfLiteFloat64"; }   
   if (myType == 12){myTensorType = "kTfLiteComplex128"; } 
   
   Serial.println("     const Arena kModelArenaSize: " + String(kModelArenaSize) );
   Serial.println(" interpreter->arena_used_bytes(): " + String(myUsedArena) );
  
   Serial.println("       interpreter.inputs_size(): " + String(interpreter->inputs_size()) );
   Serial.println("       interpreter.outputs_size(): " + String(interpreter->outputs_size()) );
   Serial.println("       interpreter.tensors_size(): " + String(interpreter->tensors_size()) );
   Serial.println("       interpreter.tensors_size(): " + String(interpreter->tensors_size()) );
   
   Serial.println();
   Serial.println("                     input->type: " + String(input->type) + " = " + myTensorType);
   Serial.println("               input->dims->size: " + String(input->dims->size) );
   int mySize = input->dims->size;


   
   for (int i = 0; i < mySize; i++) {
     int myIn = input->dims->data[i]; 
     Serial.println( "            input->dims->data[" + String(i) + "]: " + String(myIn) );
       
   }

   Serial.println(  );
   int myType2 =  output->type; 
   String myTensorType2 = "Not Set"; 
   if (myType2 == 0){myTensorType2  = "kTfLiteNoType"; }  
   if (myType2 == 1){myTensorType2  = "kTfLiteFloat32"; }  
   if (myType2 == 2){myTensorType2  = "kTfLiteInt32"; }   
   if (myType2 == 3){myTensorType2  = "kTfLiteUInt8"; }   
   if (myType2 == 4){myTensorType2  = "kTfLiteInt64"; }   
   if (myType2 == 5){myTensorType2  = "kTfLiteString"; }  
   if (myType2 == 6){myTensorType2  = "kTfLiteBool"; }    
   if (myType2 == 7){myTensorType2  = "kTfLiteInt16"; }    
   if (myType2 == 8){myTensorType2  = "kTfLiteComplex64"; }    
   if (myType2 == 9){myTensorType2  = "kTfLiteInt8"; }    
   if (myType2 == 10){myTensorType2 = "kTfLiteFloat16"; }    
   if (myType2 == 11){myTensorType2 = "kTfLiteFloat64"; }   
   if (myType2 == 12){myTensorType2 = "kTfLiteComplex128"; }  


   
   Serial.println("                     output->type: " + String(output->type) + " = " + myTensorType2);
   Serial.println("               output->dims->size: " + String(output->dims->size) );
   int mySize2 = output->dims->size;


   
   for (int i = 0; i < mySize2; i++) {
     int myOut = output->dims->data[i];      
     Serial.println( "            output->dims->data[" + String(i) + "]: " + String(myOut) );

   }


   Serial.println("-----------------------------------------------------------" );

  for (size_t tensor_index = 0; tensor_index < interpreter->tensors_size(); tensor_index++) {
    TfLiteTensor* tensor = interpreter->tensor(static_cast<int>(tensor_index));
    //printf("Tensor %3zu %-20s %10s %15s %10zu bytes (%4.1f MB) ", tensor_index,
    //       tensor->name, TensorTypeName(tensor->type),
    //       AllocTypeName(tensor->allocation_type), tensor->bytes,
     //      (static_cast<float>(tensor->bytes) / (1 << 20)));
   // PrintTfLiteIntVector(tensor->dims);
   Serial.print("Tensor index: " + String(tensor_index) );
   Serial.print(", Type: " + String(tensor->type) );
   Serial.println(", Size in Bytes: " + String(tensor->bytes) );
   Serial.print("tensor->dims->data[k]" );
   for (int k = 0; k < tensor->dims->size; k++) {
      Serial.print(", K: " + String(k)+ ", Data: "+ String(tensor->dims->data[k]));
   }
   Serial.println( );
 }





/*
   Serial.println();
   Serial.println("                     output->type: " + String(output->type) );
   Serial.println("               output->dims->size: " + String(output->dims->size) );
   Serial.println("            output->dims->data[0]: " + String(output->dims->data[0]) );
   Serial.println("            output->dims->data[1]: " + String(output->dims->data[1]) );
  
   
   Serial.println("-----------------------------------------------------------" );
   Serial.println("            input->dims->data[2]: " + String(input->dims->data[2]) );
   Serial.println("            input->dims->data[3]: " + String(input->dims->data[3]) );
   Serial.println("            input->dims->data[4]: " + String(input->dims->data[4]) );
   Serial.println("            input->dims->data[5]: " + String(input->dims->data[5]) );
   Serial.println("            input->dims->data[6]: " + String(input->dims->data[6]) );
   
   Serial.println("------------" );
   Serial.println("            output->dims->data[2]: " + String(output->dims->data[2]) );
   Serial.println("            output->dims->data[3]: " + String(output->dims->data[3]) );
   Serial.println("            output->dims->data[4]: " + String(output->dims->data[4]) );
   Serial.println("            output->dims->data[5]: " + String(output->dims->data[5]) );
   Serial.println("            output->dims->data[6]: " + String(output->dims->data[6]) );


    */
   Serial.println("-----------------------------------------------------------" );  
   Serial.println();
  



  // Output the results. A custom HandleOutput function can be implemented
  // for each supported hardware target.
  //HandleOutput(error_reporter, x_val, y_val);

  // Increment the inference_counter, and reset it if we have reached
  // the total number per cycle
  inference_count += 1;
  if (inference_count >= kInferencesPerCycle) inference_count = 0;

  //TfLiteTensor* input = interpreter.input(0);




  delay(3000);
  
}
