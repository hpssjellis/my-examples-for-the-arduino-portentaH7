
Note the highest number  cam## is the latest attpemt, but not necessarily the best attempt.


saving from the portenta or Nicla Vision camera to a webpage text file. Potentially then send the image to the cloud.

possibly keep data in BM format

http://jsfiddle.net/nj82y73d/



OR other ideas

https://joshuatz.com/posts/2020/using-binary-data-with-front-end-javascript-and-the-web/



Lots of good info


https://codepen.io/abdhass/pen/jdRNdj


```
data:image/png;base64,R0lGODdhAQABAPAAAP8AAAAAACwAAAAAAQABAAACAkQBADs=
```

```
<img src="data:image/png;base64,R0lGODdhAQABAPAAAP8AAAAAACwAAAAAAQABAAACAkQBADs=" /> 

```

My PNGend which links to the owner Larry

https://github.com/hpssjellis/PNGenc

Another great resource. storing an array of images locally

https://jsfiddle.net/sbhomra/bts3xo5n/

https://www.surinderbhomra.com/Blog/2022/04/14/Storing-An-Array-of-Images-In-localStorage



Reference Files

my Portenta SD Card saving utilities  [dot513-utilities](https://github.com/hpssjellis/portenta-pro-community-solutions/tree/main/examples/dot5-portenta-machine-learning/dot51-portenta-edge-impulse-ml/dot513-utilities)

my Portenta Camera OLED files [here](https://github.com/hpssjellis/portenta-pro-community-solutions/tree/main/examples/dot3-portenta-vision-shields/dot35-camera-and-oled)

Official Arduino SD Card example [here](https://github.com/arduino/ArduinoCore-mbed/blob/master/libraries/Portenta_SDCARD/examples/TestSDCARD/TestSDCARD.ino)

Official Arduino Raw Camera example [here](https://github.com/arduino/ArduinoCore-mbed/blob/master/libraries/Camera/examples/CameraCaptureRawBytes/CameraCaptureRawBytes.ino)

Official Arduino Portenta Camera saving to SD card as BMP [here](https://github.com/arduino-libraries/Arduino_Pro_Tutorials/blob/main/examples/Vision%20Shield%20to%20SD%20Card%20bmp/visionShieldBitmap/visionShieldBitmap.ino)



ArrayBuffer stuff for javascript
```

var myBuffer = new ArrayBuffer(16);

// DataView that refers to myBuffer object
var view1 = new DataView(myBuffer);

// Int8Array that refers to myBuffer object
var view2 = new Int8Array(myBuffer);

// set value to 32 bits
view1.setInt32(0, 0x76543210);

// console log the 32 bit value
console.log("32 bit value: "+view1.getInt32(0).toString(16));

// console log  only the 8 bit value
console.log("8 bit value: "+view1.getInt8(0).toString(16));
console.log("32 bit value: "+view2[0].toString(16));


```




Also showing data on webpages

https://pqina.nl/blog/convert-an-image-to-a-base64-string-with-javascript/



