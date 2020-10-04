Just lots of not working things in this folder.

# Oct 03, 2020 


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
[../my00-dual-clean.ino](../my00-dual-clean.ino), [../my01-BlinkM7.ino](../my01-BlinkM7.ino) works on either core seperately , [../my02a-dual-core.ino](../my02a-dual-core.ino),   [../my02e-easier-dual.ino](../my02e-easier-dual.ino), [../my03-BLE-LED-control.ino](../my03-BLE-LED-control.ino)  works on either core seperately , [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../), [../](../),





## Testing Now

my05-Web-server.ino

my06_LED_onboard_setRGB.ino

my07-analog-test.ino


my08-mbed-blink.ino


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

b07_m4_rpc_m7_print.ino


my10-DAC-to-ADC.ino


my11-servo.ino


my12-serial1-crash.ino


my13_uart_m4_m7_print.ino


my14_8x8_thermal_Array.ino




## waiting to test later

my02b-dual-core-RPC.ino

my02c-dual-core-RPC-variable.ino

my02d-dual-core-RPC-timer.ino

my04-BLE-LED-multi-control.ino



