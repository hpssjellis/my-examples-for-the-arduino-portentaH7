/* 
 *  makerML_template.ino
 *  made with Arduino_TensorFlowLite version 2.1.0-ALPHA-precompiled
 *  
 *  Getting started with Machine Learning using only the Arduino_TensorflowLite library
 *  no extra libraries
 *  
 *  Copyright 2019 The TensorFlow Authors. All Rights Reserved.
 *  
 *  Changes made August 2020 by
 *  Jeremy Ellis
 *  Twitter @rocksetta
 *  website https://www.rocksetta.com/
 *  
 *  
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ==============================================================================
 * 
 * Machine Learning from TensorflowJS in the browser 
 * to Arduino style microcontrollers. I use a three step process
 * 
 * 
 * 1. Design your Machine Learning model usiing Tensorflowjs in browser
 *  https://rocksetta.com/tensorflowjs/
 * 
 * 2. Convert your TensorflowJS Machine Learning model to #tensorflowMicro using an online docker called gitpod
 *  (or use your own command line) and create the model.h header file containing your Machine Learning model
 *  https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/tree/master/m09-Tensoflow/tfjs-convert-to-arduino-header
 * 
 * 3. Run your model using this sketch.
 * other starting sketches at
 * 
 *  https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/tree/master/m09-Tensoflow
 * 
 *  Hashtags
 *  #TensorflowLiteMicro
 *  #TensorflowMicro
 *  #TensorflowLiteForArduino
 *  #tfMicro
 *  #TinyMY
 *  #MakerML
 * 
 *  By Jeremy Ellis
 *  Twitter @rocksetta
 *  website https://www.rocksetta.com/
 *  
 *  Use at your own risk!
 */


#include "model.h"  // name of the tabbed file containing your machine learning model


#include "Arduino.h"
#include <TensorFlowLite.h>

// A few important global variables

// Create an area of memory to use for input, output, and intermediate arrays.
constexpr int kTensorArenaSize = 15 * 1024;  // Original was 2 * 1024, I like 20 * 1024 for large boards
uint8_t tensor_arena[kTensorArenaSize];

//TfLiteStatus invoke_status;
int myZeroIfPredictionOk;

/*================= Start Advanced Area ===============================*/

#include "tensorflow/lite/micro/all_ops_resolver.h"
//#include "tensorflow/lite/micro/kernels/micro_ops.h"
//#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"

#include "tensorflow/lite/micro/micro_error_reporter.h"  // may have issues on M4 core
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "tensorflow/lite/c/common.h"
//#include "tensorflow/lite/c/c_api.h" // has interesting funcitons, not in main library


// Start Debug.cc information    ----------------------------------------------------------

 #if  defined (CORE_CM7)  ||  defined (YOUR_BOARD1) // CORE_CM7 is for the PortentaH7 outer core
 
    // do abosolutely nothing the default works
    
 #elif defined (CORE_CM4)  || defined (NANO_33_BLE) ||  defined (YOUR_BOARD2)  // CORE_CM4 is for the PortentaH7 inner core
 
     #define DEBUG_SERIAL_OBJECT (Serial) 

     extern "C" void DebugLog(const char* s) {
        static bool is_initialized = false;
        if (!is_initialized) {
           DEBUG_SERIAL_OBJECT.begin(9600);
           is_initialized = true;
        }
        DEBUG_SERIAL_OBJECT.print(s);
     }

 #elif defined (__SAM3X8E__)  ||  defined (YOUR_BOARD3) // Arduino UNO style boards

     #define DEBUG_SERIAL_OBJECT (SerialUSB) 

     extern "C" void DebugLog(const char* s) {
        static bool is_initialized = false;
        if (!is_initialized) {
           DEBUG_SERIAL_OBJECT.begin(9600);
           is_initialized = true;
        }
        DEBUG_SERIAL_OBJECT.print(s);
     }
 #elif defined (SEEED_XIAO_M0)  ||  defined (YOUR_BOARD4) // The new $5 USD Seeeduino XIAO board

     #define CFG_TUSB_DEBUG
     
 #else
   // don't do any debugging until you figure out your board  
   
   extern "C" void DebugLog(const char* s) {
     // Do not log debug info
   } 
 #endif


/*
 * nano_33_iot.build.board=SAMD_NANO_33_IOT  // have not got it working yet
 * 
*/

// End Debug.cc information    ----------------------------------------------------------


namespace { // Start namespace----------------------------------------------------------

   // define needed variables
   tflite::ErrorReporter* error_reporter = nullptr;
   const tflite::Model* model = nullptr;
   tflite::MicroInterpreter* interpreter = nullptr;
   TfLiteTensor* input = nullptr;
   TfLiteTensor* output = nullptr;


}  // END namespace----------------------------------------------------------



/*================= End Advanced Area ===============================*/


/*================= Start Smart Area ================================*/

void modelSetup(const unsigned char theModel[]){

  // NOLINTNEXTLINE(runtime-global-variables)
  
   static tflite::MicroErrorReporter micro_error_reporter;
  
   error_reporter = &micro_error_reporter;  

   // Map the model into a usable data structure. This doesn't involve any
   // copying or parsing, it's a very lightweight operation.


   model = tflite::GetModel(theModel);  // name from the tflite converter model.h file

  
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


  /* // replace the above line if you know each operation to save space
  
  static tflite::MicroMutableOpResolver<5> micro_op_resolver;  // NOLINT
  micro_op_resolver.AddBuiltin(tflite::BuiltinOperator_DEPTHWISE_CONV_2D,tflite::ops::micro::Register_DEPTHWISE_CONV_2D() );
  micro_op_resolver.AddBuiltin(tflite::BuiltinOperator_MAX_POOL_2D,tflite::ops::micro::Register_MAX_POOL_2D() );
  micro_op_resolver.AddBuiltin(tflite::BuiltinOperator_CONV_2D,tflite::ops::micro::Register_CONV_2D() );
  micro_op_resolver.AddBuiltin(tflite::BuiltinOperator_FULLY_CONNECTED,tflite::ops::micro::Register_FULLY_CONNECTED() );
  micro_op_resolver.AddBuiltin(tflite::BuiltinOperator_SOFTMAX,tflite::ops::micro::Register_SOFTMAX() );

   * 
   */
   

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  
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
 
}


// Main prediction function
void modelPredict(){   

  // Run inference, and report any error
  //TfLiteStatus invoke_status = interpreter->Invoke();
  // I made the above a global variable
  myZeroIfPredictionOk = interpreter->Invoke();
  
  // if (invoke_status != kTfLiteOk) {
  //    Serial.print("Error with input: " + String(myInput));
  // }


}



/*================= End Smart Area ======================================*/


/*================= Start Maker Area ======================================*/



int myLed = LED_BUILTIN;   // or 7 or 5 or LEDB etc
String myLedState = "Not Set";

void setup() {
   randomSeed(analogRead(A0));
   Serial.begin(115200);      // 9600
   pinMode(myLed, OUTPUT);   
   
   modelSetup(model_tflite);    

}


void loop() {

    // https://www.tensorflow.org/lite/api_docs/cc/class/tflite/impl/interpreter
    // interpreter is a pointer to Tensor data note () then []

    // The following lines show how to to do a basic input set, prediction, output read.


     
 float myInput[1*32*32*1] =  {
 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,2,2,2,2,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,2,2,2,2,2,2,2,2,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,2,7,7,7,7,2,2,2,2,2,2,2,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,7,7,7,7,7,7,7,7,2,2,2,2,2,7,7
,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,7,7,7,7,7,7,7,7,2,2,2,2,2,2,7
,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,7
,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,7
,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,7
,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,7,7,7,7,7,7,7,7,2,2,2,2,2,2,7
,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,7,7,7,7,7,7,7,7,2,2,2,2,2,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,2,7,7,7,7,2,2,2,2,2,2,2,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,2,2,2,2,2,2,2,2,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,2,2,2,2,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,7,7,7,7,7,7,7,7
,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
 };

    interpreter->input(0)->data.f = myInput;

    modelPredict();  // run the prediction


    Serial.println("no-shape: " + String(interpreter->output(0)->data.f[0],6)  );
    Serial.println("circle(s): " + String(interpreter->output(0)->data.f[1],6)  );
    Serial.println("triangle(s):" + String(interpreter->output(0)->data.f[2],6)  );
    Serial.println("rectangle(s): " + String(interpreter->output(0)->data.f[3],6)  );
    Serial.println();

   
    
    Serial.println("Just getting information from the model. Delete once working." );
    Serial.println("constexpr int kTensorArenaSize: " + String(kTensorArenaSize) );
    Serial.println("interpreter->arena_used_bytes(): " + String(interpreter->arena_used_bytes()) );     
    Serial.println("Hidden Layers: " +  String( interpreter->tensors_size() )   );  
    Serial.println("input type: " + String(interpreter->input(0)->type) + ", Dimensions: " + String(interpreter->input(0)->dims->size) );
    Serial.println("output type: " + String(interpreter->output(0)->type) + ", Dimensions: " + String(interpreter->output(0)->dims->size) );
    // type: 0=kTfLiteNoType,  1=kTfLiteFloat32,   2=kTfLiteInt32, 3=kTfLiteUInt8,    4=kTfLiteInt64,   5=kTfLiteString,     6=kTfLiteBool, 
    // type: 7=kTfLiteInt16,   8=kTfLiteComplex64, 9=kTfLiteInt8, 10=kTfLiteFloat16, 11=kTfLiteFloat64, 12=kTfLiteComplex128  

    Serial.println("--------------------------" );
    Serial.println();

    delay(3000); // slows things down

}



