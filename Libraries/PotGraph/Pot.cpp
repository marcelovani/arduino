#include "Pot.h"

/*
    Constructor
*/
Pot::Pot(void) {
}

Pot::Pot(short int type, int8_t pin, int max, String label) {
  //_type = type;
  //_pin = pin;
  //_max = max;
  //_label = label;

  //  // Establish whatever pin reads you need
  pinMode(pin, INPUT);
}

/**
   Read the value
*/
int Pot::read() {
  int t = millis();
  int _rawValue = analogRead(pin);

  // Prevent falsely detecting movement on the first iteration
  if (_prevValue == -9999) {
    _prevValue = _rawValue;
  }

  Serial.print(_rawValue);
  Serial.print("\t");

  // Eliminate noise due to small variations of resistance
  int diff = _prevValue - _rawValue;
  Serial.print(diff);
  Serial.print("\t");
  if (diff < -6 || diff > 6) { //@todo make noise configurable
    //_value = _rawValue;
    Serial.print(diff);
    Serial.print("\t");
  }
  else {
    Serial.print("N");
    Serial.print("\t");
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
    _rawValue = _prevValue = analogRead(pin);
    _moveStart = 0;
    //_drawing = false;
    //_redraw = true;
    // clear()
  }

  value = map(_rawValue, 0, 1023, max, 1);

  Serial.print(value);
  Serial.print("\t");

  return value;
}

/**
   Check if potentiometer is being moved
*/
bool Pot::knobMoving()
{
  return _moveStart != 0;
}
