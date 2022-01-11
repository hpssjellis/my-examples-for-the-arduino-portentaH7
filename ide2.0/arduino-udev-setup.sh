#!/bin/bash

# run the following commands without the #
# chmod +x arduino-udev-setup.sh
# sudo ./arduino-udev-setup.sh






echo "This script should make or append udev rules to the file 20-arduino.rules "
echo "in the administrators folder /etc/udev/rules.d"
echo "enter any key to continue"
read


# Append the arduino udev rules to the folder at /etc/udev/rules.d
echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="2341", MODE="0666"' | sudo tee -a /etc/udev/rules.d/20-arduino.rules

echo "H0pefully finished correctly."
echo "now showing the file"
echo "enter any key to continue"
read
# show the file
cat /etc/udev/rules.d/20-arduino.rules








#old
#sudo echo "My Text on Line 2" >> myfile
#sudo cat /etc/udev/rules.d/20-arduino.rules
#SUBSYSTEM=="usb", ATTRS{idVendor}=="2341", MODE="0666"
