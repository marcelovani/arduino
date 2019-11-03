#include "Wire.h" // This library allows you to communicate with I2C devices.

int led1 = 8; // Yellow
int led2 = 9; // Yellow
int led3 = 10; // Yellow
int led4 = 11; // Yellow
int led5 = 12; // Red

short int LED = 13; // Led number
bool ledStatus = 0;

void setupLED()
{
    // LED
    pinMode(LED, OUTPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    ledOn();
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

  // Show percentage
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  
  if (perc > 10) {
    digitalWrite(led1, HIGH);
  }
  if (perc > 30) {
    digitalWrite(led2, HIGH);
  }
  if (perc > 50) {
    digitalWrite(led3, HIGH);
  }
  if (perc > 70) {
    digitalWrite(led4, HIGH);
  }
  if (perc > 90) {
    digitalWrite(led5, HIGH);
  }
}
