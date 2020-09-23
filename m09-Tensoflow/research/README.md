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
