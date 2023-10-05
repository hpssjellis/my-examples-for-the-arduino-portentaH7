# Issue the tFlite github by Google does not transfer to all Arduino's easily

Google tFlite github is at  https://github.com/tensorflow/tflite-micro



The Arduino version is at  https://github.com/tensorflow/tflite-micro-arduino-examples   which works great for the Nano33BleSense REV1 but not any other Arduino








Using the fork at   https://github.com/josemqz/tflite-micro-arduino-portenta-h7  person detection now works. Thanks Jose

<img  width="100%" src="https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/assets/5605614/1d3ae9e2-28b3-4afc-8f20-a693915f4d2c">




.



.




.




.






### not as good attempts.

My attempt is here   https://github.com/hpssjellis/TensorFlowLiteRocksetta2023

and my very old but still working version is here   https://github.com/hpssjellis/RocksettaTinyML



## Oct 4th, 2023


I took the original tFlite for Arduino examples  https://github.com/tensorflow/tflite-micro-arduino-examples and deleted the peripherals folder
Changed the tensorflowlite.h file to 

```
/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef TENSORFLOW_LITE_MICRO_TOOLS_MAKE_TEMPLATES_TENSORFLOWLITE_H_
#define TENSORFLOW_LITE_MICRO_TOOLS_MAKE_TEMPLATES_TENSORFLOWLITE_H_

// This header is deliberately empty, and is only present because including it
// in a .ino sketch forces the Arduino toolchain to build the rest of the
// library.

//#include "peripherals/peripherals.h"


#include <Arduino.h>  // mainly for Platform.io
#include <Wire.h>

// Temporary fix, see buganizer #268498682, arduino-examples issue #169
#undef abs



#endif  // TENSORFLOW_LITE_MICRO_TOOLS_MAKE_TEMPLATES_TENSORFLOWLITE_H_


```



  and changed   ......Arduino\libraries\tflite-micro-arduino-examples-main\src\tensorflow\lite\micro\micro_time.cpp  getting rid of the two peripherals calls


  ```


/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// Reference implementation of timer functions.  Platforms are not required to
// implement these timer methods, but they are required to enable profiling.

// On platforms that have a POSIX stack or C library, it can be written using
// methods from <sys/time.h> or clock() from <time.h>.

// To add an equivalent function for your own platform, create your own
// implementation file, and place it in a subfolder with named after the OS
// you're targeting. For example, see the Cortex M bare metal version in
// tensorflow/lite/micro/bluepill/micro_time.cc or the mbed one on
// tensorflow/lite/micro/mbed/micro_time.cc.

#include "tensorflow/lite/micro/micro_time.h"

//#include "peripherals/utility.h"

#if defined(TF_LITE_USE_CTIME)
#include <ctime>
#endif

namespace tflite {

#if !defined(TF_LITE_USE_CTIME)

// Reference implementation of the ticks_per_second() function that's required
// for a platform to support Tensorflow Lite for Microcontrollers profiling.
// This returns 0 by default because timing is an optional feature that builds
// without errors on platforms that do not need it.
uint32_t ticks_per_second() { return 1000000; }

// Reference implementation of the GetCurrentTimeTicks() function that's
// required for a platform to support Tensorflow Lite for Microcontrollers
// profiling. This returns 0 by default because timing is an optional feature
// that builds without errors on platforms that do not need it.
uint32_t GetCurrentTimeTicks() { }  //return peripherals::MicrosecondsCounter(); }

#else  // defined(TF_LITE_USE_CTIME)

// For platforms that support ctime, we implment the micro_time interface in
// this central location.
uint32_t ticks_per_second() { return CLOCKS_PER_SEC; }

uint32_t GetCurrentTimeTicks() { return clock(); }
#endif

}  // namespace tflite



```


And the nano33BleSense seems to run at least hello_World.

Super strange is when I tried the Portenta. The compiler found my renamed peripherals folder and tried to compile some hal code from it. I have now removed the old pheripherals folder from the librry.

