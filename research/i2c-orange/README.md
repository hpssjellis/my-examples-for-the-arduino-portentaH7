a04 works to scan for I2C devices. With the portenta if I connect it through SCL1 and SDA1 irt fines all three I2C channels. not really sure how it does that.

```
Scanning...
I2C device found at address 0x08  !
I2C device found at address 0x24  !
I2C device found at address 0x60  !
done
```
weird only works on SDA1 and SCL1 not 0 or 2 for me




a01, a02, a03 not working very well yet

orange led of hell 


https://github.com/arduino/ArduinoCore-mbed/issues/608
