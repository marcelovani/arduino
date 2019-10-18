# Turbo machine
Emulates the spray from the turbo engine after a sharp acceletation.

## How it works?
Using the accelerometer with some advanced calculations it is possible to detect variation of speed.
When the variation reaches the threshold, it will detect the acceleration/de-acceleration curve and play the sound.

## Installation
Install the libraries, open Sound_machine.ino.

## Configuration
On Arduino App, select:
- Board: Arduino Nano
- Processor: ATmega328P (Old Bootloader)
- Port: /dev/cu/wchusbserial1420
- Programmer: AVRISP mkII

## The circuit
- Arduino Nano
- Accelerometer MPU-6050
- Mp3 player
- Amplifier
- Tweet

## Wirring and Schematics
//@todo
### Boards

### Potentiomenters

### Leds

### Speakers

## Docs
https://www.silabs.com/Support%20Documents/Software/Mac_OSX_VCP_Driver.zip

https://sparks.gogo.co.nz/ch340.html

https://github.com/adrianmihalko/ch340g-ch34g-ch34x-mac-os-x-driver

https://stackoverflow.com/questions/6291931/how-to-calculate-g-force-using-x-y-z-values-from-the-accelerometer-in-android

https://forum.arduino.cc/index.php?topic=511931.0

https://www.if.ufrj.br/~pef/producao_academica/dissertacoes/2013_Leonardo_Vieira/experimentos_acelerometro.pdf

http://cache.freescale.com/files/sensors/doc/app_note/AN3397.pdf?fsrch=1&sr=2

https://www.researchgate.net/post/How_can_I_calculate_displacement_from_accelerometer_data

https://forum.arduino.cc/index.php?topic=56561.0

http://www.softschools.com/formulas/physics/acceleration_formula/1/

http://www.electronicwings.com/arduino/mpu6050-interfacing-with-arduino-uno

https://github.com/jarzebski/Arduino-MPU6050

http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html

https://github.com/jarzebski/Arduino-KalmanFilter

https://github.com/Ewenwan/ShiYanLou/blob/9753f92b48791e53b9748a3fba4845d955d9e130/MCU/arduino/driver/MPU6050_free_fall.c

https://github.com/juancgarcia/SerIOGrapher

https://pt.wikihow.com/Calcular-a-Acelera%C3%A7%C3%A3o

http://www.ppgia.pucpr.br/~santin/ee/2005/3s/4/index.html

https://www.i2cdevlib.com/forums/topic/312-velocity-from-acceleration/

http://www.chrobotics.com/library/accel-position-velocity

http://labdegaragem.com/forum/topics/calculo-de-velocidade-mpu6050

https://en.wikipedia.org/wiki/Numerical_integration

https://stats.stackexchange.com/questions/41145/simple-way-to-algorithmically-identify-a-spike-in-recorded-errors

https://en.wikipedia.org/wiki/Moving_average

https://rosettacode.org/wiki/Averages/Simple_moving_average

https://arduino.stackexchange.com/questions/25010/help-with-getting-sensor-average-using-arrays

https://stattrek.com/statistics/formulas.aspx?tutorial=stat

https://playground.arduino.cc/Main/Statistics/
