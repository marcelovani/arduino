#include "Arduino.h"
#include "Pot.h"

/*
 * Constructor
 */
Pot::Pot(int8_t pin, int max)
{
  _pin = pin;
  _max = max;
}

/**
 * Read the value
 */
int Pot::Read() 
{
  int t = millis();  
  int value = map(analogRead(_pin), 0, 1023, _max, 0);

  // Detect change start
  if (_prevValue != value) {
    int diff = _prevValue - value;
    if (diff < -1 || diff > 1) { // Eliminate noise
      _prevValue = value;
      _moveStart = t;
      _timer = t + 500; // Set timer
    }
  }

  // Detect change finished
  if (_moveStart != 0 && _timer < t) {
    _moveStart = 0;
  }

  // Display graphs
  if (Pot::Moving()) {
    //DrawDial(display, value / 204.6, 65, 50, 25, 0, 5 , 1, 0, 200, "Threshold", Redraw1);
  }

  Serial.print(value);
  Serial.print(",");

  return value;
}

/**
 * Check if potentiometer is being moved
 */
int Pot::Moving()
{
  return _moveStart != 0;
}
