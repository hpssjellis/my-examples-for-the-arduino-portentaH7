
To get the default tensorflowLite Hello_world working: some background information:

The PortentaH7 connects the on-board LED to 3V3 instead of to ground like most Arduinos. This means you need to ground it to set the LED on. This effects LED_BUILTIN, LEBR, LEBG, LEDB

As such the on-board LED can not do a normal PWM on off cycle to allow fading.

The file Hellow_World has an attached .cpp file that defines the LED_BUILTIN pin. Look for the header file arduino_output-handler.cpp then make this change

```
// int led = LED_BUILTIN;  // jerteach changed this
int led = 5;  // an analogWrite PWM pin

```


Unfortunately at the moment connecting that pin does crash the program, however if you choose serial-plotter you should be able to see the sine wave generated.


