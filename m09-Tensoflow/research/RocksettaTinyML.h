/*
* RocksettaTinyML by Jeremy Ellis,keyfreemusic@gmail.com
*
*
* transition from EloquentTinyML to full TensorflowLite imprementation without library
*
*
* Based on the Arduino Library
* EloquentTinyML by Simone Salerno,eloquentarduino@gmail.com
* https://github.com/eloquentarduino/EloquentTinyML
* 
* Passed from the main program
* #define NUMBER_OF_INPUTS 8
* 
* #define NUMBER_OF_OUTPUTS 4
* 
* #define TENSOR_ARENA_SIZE 20*1024  // default 2*1024 up to 432*1024 on PortentaH7 M7 core
*/




#pragma once

#include <Arduino.h>
#include <math.h>
#include "tensorflow/lite/version.h"
#include "tensorflow/lite/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"


