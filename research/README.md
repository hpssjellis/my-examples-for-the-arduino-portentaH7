Just lots of not working things in this folder.

# Update: Oct 03, 2020 Testing mbed version 1.2.3


Note: Try the new mbed board version 1.2.3 for the Nano33BLE and PortentaH7

Not official yet so will need to put in your preferences comma seperated list 

http://downloads.arduino.cc/packages/package_mbed_staging_index.json

and if you find issues put them here

https://github.com/arduino/ArduinoCore-mbed/issues


I will just do a stream of concsiousness while I fly through my examples.

# Issues

1. While not relevant to just this version: unlike most arduino boards this board install (write at the end of the installation) has something that requires admin access. At school it installs, I can compie but I think uploading to the Portenta does not work, while uploading to the Nano33BLE works.

2. Running the example RPC --> serialpassthrough_RPC     *I just don't understand this at all. I should, but I don't*

3. not working my wifi example [../my05-Web-server.ino](../my05-Web-server.ino)
compiles without error but I am concerned about this statement

```
Alternatives for WiFi.h: [WiFiNINA@1.5.0 WiFi@1.2.7 WiFi@1.0]
ResolveLibrary(WiFi.h)
  -> candidates: [WiFiNINA@1.5.0 WiFi@1.2.7 WiFi@1.0]


```

Since the Library is in the libraries folder
.


.



.






## Working Examples
1. [../my00-dual-clean.ino](../my00-dual-clean.ino),  
1. [../my01-BlinkM7.ino](../my01-BlinkM7.ino) works on either core seperately ,  
1. [../my02a-dual-core.ino](../my02a-dual-core.ino),  
1. [../my02e-easier-dual.ino](../my02e-easier-dual.ino),  
1. [../my02f_easy_m4_rpc_print.ino](../my02f_easy_m4_rpc_print.ino),   


1. [../my03-BLE-LED-control.ino](../my03-BLE-LED-control.ino)  works on either core seperately ,  
1. [../my05-Web-server.ino](../my05-Web-server.ino) Possibly only from the M7 core, I even tried RPC,  
1. [../my06_LED_onboard_setRGB.ino](../my06_LED_onboard_setRGB.ino) works on either core seperately ,   
1. [../my07-analog-test.ino](../my07-analog-test.ino) works on both cores, minor change to get RPC working see [my02f](../my02f_easy_m4_rpc_print.ino),   
1. [../my08-mbed-blink.ino](../my08-mbed-blink.ino)  works on either core seperately , 


1. [../my10-DAC-to-ADC.ino](../my10-DAC-to-ADC.ino) did not test on M4, but DAC must be A0, for reading A6 and D6 worked, but A5 and D5 did not,   
1. [../](../),   
1. [../](../),   
1. [../](../),   
1. [../](../),  


# Machine Learning Files


1. [../m09-Tensoflow/b00_template](../m09-Tensoflow/b00_template) works on M7 only,   
1. [../m09-Tensoflow/b01_makerML_hello_world.ino](../m09-Tensoflow/b01_makerML_hello_world.ino) fixed up some issues not related to this new version 1.2.3 build,   
1. [../m09-Tensoflow/b02_makerML_xor.ino](../m09-Tensoflow/b02_makerML_xor.ino) Runs on both cores, Led flashes, of course no serial for M4,   
1. [../m09-Tensoflow/b05_makerML_medium_image.ino](../m09-Tensoflow/b05_makerML_medium_image.ino) works on M7,   
1. [../](../),  


1. [../](../),   
1. [../](../),   
1. [../](../),   
1. [../](../),   
1. [../m09-Tensoflow/b08-rpc-m4-hello-world-sine.ino](../m09-Tensoflow/b08-rpc-m4-hello-world-sine.ino) This runs the serial plotter using the TFLITE hello world sine wave but from the M4 core using RPC. A bit advanced,  






## Testing Now





---------------------------------------------- Start Machine Learning Programs ---------------------------------
my09-tensorflow-machine-learning-link.md

b04_makerML_template.ino with  tabbed file b04_model_xor.h

b01_makerML_hello_world.ino

b02_makerML_xor.ino

b03_makerML_layers.ino

b05_makerML_medium_image.ino

b05_medium_image_model.h

b06_makerML_one_hot.ino

b06_model_one_hot.h



---------------------------------------------- End Machine Learning Programs ---------------------------------


















## waiting to test later

my02b-dual-core-RPC.ino

my02c-dual-core-RPC-variable.ino

my02d-dual-core-RPC-timer.ino

my04-BLE-LED-multi-control.ino

b07_m4_rpc_m7_print.ino

my12-serial1-crash.ino

my13_uart_m4_m7_print.ino   Not needed as much now with RPC working

my11-servo.ino     Left it at school will have to do it later

my14_8x8_thermal_Array.ino



