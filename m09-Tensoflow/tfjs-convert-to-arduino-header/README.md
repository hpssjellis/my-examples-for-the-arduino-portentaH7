

1. Login to github, since Gitpod needs this.

2. Open a fresh Gitpod   https://gitpod.io/#

3. ``` pip install tf-nightly ```

4. Check if xxd installed ``` xxd -h ````

5. Check if tflite_convert installed ```tflite_convert --help```

6. make a new directory ```mkdir a-folder-name```

7. go to that folder ```cd a-folder-name```

8. Drag your keras model into your new folder say it was called "model.keras"

9. convert the keras model to tensorflowlite 
``` 
tflite_convert --keras_model_file model.keras --output_file model.tflite 
```

10. convert that new file to an Arduino style header file ```xxd -i model.tflite model.h```

11. Copy your model.h file into the support files location of your Arduino IDE.






