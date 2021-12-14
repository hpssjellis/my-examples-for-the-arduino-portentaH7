Strangely the adxl362 does not work with the SPI.h library for the mbed Portenta. 


Very irritating. the main ADXL362 library src file needs this replacement
```
   // SPI.setDataMode(SPI_MODE0);	//CPHA = CPOL = 0    MODE = 0
   SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
   
   ```
   
   
   possibly
   
   ```
   
   // SPI.setDataMode(SPI_MODE0);	//CPHA = CPOL = 0    MODE = 0
   SPI.beginTransaction(SPISettings(4000000, LSBFIRST, SPI_MODE0));
   
   ```
   
   Then raw data seems to work




datasheet for the adxl362  http://dlnmh9ip6v2uc.cloudfront.net/datasheets/BreakoutBoards/ADXL362.pdf



Good reference  https://os.mbed.com/users/tkreyche/notebook/adxl362_tkreyche/



Another arduino reference https://ez.analog.com/mems/w/documents/4505/adxl362-arduino-how-to

And another https://os.mbed.com/users/tkreyche/notebook/adxl362_tkreyche/

Images and purchase at sparkfun  https://www.sparkfun.com/products/11446

![adxl362](https://cdn.sparkfun.com//assets/parts/7/2/9/8/11446-03a.jpg)

![adxl362](https://cdn.sparkfun.com//assets/parts/7/2/9/8/11446-04a.jpg)
