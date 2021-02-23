# Machine Learning on Micro-controllers. Specifically the new $100 Dual Core Arduino Portenta H7



This TensorflowLite C++ API should be usefull
https://www.tensorflow.org/lite/api_docs/cc/class/tflite/impl/interpreter?hl=cs

Note: PortentaH7 has only one arduino library, but the Nano 33 BLE has a library connected with the Portenta and a library for the nRF528x boards. The nRF528x boards only work with my code. 


# Try the following files. As of August 22nd, 2020:



#### 0
[b00_template/b04_makerML_template.ino](b00_template/b04_makerML_template.ino) MakerML template. This will be the latest template that seperates the model from the sketch and has been made to work on as many Arduinos as possible. This is a 2 file program, but most of the examples below combine the model with the sketch so that one program can be easily emailed, downloaded, loaded etc. For any of the examples once working it is fairly easy to seperate the model.



#### 1
[b01_makerML_hello_world.ino](b01_makerML_hello_world.ino) This will be the base, single file demo of the sine wave program to test on your board. Note the model.h file is built into this sketch to simplify uploading. It is your choice if you want to move it to a new tab and include that tab into your program. Probably best to test if it works first. The onboard LED should blink and the serial plotter should show a sine wave. [video here](https://www.youtube.com/watch?v=egrsUlEcjNA&list=PL57Dnr1H_egtm0pi-okmG0iE_X5dROaLw&index=25&t=3s) 


#### 2
[b02_makerML_xor.ino](b02_makerML_xor.ino) This is my example xOr logic program. The TensorflowJS 20keras-xOr.html example is [here](https://www.rocksetta.com/tensorflowjs/beginner-keras/20keras-xOr.html) and the conversion of the saved model to a model.h file is [here](https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/tree/master/m09-Tensoflow/tfjs-convert-to-arduino-header). If the inputs are both HIGH or both LOW the output should be near 0. If either input is HIGH and the other LOW the ouput should be close to 1. [video here](https://www.youtube.com/watch?v=pxqgS2x-OJI&list=PL57Dnr1H_egtm0pi-okmG0iE_X5dROaLw&index=26)

#### 3
[b03_makerML_layers.ino](b03-makerML-layers.ino) This program gives information about the model that has been loaded and tests if the model can be loaded. It does not do a prediction so knowing input and output dimensions or types is not needed. The program should actually assist in showing types and dimensions. More work is needed here. Output is on the serial monitor. minimal blinking is done in this program.   [video here](https://www.youtube.com/watch?v=PMHbxf5udmw&list=PL57Dnr1H_egtm0pi-okmG0iE_X5dROaLw&index=27)

#### 4 
Moved to number 0


#### 5
[b05_makerML_medium_image.ino](b05_makerML_medium_image.ino) A medium image entered as an array of numbers representing colors. The TensorflowJS helper page is at  https://www.rocksetta.com/tensorflowjs/beginner-keras/27keras-medium-image.html



#### 6
[b06_makerML_one_hot.ino](b06_makerML_one_hot.ino). This was not very successful. The training set was probably too small. Basically it works to show one hot training but the final trained model is not vey good. I have combined the model in the same file for simplicity, you are welcome to move it to it's own tab.     Tensorflowjs helper page at https://www.rocksetta.com/tensorflowjs/beginner-keras/24keras-one-hot.html


#### 7
[b07_m4_rpc_m7_print.ino](b07_m4_rpc_m7_print.ino) This is exciting, getting the inner M4 core to do the machine learning while the outer M7 core handles the serial print by using RPC calls. This one actually changes the Serial.println to RPC1.println, see next example for an easier technique Next I need to see how big a model I can fit on the M4 core.


#### 8
[b08-rpc-m4-hello-world-sine.ino](b08-rpc-m4-hello-world-sine.ino) Same as [b01_makerML_hello_world.ino](b01_makerML_hello_world.ino) but with code to run RPC on M7 and the Hello world sine wave on M4. Bit advanced.
Note: If you have lots  of Serial.println then put a delay(2); infront of it. also Serial.begin() takes no integer.

Key feactures

```

#ifdef CORE_CM4    // Start M4 programming

#define Serial RPC1  // So the M4 regular serial prints to RPC

void setup(){  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin();   // note no speed 9600 or 115200, since it is now RPC1
}

void loop() {
  delay(2); Serial.println("Your print stuff");
}

#endif;

```

..





..





..








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



#### links

A few other TensorflowLiTe tutorials for a camera connected arduino are here

https://github.com/arduino/ArduinoTensorFlowLiteTutorials


Useful reference  https://www.tensorflow.org/lite/guide/ops_compatibility

TFLite Ops page  https://www.tensorflow.org/mlir/tfl_ops

This might be the latest supported ops   https://github.com/tensorflow/tensorflow/blob/master/tensorflow/lite/micro/all_ops_resolver.cc


converter command line reference   https://www.tensorflow.org/lite/convert/cmdline


