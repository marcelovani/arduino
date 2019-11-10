#include "Pot.h"

PotLCD _potLcd;

/*
 * Constructor
 */
Pot::Pot(int8_t pin, int max, String label, short int type=PotLCDTypeDial)
{
  _pin = pin;
  _max = max;

  // Lcd
  _label = label;
  _type = type;
  _redraw = true;

  // Establish whatever pin reads you need
  pinMode(_pin, INPUT);
}

/**
 * Read the value
 */
int Pot::read() 
{
return 000000000;
  
  int t = millis();  
  int _value = map(analogRead(_pin), 0, 1023, _max, 0);

  // Eliminate noise due to small variations of resistance
  int diff = _prevValue - _value;
  if (diff < -1 || diff > 1) {
    // Skip this
  }
  else
  {
    _value = _prevValue;
  }

  // Detect change start
  if (_prevValue != _value) {
    _prevValue = _value;
    _moveStart = t;
    _timer = t + 500; // Set timer
  }

  // Detect change finished
  if (_moveStart != 0 && _timer < t) {
    _moveStart = 0;
  }

  // Display graphs
  if (knobMoving()) {
    Pot::display();
  }

  return _value;
}

/*
 * Display the graph
 */
void Pot::display()
{
  switch (_type) {
    case PotLCDTypeDial:
      _potLcd.drawDial(_value, 90, 50, 25, 0, 5 , 1, 0, 200, _label, _redraw); // @todo calculate values for scale
      break;

    case PotLCDTypeChartV:
      _potLcd.drawBarChartV(_value, 90, 50, 25,   0, 5, 1, 0, 200, _label, _redraw);
      break;

    case PotLCDTypeChartH:
      _potLcd.drawBarChartH(_value, 90, 50, 25, 0, 5 , 1, 0, 200, _label, _redraw);
      break;

    default:
      break;
  }
}

/**
 * Check if potentiometer is being moved
 */
bool Pot::knobMoving()
{
  return _moveStart != 0;
}
