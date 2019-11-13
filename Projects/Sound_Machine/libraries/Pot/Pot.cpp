#include "Pot.h"

PotGraph potGraph;

/*
 * Constructor
 */
Pot::Pot(void) {
  
}
 
Pot::Pot(short int type, int8_t pin, int max, String label)
{
//  _graph = potGraph;
  _type = type;
  _pin = pin;
  _max = max;
  _label = label;

  // Establish whatever pin reads you need
  pinMode(_pin, INPUT);
}

/*
 * Begin
 */
void Pot::begin() {
    
  Serial.begin(9600);
    //delay(1000);
    Serial.println("Init pot");
    
  potGraph.begin();
//void Pot::begin() {
  //_graph = graph;
}

/**
 * Read the value
 */
int Pot::read() 
{ 
  int t = millis();  
  int _rawValue = analogRead(_pin);

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
  if (diff < -5 || diff > 3) { //@todo detect diff based on raw value 0 - 1024
    //_value = _rawValue;
    Serial.print(diff);
    Serial.print("\t");
  }
  else
  {
    Serial.print("N");
    Serial.print("\t");
    _rawValue = _prevValue;
  }

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
    _drawing = false;
    potGraph.clearDisplay();
  }

  _value = map(_rawValue, 0, 1023, 0, _max);

Serial.print(_value);
Serial.print("\t");

  // Display graphs
  if (knobMoving() && !_drawing) {
    //_redraw = true;
    _drawing = true;
    draw();
  }
  else {
  }

  return _value;
}

void Pot::draw() {
    switch (_type) {
    case PotGraphTypeDial:
      potGraph.drawDial(potGraph._display, _value, 90, 50, 25, 0, 5 , 1, 0, 200, _label, _redraw); // @todo calculate values for scale
      break;

    case PotGraphTypeChartV:
      potGraph.drawBarChartV(potGraph._display, _value, 90, 50, 25,   0, 5, 1, 0, 200, _label, _redraw);
      break;

    case PotGraphTypeChartH:
      potGraph.drawBarChartH(potGraph._display, _value, 90, 50, 25, 0, 5 , 1, 0, 200, _label, _redraw);
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
