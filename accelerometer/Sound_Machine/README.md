# Turbo machine
Emulates the spray from the turbo engine after a sharp acceletation.

## How it works?
Using the accelerometer with some advanced calculations it is possible to detect variation of speed.
When the variation reaches the threshold, it will detect the acceleration/de-acceleration curve and play the sound.

## The circuit
- Arduino Nano
- Accelerometer MPU-6050
- Mp3 player
- Amplifier
- Tweet

## Schematics
//@todo

## Installation
Install the libraries, open Sound_machine.ino.

## Configuration
On Arduino App, select:
- Board: Arduino Nano
- Processor: ATmega328P (Old Bootloader)
- Port: /dev/cu/wchusbserial1420
- Programmer: AVRISP mkII
