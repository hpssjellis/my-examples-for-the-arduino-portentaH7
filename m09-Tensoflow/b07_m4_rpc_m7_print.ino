/*
 * my02-Dual-Core for the Portenta H7
 *
 * This code can be loaded on either core.
 * The M7 core will initialize the M4 core
 * The M7 will flash Blue randomly (under 6 seconds)
 * The M7 core will serial print its own messges
 * The M7 core will serial print messages it receives from the M4 core
 * The M7 core will continuously print the "myIntGlobal" variable
 * 
 * The M4 will flash Green randomly (under 6 seconds)
 * The M4 will randomly set the M7 variable "myIntGlobal"
 *
 * Note: The M4 core will not compile unless -fexceptions is added 
 * to the bottom of the files: 
 * cflags.txt
 * cxxflags.txt 
 * at
 * C:\Users\<USER>\AppData\Local\Arduino15\packages\arduino-beta\hardware\mbed\1.2.2\variants\PORTENTA_H7_M4
 *
 * Note: AppData is hidden so find it directly
 * 
 * updated August 2nd, 2020
 * by Jeremy Ellis
 * Twitter @rocksetta
 * Website https://www.rocksetta.com
 *
 *I have re-written this to make larger programs easier
 *by seperating the M7 and M4 code completely.
 *
*/




///////////////////////////////// ALL M7 PROGRAMMING //////////////////////////////////////////////
#ifdef CORE_CM7

  #include "RPC_internal.h"  // comes with the mbed board installation
  int myLED; 

  // Set an M7 core global variable
  int myIntGlobal = 1234;

  int setVar(int a) {
    myIntGlobal = (int)a;
    return a;
  }

void setup() {
   randomSeed(analogRead(A0));
   RPC1.begin();
    
   bootM4();  
   myLED = LEDB; // on-board blue LED
   Serial.begin(115200);

   RPC1.bind("setVar", setVar); // do these have to be the same? 
   
   pinMode(myLED, OUTPUT);
   digitalWrite(myLED, HIGH); // turn the Portenta on-board LED off 
}

void loop() {
   
  // Serial.println("---------------------------------");
  // Serial.println("From M7 showing global variable: "+ String(myIntGlobal));
   while (RPC1.available()) {
     digitalWrite(myLED, LOW); // turn the Portenta on-board LED on 
     Serial.write(RPC1.read()); // check if the M4 has sent an RPC println
   }  
   delay(50); // minor slow down just for fun
   digitalWrite(myLED, HIGH); // turn the Portenta on-board LED off 
}


#endif   // end al M7 core programming






///////////////////////////////// ALL M4 PROGRAMMING //////////////////////////////////////////////
#ifdef CORE_CM4 



#include "b04_model_xor.h"  // name of the tabbed file containing your machine learning model


#include "Arduino.h"
#include <TensorFlowLite.h>

// A few important global variables

// Create an area of memory to use for input, output, and intermediate arrays.
constexpr int kTensorArenaSize = 15 * 1024;  // Original was 2*1024; Large Board likes 20*1024
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















  #include "RPC_internal.h"  // comes with the mbed board installation
  int myLED; 





String myLedState = "Not Set";


void setup() {
   randomSeed(analogRead(A0));
   RPC1.begin();
   myLED = LEDG; // on-board greeen LED
   
   pinMode(myLED, OUTPUT);
  
   modelSetup(model_tflite);    
}


void loop() {
  // digitalWrite(myLED, LOW); // turn the Portenta on-board LED on 
  // delay(200); // wait for a second
  // digitalWrite(myLED, HIGH); // turn the Portenta on-board LED off 


    


  // https://www.tensorflow.org/lite/api_docs/cc/class/tflite/impl/interpreter
    // interpreter is a pointer to Tensor data note () then []

    // The following lines show how to to do a basic input set, prediction, output read.

     
     
    float myA =  rand() % 2;  // random number either 0 or 1 
    float myB =  rand() % 2;  

    float myInput[2] = {myA, myB };              // set an array variable
    interpreter->input(0)->data.f = myInput;     // point the tensor to the array.
    
    //Important to print the inputs before the predic
     RPC1.print("Input A: " +  String(interpreter->input(0)->data.f[0]) + ", Input B: " +  String(interpreter->input(0)->data.f[1]));

    modelPredict();  // run the prediction
    
    if (interpreter->output(0)->data.f[0] >= 0.5){  // interpret the output array
       digitalWrite(myLED, LOW); // grounds the LED turns it on only on portenta and nano 33 BLE
       myLedState = "On";
    } else {  
       digitalWrite(myLED, HIGH); //  turns it off only on portenta and nano 33 BLE
       myLedState = "Off";
    }

     RPC1.print("\r\nPredicted: " + String(interpreter->output(0)->data.f[0],6) +", so the LED is: " + String(myLedState) );



   int myPredict = round(interpreter->output(0)->data.f[0]*100);
    
     auto res = RPC1.call("setVar", myPredict).as<int>();
     RPC1.print("\r\nFrom M4 core setting M7 variable to: " + String(res)+"%");
     RPC1.println("\r\n ---------------------- \r\n");

    // RPC1.println("Just getting information from the model. Delete once working." );
    // RPC1.print("constexpr int kTensorArenaSize: " + String(kTensorArenaSize) );
    // RPC1.print("interpreter->arena_used_bytes(): " + String(interpreter->arena_used_bytes()) );     
    // RPC1.print("Hidden Layers: " +  String( interpreter->tensors_size() )   );  
    // RPC1.print("input type: " + String(interpreter->input(0)->type) + ", Dimensions: " + String(interpreter->input(0)->dims->size) );
    // RPC1.print("output type: " + String(interpreter->output(0)->type) + ", Dimensions: " + String(interpreter->output(0)->dims->size) );
    // type: 0=kTfLiteNoType,  1=kTfLiteFloat32,   2=kTfLiteInt32, 3=kTfLiteUInt8,    4=kTfLiteInt64,   5=kTfLiteString,     6=kTfLiteBool, 
    // type: 7=kTfLiteInt16,   8=kTfLiteComplex64, 9=kTfLiteInt8, 10=kTfLiteFloat16, 11=kTfLiteFloat64, 12=kTfLiteComplex128  

    // RPC1.println("--------------------------" );
   //  RPC1.println();





   delay(6000); // slow the M4 core down only
                  
}

#endif  // end all M4 core programming

