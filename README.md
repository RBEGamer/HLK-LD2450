## LD2450 24Ghz Human Radar

Arduino library for HLK-LD2450 24Ghz Human body Motion Inductive Radar Sensor Module Kit

An Arduino library for the Hi-Link HLK-LD2450 24Ghz FMCW radar sensor. This sensor is a Frequency Modulated Continuous Wave radar, which makes it good for presence detection and its sensitivity at different ranges to both static and moving targets can be configured.


The code in this library is based heavily off this piece of work for ESPHome and the manufacturer datasheet.

The LD2450, as sold for configuration with the common breakout boards shown above communicates over serial at 256000 baud by default. This library allows you to configure and use the sensor over this serial connection. As the LD2450 is a device that uses a high baud rate, a microcontroller with a spare hardware UART for this communication is preferable to bit-banged software serial.


# DISCLAIMER AND NOTES

Library template for arduino based on https://github.com/arduino/Arduino/wiki/Library-Manager-FAQ
The LD2450 integration is based on https://github.com/0ingchun/arduino-lib_HLK-LD2450_Radar/ with the orgininal demonstration code placed in the example folder.