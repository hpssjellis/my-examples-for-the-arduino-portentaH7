#!/bin/bash
sudo cat /etc/udev/rules.d/20-arduino.rules
SUBSYSTEM=="usb", ATTRS{idVendor}=="2341", MODE="0666"
