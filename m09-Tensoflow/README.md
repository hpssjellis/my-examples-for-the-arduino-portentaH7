# Machine Learning on Micro-controllers. Specifically the new $100 Dual Core Arduino Portenta H7


1. [a01-tensorflowLite-hello_world.md](a01-tensorflowLite-hello_world.md) shows how to get the default example working by changing LED_BUILTIN to pin 5 a PWM pin


2. [a02-EloquentTinyML-to-M4.ino](a02-EloquentTinyML-to-M4.ino) Note: uses version 0.0.2 and new library is coming out soon. This loads to both the M7 core and the M4 core. The serial plotter only works for the M7 core. On either core the LED connected with a resistor from D5 to ground pulses. Reminder to have it work on the M4 core you need in a blank setup the following code

```
void setup() {
  bootM4();
}

void loop() {
 
}

```

3. [a03-eloquentTineML-from-github.ino](a03-eloquentTineML-from-github.ino) Uses the new EloquentTinyML from the github. Need to manually update the library manually.

.


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


