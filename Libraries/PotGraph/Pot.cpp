#include "Pot.h"

/*
    Constructor
*/
Pot::Pot(void) {
}

Pot::Pot(short int type, int8_t pin, int max, String label) {
  _type = type;
  _pin = pin;
  _max = max;
  _label = label;

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

//  Serial.print(_rawValue);
//  Serial.print("\t");

  // Eliminate noise due to small variations of resistance
  int diff = _prevValue - _rawValue;
//  Serial.print(diff);
//  Serial.print("\t");
  if (diff < -6 || diff > 6) { //@todo make noise configurable
    //_value = _rawValue;
//    Serial.print(diff);
//    Serial.print("\t");
  }
  else {
//    Serial.print("N");
//    Serial.print("\t");
    _rawValue = _prevValue;
  }

  // Detect change start
  if (_prevValue != _rawValue) {
    _prevValue = _rawValue;
    _moveStart = t;
    _timer = t + 500; // Set timer
    //_drawing = true;
  }

  // Detect change finished
  if (_moveStart != 0 && _timer < t) {
    _rawValue = _prevValue = analogRead(_pin);
    _moveStart = 0;
    //_drawing = false;
    //_redraw = true;
    // clear()
  }

  _value = map(_rawValue, 0, 1023, _max, 1);

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
 * Return the pot type
 */
int Pot::getType()
{
  return _type;
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

/*
 * Return the pot label value
 */
String Pot::getLabel()
{
  return _label;
}

/**
   Check if potentiometer is being moved
*/
bool Pot::knobMoving()
{
  return _moveStart != 0;
}
