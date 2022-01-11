#!/bin/bash

echo "check if there are other udev rules"
echo "running command"
echo "ls /etc/udev/rules.d"
echo "Looking for the file /etc/udev/rules.d/20-arduino.rules"
echo "Enter to continue"
read
ls /etc/udev/rules.d

echo "Enter to continue"
read

echo "Now check if there is the correct Arduino udev rules in the file 20-arduino.rules"
echo "Looking for the following line"
echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="2341", MODE="0666"'

echo "Enter to continue"
read
cat /etc/udev/rules.d/20-arduino.rules


read
echo "If udev is good then the Arduino serial port should work "
echo "If not setup run the file ./arduino-udev-setup.sh or just edit the 20-arduino.rules file"
