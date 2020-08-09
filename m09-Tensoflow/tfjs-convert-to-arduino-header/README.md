# Warning: Your favorite Machine Learning model will probably not convert to a format that will work on an Arduino. Also it will probably be too big! Sorry.


## Note: As of Aug 9th, 2020 I am still working on getting this fully working.

1. Login to Github, since Gitpod needs you to be logged in.

2. Open my repsoitory for Tensorflow to Arduino   https://gitpod.io/#github.com/hpssjellis/gitpod-tensorflowjs-to-arduino

3. Install Tensorflow nightly build and Tensorflowjs
``` 
pip install tf-nightly 
pip install tensorflowjs
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

9. Drag your TensorflowJS model into your new folder say it was called "model.json"

10. Convert the TensorflowJS model.json to keras 

The format is tensorflowjs_converter --input_format=  --output_format= path-to-input-folder path-to-output-folder

help is at https://github.com/tensorflow/tfjs/tree/master/tfjs-converter

```
tensorflowjs_converter \
--input_format=tfjs_layers_model \
--output_format=keras_saved_model \
/workspace/gitpod-tensorflowjs-to-arduino/myFolder \
/workspace/gitpod-tensorflowjs-to-arduino/myFolder 

```

10b. If that messes up try the wizard

```
tensorflowjs_wizard --dryrun

then try 

tensorflowjs_wizard
```

10. convert the keras model to tensorflowlite 
``` 
tflite_convert --keras_model_file model.keras --output_file model.tflite 
```

11. convert that new file to an Arduino style header file ```xxd -i model.tflite model.h```

12. Copy your model.h file into the support files location of your Arduino IDE.






