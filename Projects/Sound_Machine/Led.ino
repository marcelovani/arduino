#include "Wire.h" // This library allows you to communicate with I2C devices.

bool ledStatus = 0;

void setupLED()
{
    // LED
    ledOn();
}

// LED on
void ledOn()
{
    ledStatus = 1;
}

// LED off
void ledOff()
{
    ledStatus = 0;
}

// Display LED bar depending on Acceleration
// @todo display LED bar
void ledBar(short int perc) {
  perc = perc;
  if (ledStatus == 1) {
    Serial.print(getCalibrationX() + getThreshold());
  }
  else {
    Serial.print(0);
  }
}
