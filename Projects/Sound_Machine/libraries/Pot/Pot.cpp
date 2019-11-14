#include "Pot.h"

//Adafruit_SSD1306 _display;
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
void Pot::begin(Adafruit_SSD1306 &display) {
  _display = &display;

  Serial.begin(9600);
    //delay(1000);
    Serial.println("Init pot");

    //Adafruit_SSD1306 _display = &display;
    potGraph.begin(display);
//_display.begin(SSD1306_SWITCHCAPVCC, LCD_ADDR);
//_display.display();
//delay(2000);
//_display.clearDisplay();
//_display.display();
//_display.setTextSize(1);
//_display.setTextColor(SSD1306_WHITE);
//_display.setCursor(0,0);
//_display.print("Connecting to SSID\n'adafruit':");
//_display.display();

  
  bool _redraw=true;
  //potGraph.drawDial(_display, 600, 90, 50, 25, 0, 5 , 1, 0, 200, "aaa", _redraw); // @todo calculate values for scale

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
  if (diff < -6 || diff > 6) { //@todo make noise configurable
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
    //potGraph.clearDisplay(_display);
    _redraw = true;
  }

  _value = map(_rawValue, 0, 1023, _max, 1);

Serial.print(_value);
Serial.print("\t");

  // Display graphs
  if (knobMoving() && !_drawing) {
    //_redraw = true;
    _drawing = true;
    draw();
  }

  return _value;
}

void Pot::draw() {
  //@TODO draw is not working
  //potGraph.drawBarChartH(_display, 600, 10, 45, 100, 20, 0, 5, 1, 0, "A0 (volts)", _redraw);
  return;
  
    switch (_type) {
    case PotGraphTypeDial:
      potGraph.drawDial(_display, _value, 90, 50, 25, 0, 5 , 1, 0, 200, _label, _redraw); // @todo calculate values for scale
      break;

    case PotGraphTypeChartV:
      potGraph.drawBarChartV(_display, _value, 10, 45, 100, 20, 0, 5, 1, 0, _label, _redraw);
      break;

    case PotGraphTypeChartH:
      potGraph.drawBarChartH(_display, _value, 10, 45, 100, 20, 0, 5, 1, 0, _label, _redraw);
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
