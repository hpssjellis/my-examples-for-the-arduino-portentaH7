

So I can compile the arduino TensorflowLite library (takes a long time)

be logged into github
view https://github.com/tensorflow


then load the gitpod  https://gitpod.io/#github.com/tensorflow

```
cd ./tensorflow/tensorflow/lite/micro/tools/ci_build
./test_arduino.sh
 
```

and go have a long coffee

look in the folder for the file tensorflow_lite.zip

```
tensorflow/tensorflow/lite/micro/tools/make/gen/arduino_x86_64/prj/

```

download it and unzip it in your documents/arduino/libraries folder 

Then restart your arduino IDE. If you already have it installed I changed it's name in the library.properties file and the folder name and it seemed to load in the IDE and the examples worked. 

I wonder where the new versions are???
