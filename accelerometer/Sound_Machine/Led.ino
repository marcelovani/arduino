#include "Wire.h" // This library allows you to communicate with I2C devices.

int LED = 13; // Led number
bool ledStatus = 0;

void setupLED()
{
    // LED
    pinMode(LED, OUTPUT);
    ledOff();
}

// LED on
void ledOn()
{
    digitalWrite(LED, HIGH);
    ledStatus = 1;
}

// LED off
void ledOff()
{
    digitalWrite(LED, LOW);
    ledStatus = 0;
}

// Display LED bar depending on Acceleration
// @todo display LED bar
void ledBar(float perc) {
  //Serial.print("\tLED: ");
  if (ledStatus == 1) {
    //Serial.print("ON ");
    Serial.print(getCalibrationX() + getThreshold());
  }
  else {
    Serial.print(0);
    //Serial.print("OFF ");
  }
  //Serial.println(", ");
}
