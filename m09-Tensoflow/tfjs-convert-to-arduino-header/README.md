

1. Login to Github, since Gitpod needs you to be logged in.

2. Open a fresh Gitpod   https://gitpod.io/#

3. Install Tensorflow nightly build and Tensorflowjs
``` 
pip install tf-nightly 
pip install tensorflowjs
```

4. Check if xxd installed ``` xxd -h ```

5. Check if tflite_converter is installed ```tflite_convert --help```

6. Check if tensorflowjs_converter is installed ```tensorflowjs_converter --help```

7. make a new directory ```mkdir a-folder-name```

8. go to that folder ```cd a-folder-name```

9. Drag your TensorflowJS model into your new folder say it was called "model.json"

10. Convert the TensorflowJS model.json to keras 
```
tensorflowjs_converter --input_format=tfjs_layers_model --output_format=keras_saved_model 
```

10. convert the keras model to tensorflowlite 
``` 
tflite_convert --keras_model_file model.keras --output_file model.tflite 
```

11. convert that new file to an Arduino style header file ```xxd -i model.tflite model.h```

12. Copy your model.h file into the support files location of your Arduino IDE.






