/* Potentiometer
 * Reads potentiometers
 */
#include "Arduino.h"
#include <SoftwareSerial.h>
#include "PotGraph.h"

#ifndef Pot_h
#define Pot_h

class Pot
{
  public:
    Pot(void);
  
    Pot(short int type, int8_t pin, int max, String label);

    // Begin
    void begin();

    // Read the analog pin
    int read();

    // Check if potentiometer is being moved
    bool knobMoving();

    // Set display
    void setDisplay(Adafruit_SSD1306 display);

    // Draw stuff
    void draw();

  private:
    PotGraph _graph;
    int8_t _pin;
    int _max;
    short int _type;
    int _prevValue=-9999;
    //int _rawValue;
    int _value;
    int _moveStart;
    int _timer;
    bool _redraw=true;
    bool _drawing=false;
    String _label;
};

#endif
