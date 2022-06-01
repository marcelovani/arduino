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
    //Serial.print("LED:"); Serial.print(ledStatus); Serial.print(" ");
}

// LED off
void ledOff()
{
    ledStatus = 0;
    //Serial.print("LED:"); Serial.print(ledStatus); Serial.print(" ");
}

// Display LED bar depending on Acceleration
// @todo display LED bar
void ledBar(short int perc) {
  perc = perc;
  if (ledStatus == 1) {
    sprintf(str, "Thre: %d", getCalibrationX() + getThreshold());
  }
  else {
    sprintf(str, "Thre: %d", 0);
  }
  //Serial.print("Perc:"); Serial.print(perc); Serial.print("\t");
}
