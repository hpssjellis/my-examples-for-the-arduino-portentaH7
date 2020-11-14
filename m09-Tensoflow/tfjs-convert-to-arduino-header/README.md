# Warning: Your favorite Machine Learning model will probably not convert to a format that will work on an Arduino. Also it will probably be too big! Sorry.


## Note: As of Aug 9th, 2020 I am still working on getting this fully working.


Note: Link to the index for these models at https://hpssjellis.github.io/my-examples-for-the-arduino-portentaH7/m09-Tensoflow/tfjs-convert-to-arduino-header/index.html

Note: The above webpage that makes a TensorflowJS very simple model can be viewed directly from this Github by following this link

https://hpssjellis.github.io/my-examples-for-the-arduino-portentaH7/m09-Tensoflow/tfjs-convert-to-arduino-header/easy-tfjs-create-and-save.html

It is not a well made webpage, but it shows how to design a Machine Learning model using Version 2 of Tensorflowjs and how to save the .json and .bin files to your computer.



1. Login to Github, since Gitpod needs you to be logged in.

2. Open my repsitory for Tensorflow to Arduino   https://gitpod.io/#github.com/hpssjellis/gitpod-tensorflowjs-to-arduino

or

A fully loaded Gitpod can be built here https://gitpod.io/#github.com/hpssjellis/Gitpod-auto-tensorflowJS-to-arduino
(If taking this option many of the below commands are automated.) The github for this site is at https://github.com/hpssjellis/Gitpod-auto-tensorflowJS-to-arduino


3. Install Tensorflow nightly build and Tensorflowjs. The arduino-cli is in a new thing I am trying.
``` 
pip install tf-nightly 
pip install tensorflowjs
pip install netron
brew install arduino-cli
```

4. Check if xxd installed ``` xxd --help ```

5. Check if tflite_converter is installed ```tflite_convert --help```

6. Check if tensorflowjs_converter is installed ```tensorflowjs_converter --help```

7. make a new directory ```mkdir myFolder```

8. go to that folder find it's path and copy the path
```
cd myFolder
pwd
```

9. Drag your TensorflowJS model into your new folder say it was called "model.json" then a file is also expected that is called "model.weights.bin"

10. Convert the TensorflowJS model.json to keras 

The format is tensorflowjs_converter --input_format=  --output_format= path-to-input-folder path-to-output-folder

help is at https://github.com/tensorflow/tfjs/tree/master/tfjs-converter

Using ./  for the latest folder makes things much easier and you don't need the full path using the pwd command

```
tensorflowjs_converter --input_format=tfjs_layers_model --output_format=keras_saved_model ./model.json ./

```

10b. If that messes up try the wizard. The problem is the path and pwd is the command that tells you the whole path

```
tensorflowjs_wizard --dryrun

then try 

tensorflowjs_wizard
```

So either of the top commands should save a "saved_model.pb" file in the same directory. The next command seem to know what the file is called.


11. convert the keras model to tensorflowlite 

Not sure why but it doesn't seem to like the name of the saved_model.pb file. Anyway for me the below command worked.

``` 
tflite_convert --keras_model_file ./ --output_file ./model.tflite
```

11. convert that new file to an Arduino style header file 
```
xxd -i model.tflite model.h
```

12. Copy your model.h file into the support files location of your Arduino IDE. You can freely change the name of this .h file.


might want to add at the top of the header .h file

```
#pragma once
```

To view the final tflite file (not the header file). You could also do this command with the .json or .pb models and they will look different. When asked, click open in browser.
```
netron model.tflite

```



I have some saved models but they are probably a version that is not up to date

https://github.com/hpssjellis/beginner-tensorflowjs-examples-in-javascript/tree/master/saved-models


ConverTing keras back to TFJS try this

```
#!/bin/bash

#tensorflowjs_converter --input_format=tfjs_layers_model --output_format=keras_saved_model ./model.json ./



tensorflowjs_converter --output_format=tfjs_layers_model --input_format=keras_saved_model ./ ./

```


