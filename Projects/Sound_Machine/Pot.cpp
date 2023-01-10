#include "Pot.h"

/*
    Constructor
*/
Pot::Pot(void) {
}

Pot::Pot(int8_t pin, int min, int max) {
  _pin = pin;
  _min = min;
  _max = max;

  pinMode(pin, INPUT);
}

/**
   Read the value
*/
int Pot::read() {
  int t = millis();
  int _rawValue = analogRead(_pin);

  // Prevent falsely detecting movement on the first iteration
  if (_prevValue == -9999) {
    _prevValue = _rawValue;
  }

  // Eliminate noise due to small variations of resistance
  int diff = _prevValue - _rawValue;
  if (diff < -10 || diff > 10) { //@todo make noise configurable
    // Do nothing
  }
  else {
    _rawValue = _prevValue;
  }

  //Serial.print("Raw:"); Serial.print(_rawValue); Serial.print("\t");

  // Detect change start
  if (_prevValue != _rawValue) {
    _prevValue = _rawValue;
    _moveStart = t;
    _timer = t + 500; // Set timer
  }

  // Detect change finished
  if (_moveStart != 0 && _timer < t) {
    _rawValue = _prevValue = analogRead(_pin);
    _moveStart = 0;
  }

  _value = map(_rawValue, 0, 1023, _max, _min);

  return _value;
}

/*
 * Return the pot pin
 */
int Pot::getPin()
{
  return _pin;
}

/*
 * Return the pot value
 */
int Pot::getValue()
{
  return _value;
}

/*
 * Return the pot max value
 */
int Pot::getMax()
{
  return _max;
}

/**
   Check if potentiometer is being moved
*/
bool Pot::knobMoving()
{
  return _moveStart != 0;
}
