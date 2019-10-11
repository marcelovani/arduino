#include "Wire.h" // This library allows you to communicate with I2C devices.

int LED = 13; // Led number

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
}

// LED off
void ledOff()
{
    digitalWrite(LED, LOW);
}

// Display LED bar depending on Acceleration
void ledBar() {
  
}
