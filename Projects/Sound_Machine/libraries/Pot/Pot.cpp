#include "Arduino.h"
#include "Pot.h"
#include <SoftwareSerial.h>

PotLCD PotDisplay();

/*
 * Constructor
 */
Pot::Pot(int8_t pin, int max, char *label, short int type=PotLCDTypeDial)
{
  _pin = pin;
  _max = max;

  // Lcd
  _label = label;
  _type = type;
  _redraw = true;

  // Establish whatever pin reads you need
  pinMode(_pin, INPUT);

  Serial.begin(9600);
  delay(100);
  Serial.print("Pot initialized! pin: ");
  Serial.print(pin);
  Serial.print(" max: ");
  Serial.print(max);
  Serial.print(" type: ");
  Serial.print(type);
  Serial.print(" label: ");
  Serial.println(label);
}

/**
 * Read the value
 */
int Pot::read() 
{
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

  Serial.print(_value);
  Serial.print(",");

  return _value;
}

/*
 * Display the graph
 */
void Pot::display()
{
  /*
  switch (_type) {
    case PotLCDTypeDial:
      PotLCD::DrawDial(PotDisplay, _value, 90, 50, 25, 0, 5 , 1, 0, 200, _label, _redraw); // @todo calculate values for scale
      break;

    case PotLCDTypeChartV:
      PotLCD::DrawBarChartV(PotDisplay, _value, 90, 50, 25,   0, 5, 1, 0, 200, _label, _redraw);
      break;

    case PotLCDTypeChartH:
      PotLCD::DrawBarChartH(PotDisplay, _value, 90, 50, 25, 0, 5 , 1, 0, 200, _label, _redraw);
      break;

    default:
      break;
  }
  */
}

/**
 * Check if potentiometer is being moved
 */
bool Pot::knobMoving()
{
  return _moveStart != 0;
}
