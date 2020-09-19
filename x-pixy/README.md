|This folder is for examples using the portenta with the pixy2 Charmed labs color detection webcam.

Note: The pixy library for the arduino does not work out of the box, you have to delete the last 4 files. this zipped file is a working Adruno library that needs to be unzipped and then put in your local libraries folder. (where all your other libraries are stored.)


I think SCK on the Portenta is CK

PortenaH7 --> Pixy2  
+5V --> VIN     
GND --> GND   
D10 --> MISO   
D9  --> SCK   
D8  --> MOSI   





![wire connectors](../image-video/pixy2-wiring.png)


![PortenaH7 Pinout](../image-video/bothPinout.png)

First load a01_ccc_pixy.ino just to see if the Pixy2 is connected correctly. Bit confusing to program so best to use the pixymon program to visually program the pixy. https://pixycam.com/downloads-pixy2/ looking for pixymon V2

![Pixy working](../image-video/pixy-combined.jpg)

What the windows program that can see what the arduino sees.

![Pixymon](../image-video/pixymon.png)
