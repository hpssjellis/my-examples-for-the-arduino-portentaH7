Files here might be working but may have some issues before they are ready for the general public


Note: These work for esp32 boards

```

#include <TensorFlowLite_ESP32.h>

   #if  defined (ESP32) 
   Serial.println("Hello ESP32");

   #endif
   
      #if  defined (ARDUINO_NodeMCU_32S) 
   Serial.println("Hello ARDUINO_NodeMCU_32S");

   #endif

```



for platformIO

drag arduino installed libraries to the libeary folder "copy Folder"

then change the patformio.ini file src_dir to the location of examples. bypasses the default src-->main.cpp. 
for my esp32 have to touch the mode button when it tres to upload.

```
[platformio]
src_dir = lib\\TensorFlowLite_ESP32\\examples\\person_detection

[env:nodemcu-32s]
platform = espressif32
board = nodemcu-32s
framework = arduino
```

