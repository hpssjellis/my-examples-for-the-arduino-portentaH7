This folder contains the latest template for simplifying Machine Learning using an Arduino.

Typically my examples have the model embedded inside the example, but for your own programs like with this template I have sperated out the model from the example
so that it is easier to switch back and forth between program and model.


[b04_makerML_template.ino](b04_makerML_template.ino) Template to start your own program, with a few minor improvements from the above programs. Instead of passing inputs to the modelPrediction, we assign the inputs to the main pointer called interpreter->input(0)->data.f[0] (Looks intimidating but is really useful. The main API uses the interpreter [TF Micro C++ API here](https://www.tensorflow.org/lite/api_docs/cc/class/tflite/impl/interpreter)). This program expects you to have a [b04-model-xor.h](b04-model-xor.h) tab already made with code in the c header format. You can find the simple xOr version called model.h or many more in the folder called [lite-for-arduino](https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/tree/master/m09-Tensoflow/lite-for-arduino). Here is how a model.h tab file should look.


```
/// model.h tab

#pragma once

const unsigned char model_tflite[] = {
  0x1c, 0x00, 0x00, 0x00, 0x54, 0x46, 0x4c, 0x33, 0x00, 0x00, 0x12, 0x00,
  ...
  0xfc, 0xff, 0xff, 0xff, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00
};
unsigned int model_tflite_len = 1608;

```
