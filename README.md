## my-examples-for-the-arduino-portentaH7
My examples for the new Arduino Pro board the Portenta H7


## Main Site
Main Teaching Site that will use this information [https://github.com/hpssjellis/arduino-high-school-robotics-course](https://github.com/hpssjellis/arduino-high-school-robotics-course)



## Oct 4th, 2020

I just tested ~19 of these programs and put my results at [research/README.md](research/README.md) I fixed a few mistakes and got DAC working. The reason I tested everything is there is a new version of the mbed board software for the PortentaH7 coming out soon.



# The growing playlist of all my Portenta Videos is now live at

[https://www.youtube.com/playlist?list=PL57Dnr1H_egtm0pi-okmG0iE_X5dROaLw](https://www.youtube.com/playlist?list=PL57Dnr1H_egtm0pi-okmG0iE_X5dROaLw)

Click image below to view the same playlist link as above

[<img src="image-video/raft.png" alt="Rocksetta Arduino Fast Tutorials" width = 300px />](https://www.youtube.com/playlist?list=PL57Dnr1H_egtm0pi-okmG0iE_X5dROaLw)


#### Please subscribe to my youtube channel and send the link to other Robotics enthusiasts as I am just below the 1000 needed subscribers to make any income.

Note: The Arduino Pro site has much more professional Pro tutroials at https://www.arduino.cc/pro/tutorials/portenta-h7 that lead you through every step of similar examples, however these videos are for people just to quickly get up and running.


As of July 24th, 2020 this site is just to get the PortentaH7 working how I like it to work. 

My Arduino Robotics teaching will eventually contain student tested Arduino teaching programs with instructional videos. 

https://github.com/hpssjellis/arduino-high-school-robotics-course  




#### Use at your own risk
#### By Jeremy Ellis
#### Twitter https://twitter.com/rocksetta
#### Website https://www.rocksetta.com/
#### [My Portenta Youtube Playlist](https://www.youtube.com/playlist?list=PL57Dnr1H_egtm0pi-okmG0iE_X5dROaLw)








So Far what is working:

#### 0
[my00-dual-clean.ino](my00-dual-clean.ino) As the M7 core loads itself and using bootM4() the M4 core, what if one of them has a problem and you are working on the other one? Sometimes you need to clean both cores before you can upload new code to both cores. Or at least clean the other code before uploading new code. [Clean video at here](https://www.youtube.com/watch?v=EDc_UKpkyfc&list=PL57Dnr1H_egtm0pi-okmG0iE_X5dROaLw&index=3&t=0s)


#### 1
[my01-BlinkM7.ino](my01-BlinkM7.ino) Get the Portenta H7 Blinking with it's weird on board LED's connected to 3V3 so you have to send LOW to turn it on. Great for the board health (can't send 5V to it and break the LED), but crappy for anyone use to HIGH turns LED's on. 

#### 1b
[my01b-blink-serial.ino](my01b-blink-serial.ino). Always good to test both blink and serial. This code sets M7 to boot M4 as well. If issues make sure M4 is clean. [Blink Serial video here](https://www.youtube.com/watch?v=ZH355owXveo&list=PL57Dnr1H_egtm0pi-okmG0iE_X5dROaLw&index=4&t=0s)



#### 2
[my02a-dual-core.ino](my02a-dual-core.ino) Proud of this. I have taken the Pro Tutorial and made it more smooth. This code can be flashed to either core and randomly sets blue and green onboard LED flashing. This is the way to write dual core code.  Pro Tutorial at  https://www.arduino.cc/pro/hardware/product/portenta-h7 then go to the tutorials


### note: the my02 group after the first one is farily advanced, best to skip to my03
 The changes were that for RPC you need to add -fexceptions to the cflags.txt and cxxflags.txt files in the board location  AppData\Local\Arduino15\packages\arduino-beta\hardware\mbed\1.2.2\variants\PORTENTA_H7_M4 I have put in a request to have it changed [here](https://github.com/arduino/ArduinoCore-mbed/issues/55) to the ArduinoCore-mbed

#### 2b
[my02b-dual-core-RPC.ino](my02b-dual-core-RPC.ino) An advanced program.  The M4 core cannot print to Serial, so this advanced example uses RPC (Remote Procedure Call) to send a print command from the M4 core to the M7 core to print to serial. 

#### 2c
[my02c-dual-core-RPC-variable.ino](my02c-dual-core-RPC-variable.ino) Another advanced file that I would leave until you are more comfortable with the Portenta

#### 2d
[my02d-dual-core-RPC-timer.ino](my02d-dual-core-RPC-timer.ino) Another advanced file that I would leave until you are more comfortable with the Portenta this one uses and interval instead of the delay.


#### 2e
[my02e-easier-dual.ino](my02e-easier-dual.ino) Easier Dual RPC programming that fully seperates the M4 and M7 core programs but still in one file. A very small delay added to the M7 core while the M4 core has a long delay to slow things donw enough to see what is happening. Means more code to write, but much easier to understand and to build from.

#### 2f
[my02f_easy_m4_rpc_print.ino](my02f_easy_m4_rpc_print.ino) This is my new favorite RPC. It redirects regular Serial.println from the M4 core to the M7 as regular Serial.println, by using ``` #define Serial RPC1  ``` but only for the M4 core.

#### 2g
[my02g-analogRead-m4-rpc.ino](my02g-analogRead-m4-rpc.ino). Showing how to do analogRead of A0 to A6 but on the M4 core. Also found that delayMicrosecond(1234); was needed between each Serial.println(); statement for RPC to fully work. 


### Note: End advanced RPC stuff that requires a few changes to your library
 The changes were add -fexceptions to the cflags.txt and cxxflags.txt files in the board location  AppData\Local\Arduino15\packages\arduino-beta\hardware\mbed\1.2.2\variants\PORTENTA_H7_M4

#### 3
[my03-BLE-LED-control.ino](my03-BLE-LED-control.ino) All this does is activate the onboard LED using BLE. I use the nrf-connect androd app, but any BlueTooth connectivity app should be able to turn on and off your LED. [BLE video here](https://www.youtube.com/watch?v=K96uz8Dp20w&list=PL57Dnr1H_egtm0pi-okmG0iE_X5dROaLw&index=11), This Arduino Tutorial is based on my BLE program (Look for my name at the bottom of the page ) [Pro BLE Tutorial here](https://www.arduino.cc/pro/tutorials/portenta-h7/por-ard-ble)

#### 4
[my04-BLE-LED-multi-control.ino](my04-BLE-LED-multi-control.ino) Proud of this baby. It scans for BLE LED activated boards that must have "LED" in their bluetooth set local name and then one after another flashes the on board LED. The boards even work when fully disconnected from a computer (use a usb stick to power the boards). Unfortunately to test this out you need more than one board. I have a few Nano 33 IOT boards that have  my03-BLE-LED-control.ino running powered by a wall charger. [BLE multi video here](https://www.youtube.com/watch?v=_06vKjbj5gI&list=PL57Dnr1H_egtm0pi-okmG0iE_X5dROaLw&index=12)

#### 5
[my05-Web-server.ino](my05-Web-server.ino) Cool webserver with buttons to control the on-board LED. Needs to show the serial monitor to discover the local IP address. You must be on the same local network to view the page. More complex to make as a full www webpage. Strangely needs to be connected to a computers USB port, that should not be an issue.


#### 6
[my06_LED_onboard_setRGB.ino](my06_LED_onboard_setRGB.ino) a fairly advanced program that allows complete control of the on-board LED's.

#### 7
[my07-analog-test.ino](my07-analog-test.ino) Just a program that quickly prints out all the analogRead pins A0-A6

#### 8
[my08-mbed-blink.ino](my08-mbed-blink.ino)   starting to use the mbed compiler, fairly different from arduino code.

#### 9
[/m09-Tensoflow](m09-Tensoflow)  Read my opinions in that folder. I did get the TensorflowLite Hello_world working on the serial-plotter. Now I am able to convert my TensorflowJS Vanilla Javascript Machine Learning models to a C header file format for the Arduino. Check out this page. https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/tree/master/m09-Tensoflow/tfjs-convert-to-arduino-header 


<img src="image-video/crashTest04.png" alt="Crash test SeeeduinoXIAO and PortentaH7 both cores"  />




#### 10
[my10-DAC-to-ADC.ino](my10-DAC-to-ADC.ino) Testing the DAC pin at A6 as it sends from 0.0 to 1.0 to both A0 for analogRead (from 0 to 1023) and D6 for digitalRead (from 0 to 1).  [DAC To ADC video here](https://www.youtube.com/watch?v=9OrItMqI2VQ&list=PL57Dnr1H_egtm0pi-okmG0iE_X5dROaLw&index=19&t=0s)


#### 11
[my11-servo.ino](my11-servo.ino) Basic servo functionality. Will need Servo.h greater than 0.0.2 or make the changes stated [here](https://forum.arduino.cc/index.php?topic=691668.msg4700186#msg4700186) on the Arduino forum.

#### 12
[my12-serial1-crash.ino](my12-serial1-crash.ino). The portenta sends crash information through the Serial1 RX and TX pins. This program allows you to load a serial1 monitoring programon another 3.3V arduino (Note: must use protective resistors if using an older 5V arduino). The easier approach is to connect a TTL USB cable to Gnd, RX and TX but I don't have one of those cables.


#### 13
[my13_uart_m4_m7_print.ino](my13_uart_m4_m7_print.ino) Similar to the crash report that uses another arduino to catch the serial1 UART TX and TR and GND print output. This program allows UART print from either the M7 or M4 cores. Great for debugging the M4 core. Uses ``` _UART1_.println("Hi");``` which on the M7 is the same as Serial1.println("Hi"); and on the M4 core is Serial.println("hi"); The program also tests for Portenta or not and programs for each of 2 boards 3 cores.


#### 14
[my14_8x8_thermal_Array.ino](my14_8x8_thermal_Array.ino) Finally starting to make cool things. This $52 USD Thermal 8x8 array can sense who has a temperature. The program flashes the onboard LED when it senses a temperaturre change, but if the highest temperature is above a set threshold (I used 39 degrees celcius), it flashes continuously for about 20 seconds. The serial monitor is not needed but gives average array temperature and highest recorded temperature. Prints about 3 times until it settles down again. Uses the AMG8831 sensor at [AMG8833 IR 88 Thermal Imager Array Temperature Sensor Module 8x8 Infrared Camera Sensor](https://www.amazon.com/s?k=AMG8833+IR+88+Thermal+Imager+Array+Temperature+Sensor+Module+8x8+Infrared+Camera+Sensor&ref=nb_sb_noss) that is a generic search I used [this one](https://www.amazon.com/AMG8833-Thermal-Imager-Temperature-Infrared/dp/B07YZRGVB9/ref=sr_1_1?dchild=1&keywords=AMG8833+IR+8+*+8+Thermal+Imager+Array+Temperature+Sensor+Module+8x8+Infrared+Camera+Sensor&qid=1600007347&sr=8-1)

![AMG8833 IR 88 Thermal Imager Array Temperature Sensor Module 8x8 Infrared Camera Sensor](image-video/portenta-thermal-8x8-03.png)


#### 15
[my15-TRACE32.ino](my15-TRACE32.ino)  Presntly testing the TRACE32 debugger by [Lauterbach.com](https://www.lauterbach.com/) I will make a video soon. The other my15 sketches werre early attempts. 







#### pinout

## Portenta H7 Pinout documentation:
Lots more info in this pdf file: https://content.arduino.cc/assets/Pinout-PortentaH7_latest.pdf

![image-video/bothPinout.png](image-video/bothPinout.png)




.




#### other

## Other sites with good examples about Portenta

https://github.com/trimchess/portenta_basics

https://www.arduino.cc/pro/tutorials/portenta-h7


#### links

The battery connector  https://www.digikey.com/product-detail/en/jst-sales-america-inc/BM03B-ACHSS-GAN-TF-LF-SN/455-2203-1-ND/1647795
