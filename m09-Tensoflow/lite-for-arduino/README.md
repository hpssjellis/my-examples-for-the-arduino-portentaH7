The folowing header files are TensorflowLite models converted ready for loading on an Arduino

Folders are for when there are 2 or more files


For simplicity I have combined the .h and .c files into one .h file when I find them. Basically ignoring the original  .h file but adding the line


#pragma once



# Presently no idea if any of these other than the sine_model.h work. Use at your own risk!


Note: It is fairly easy to convert a .tflite file to an arduino .h header file.


load the tensorflow site using gitpod (needs a github login)

https://gitpod.io/#github.com/tensorflow/tensorflow

Check if xxd has been pre-installed (It should)

```xxd -h```

If you see a help file?

make and enter a directory

``` 
mkdir myArduino 
cd myArduino

```

upload your .tflit file to the directory. I drag and drop

Convert your file to a .h header file
Note: expecting your file to be called name_model.tflite Change the following code if the name is different



``` xxd -i name_model.tflite name_model.h ```


to the top of the file add

``` #pragma once ```








