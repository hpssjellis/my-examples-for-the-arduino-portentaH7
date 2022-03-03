Issue on the mbed core solves a lot of these issues


https://github.com/arduino/ArduinoCore-mbed/issues/74










The pin names on the Portenta are very confusing and when trying to use the OpenMV Vision Shield it gets really confusing. This is an attempt reduce the complexity

Pull Requests would be appreciated


Information has been pulled from these pages:


# PINS 

Checkout this 

https://github.com/arduino/ArduinoCore-mbed/blob/2cd3540ce2cd2e13450f322747280b7cb018d8af/patches/0026-PortentaH7-fix-mbed-6.1-build.patch#L659-L914


# Rufus Girard
https://rufus31415.github.io/arduino-portenta-h7-carrier-board.html

His board image

https://raw.githubusercontent.com/Rufus31415/arduino-pro-portenta-h7-carrier-board/master/images/schematics.svg



# OpenMV Vision Shield
https://github.com/openmv/micropython/blob/openmv-1.12/ports/stm32/boards/PORTENTA/pins.csv

https://content.arduino.cc/assets/Schematic-Portenta_Vision_Shield_latest.pdf

https://content.arduino.cc/assets/Pinout_VisionShield_latest.pdf




# Portenta

https://content.arduino.cc/assets/Arduino-PortentaH7-schematic-V1.0.pdf

https://content.arduino.cc/assets/Pinout-PortentaH7_latest.pdf

# MBED

https://github.com/arduino/ArduinoCore-mbed/blob/master/variants/PORTENTA_H7_M7/pins_arduino.h

https://github.com/arduino/ArduinoCore-mbed/blob/master/variants/PORTENTA_H7_M7/variant.cpp\\


more mbed examples for PINS

https://github.com/arduino/ArduinoCore-mbed/blob/master/cores/arduino/mbed/targets/TARGET_STM/TARGET_STM32H7/TARGET_STM32H747xI/TARGET_PORTENTA_H7/PinNames.h



https://github.com/arduino/mbed-os/blob/portenta-mbed-6.2.0/targets/TARGET_STM/TARGET_STM32H7/TARGET_STM32H747xI/TARGET_PORTENTA_H7/PeripheralPins.c

https://github.com/arduino/mbed-os/blob/portenta-mbed-6.2.0/targets/TARGET_STM/TARGET_STM32H7/TARGET_STM32H747xI/TARGET_PORTENTA_H7/PinNames.h

https://github.com/arduino/mbed-os/blob/portenta-mbed-6.2.0/targets/TARGET_STM/TARGET_STM32H7/TARGET_STM32H747xI/TARGET_PORTENTA_H7/system_clock_override.c



