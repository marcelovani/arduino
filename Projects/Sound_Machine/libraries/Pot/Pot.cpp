#include "Pot.h"

//PotGraph potGraph;

/*
 * Constructor
 */
Pot::Pot(void) {
  
}
 
Pot::Pot(short int type, int8_t pin, int max, String label)
{
//  _graph = potGraph;
  _pin = pin;
  _max = max;
  _label = label;

  // Establish whatever pin reads you need
  pinMode(_pin, INPUT);
}

/*
 * Begin
 */
void Pot::begin(PotGraph graph) {
//void Pot::begin() {
  //_graph = graph;
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
  //if (knobMoving()) {
    display();
  //}

  return _value;
}

void Pot::display() {
    switch (_graph.getType()) {
    case PotGraphTypeDial:
      boolean _redraw = true;
      //potGraph.drawDial(_value, 90, 50, 25, 0, 5 , 1, 0, 200, _label, _redraw); // @todo calculate values for scale
      break;

    case PotGraphTypeChartV:
      //potGraph.drawBarChartV(_value, 90, 50, 25,   0, 5, 1, 0, 200, _label, _redraw);
      break;

    case PotGraphTypeChartH:
      //potGraph.drawBarChartH(_value, 90, 50, 25, 0, 5 , 1, 0, 200, _label, _redraw);
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
