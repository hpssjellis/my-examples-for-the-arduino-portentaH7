My best ideas so far

[a01](ao1.ino)  is trying to edit your code, but always has some compiler issues.

Compile issue at [here](https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/blob/42e591f29604f498ca8ee786af78ac8596856654/research/camera-webserver-save/larry/a01.ino#L113)

```
  rc = png.open("fs/testimg.png", myOpen, myClose, myRead, myWrite, mySeek);

```


[a02](a02.ino) is what I am having most success with as I build from what works.

Latest issue is finding the storage spot for the combined PNG

This line is not working to dump the entire PNG to disk [here](https://github.com/hpssjellis/my-examples-for-the-arduino-portentaH7/blob/42e591f29604f498ca8ee786af78ac8596856654/research/camera-webserver-save/larry/a02.ino#L71)

```
            fprintf(myPngFile, (const char *)ucOut, sizeof(ucOut) );    
```



