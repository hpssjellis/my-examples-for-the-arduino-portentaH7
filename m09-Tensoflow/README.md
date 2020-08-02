# Machine Learning on Microcontrolers

I have made 100's of Machine Learning models using [TensorflowJS](https://www.tensorflow.org/js) my examples [here](http://rocksetta.com/tensorflowjs) and my personal opinion is that they are not yet ready for microcontrols. 
in this directory I will show whatever I can get working on the Portenta, however, my solution is to use a powerful cell phone to do the Machine Learning and to connect 
that cell phone to the microcontroller using a web socket. I am in the process of converting this concept to arduino boards.


My toy car web socket TensorflowJS solution of Machine Learning using microcontrollers youtube video is at

https://www.youtube.com/watch?v=61jYk4a8wkE

Please remember to subscribe as that is important to creators.


I have tested the arduino_tensorflowLT library using the nano 33 BLE sense. Presently Aug 2nd, 2020 I have got the hello_world program working. Using the serial plotter you get a nice sine wave.

I tried the magic_wand, very cool program that detects a W and O and an L using the serial monitor but it has some edits you need to do explained here

https://create.arduino.cc/projecthub/user1382012/magic-wand-29fa3b

since I don't have an accelerometer connected to the Portenta, I am not really interested in this yet. Presntly I will just test the Heloow_world. A bit of a concern is that the Heloo_world works fine on the Nano 33 BLE sense using the regular Nano board manager, but I am having some issues using the mBED version for the Nano 33 BLE. The port finding and labelling is not working. 


NOPE: HEOLLO_WORLD DOES NOT COMPILE ON THE PORTENTA, SAME KIND OF ISSUE AS THE NANO 33 ble USING THE MBED BOARD. CAN'T FIND THE CORRECT PORT AFTER UPLOAD.



A few other TensorflowLT tutorials for a camera connected arduino are here

https://github.com/arduino/ArduinoTensorFlowLiteTutorials








