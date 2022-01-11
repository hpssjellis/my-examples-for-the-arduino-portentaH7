#!/bin/bash

# run the following commands without the #
# chmod -x linux-install.sh
# sudo ./linux-install.sh




#old
#sudo echo "My Text on Line 2" >> myfile
#sudo cat /etc/udev/rules.d/20-arduino.rules
#SUBSYSTEM=="usb", ATTRS{idVendor}=="2341", MODE="0666"


# Append the arduino udev rules to the folder at /etc/udev/rules.d
echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="2341", MODE="0666"' | sudo tee -a /etc/udev/rules.d/20-arduino.rules


# show the file
cat /etc/udev/rules.d/20-arduino.rules

