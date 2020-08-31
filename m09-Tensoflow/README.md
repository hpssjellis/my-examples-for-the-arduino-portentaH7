# Machine Learning on Micro-controllers. Specifically the new $100 Dual Core Arduino Portenta H7



This TensorflowLite C++ API should be usefull
https://www.tensorflow.org/lite/api_docs/cc/class/tflite/impl/interpreter?hl=cs

Note: PortentaH7 has only one arduino library, but the Nano 33 BLE has a library connected with the Portenta and a library for the nRF528x boards. The nRF528x boards only work with my code. 


# Try the following files. As of August 22nd, 2020:

1. [b01_makerML_hello_world.ino](b01_makerML_hello_world.ino) This will be the base, single file demo of the sine wave program to test on your board. Note the model.h file is built into this sketch to simplify uploading. It is your choice if you want to move it to a new tab and include that tab into your program. Probably best to test if it works first. The onboard LED should blink and the serial plotter should show a sine wave.

2. [b02_makerML_xor.ino](b02_makerML_xor.ino) This is my example xOr logic program. The TensorflowJS 20keras-xOr.html example is [here](https://www.rocksetta.com/tensorflowjs/beginner-keras/20keras-xOr.html) and the conversion of the saved model to a model.h file is [here](https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/tree/master/m09-Tensoflow/tfjs-convert-to-arduino-header). If the inputs are both HIGH or both LOW the output should be near 0. If either input is HIGH and the other LOW the ouput should be close to 1.

3. [b03_makerML_layers.ino](b03-makerML-layers.ino) This program gives information about the model that has been loaded and tests if the model can be loaded. It does not do a prediction so knowing input and output dimensions or types is not needed. The program should actually assist in showing types and dimensions. More work is needed here. Output is on the serial monitor. minimal blinking is done in this program.

4. [b04_makerML_template.ino](b04_makerML_template.ino) Template to start your own program, with a few minor improvements from the above programs. Instead of passing inputs to the modelPrediction, we simply assign the inputs to the main pointer called interpreter->input(0)->data.f[0] (Looks intimidating but is really useful. The main API uses the interpreter [TF Micro C++ API here](https://www.tensorflow.org/lite/api_docs/cc/class/tflite/impl/interpreter)). This program expects you to have a model.h tab already made with code in the c header format format. You can find the simple xOr version called model.h or many more in the folder called [lite-for-arduino](https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/tree/master/m09-Tensoflow/lite-for-arduino)

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



# These have already been deprecated in favour of the B series above

1. [deprecated/a01-tensorflowLite-hello_world.md](deprecated/a01-tensorflowLite-hello_world.md) shows how to get the default example working by changing LED_BUILTIN to pin 5 a PWM pin. Because of Serial print sensitivity this program only loads to the M7 core for me.


2. [deprecated/a02-EloquentTinyML-to-M4.ino](deprecated/a02-EloquentTinyML-to-M4.ino) Note: uses version 0.0.2 and new library is coming out soon. This loads to both the M7 core and the M4 core. The serial plotter only works for the M7 core. On either core the LED connected with a resistor from D5 to ground pulses. Reminder to have it work on the M4 core you need in  to run this  blank setup code on the M7 core so that it only loads the M4 core the following code

```
void setup() {
  bootM4();
}

void loop() {
 
}

```

3. [deprecated/a03-eloquentTinyML-from-github.ino](deprecated/a03-eloquentTineML-from-github.ino) Uses the new EloquentTinyML from the github. Need to manually update the library.


Note: The above EloquentTinyML library is great, except I never like using libraries that are based on Google LIbraries, that extra layer of installed libraries means certain pain when Google updates there library. So from now on I will try to use only the arduino_TensorflowLite libary.


4. [deprecated/a04-digital.ino](deprecated/a04.digital.ino) *DRAFT* present issue as it stilluses a library. Also only M7 core as it uses Serial.print. Has 8 digital inputs of on or off become 4 deciaml outputs from 0-1 1 being fully on and 0 fully off. Uses the model in the lite-for-arduino folder called digital_model.h

5. [deprecated/a05-myNetron.ino](deprecated/a05-myNetron.ino). Note: Only for M7 core as it uses Serial.print. The netron program shows model data for other types of Tensorflow models but not c header files. (A simple python program can convert a c header file to a tflite file). So without Python load this program on your Portenta and load a model frm the lite-for-arduino file and see information about the model. note: models array must be called  "unsigned char model_tflite[] = {"

6/ [deprecated/a06_rocksetta_hello_world.ino](deprecated/a06_rocksetta_hello_world.ino) This file is starting to be how I would like the ML programs to be. Does not call an extra libary that has to be maintained only uses the Arduino_tensorflowlite library but is reasonably easy.




.


Note: The [tflite-models](tflite-models) folder has several models that have not yet been tried on the Portenta. These may get deleted

3. [lite-for-arduino](lite-for-arduino) This folder actually has the converted to header file TensorflowLite pre-compiled models. Presently untested so proceed with caution.




# My Opinion that may change soon.

I have made lots of Machine Learning models using [TensorflowJS](https://www.tensorflow.org/js) my examples [here](http://rocksetta.com/tensorflowjs) and my personal opinion is that Machine Learning is not yet ready for microcontrollers. 
in this directory I will show whatever I can get working on the Portenta, however, my solution for machine learning on microcontrollers is to use a powerful cell phone to do the Machine Learning and to connect 
that cell phone to the microcontroller using a web socket. My time lag is about 10 us based on the wifi/internet connection speed. I am in the process of converting this concept to arduino boards.


My toy car web socket TensorflowJS solution of Machine Learning using microcontrollers youtube video is at

https://www.youtube.com/watch?v=61jYk4a8wkE

Please remember to subscribe as that is important to creators.


I have tested the arduino_tensorflowLT library using the nano 33 BLE sense. Presently Aug 2nd, 2020 I have got the hello_world program working. Using the serial plotter you get a nice sine wave.

I tried the magic_wand, very cool program that detects a W and O and an L using the serial monitor but it has some edits you need to do explained here

https://create.arduino.cc/projecthub/user1382012/magic-wand-29fa3b

since I don't have an accelerometer connected to the Portenta, I am not really interested in this yet. Prsently I will just test the Hello_world. A bit of a concern is that the Helo_world works fine on the Nano 33 BLE sense using the regular Nano board manager, but I am having some issues using the mBED version for the Nano 33 BLE. The port finding and labelling is not working. 


NOPE: HELLO_WORLD DOES NOT COMPILE ON THE PORTENTA, SAME KIND OF ISSUE AS THE NANO 33 ble USING THE MBED BOARD. CAN'T FIND THE CORRECT PORT AFTER UPLOAD.

Update about August 4th, 2020

I have got the Hello_World program working on the Portenta, see above files, but I am leaning towards the eleoquentTinyML library since it seems very condensed and easier to understand.



A few other TensorflowLiTe tutorials for a camera connected arduino are here

https://github.com/arduino/ArduinoTensorFlowLiteTutorials


Useful reference  https://www.tensorflow.org/lite/guide/ops_compatibility

TFLite Ops page  https://www.tensorflow.org/mlir/tfl_ops

This might be the latest supported ops   https://github.com/tensorflow/tensorflow/blob/master/tensorflow/lite/micro/all_ops_resolver.cc


converter command line reference   https://www.tensorflow.org/lite/convert/cmdline


