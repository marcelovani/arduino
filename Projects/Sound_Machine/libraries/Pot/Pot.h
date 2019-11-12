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
    void begin(PotGraph graph);

    // Read the analog pin
    int read();

    // Check if potentiometer is being moved
    bool knobMoving();

    // Set display
    void setDisplay(Adafruit_SSD1306 display);

    // Display stuff
    void display();

  private:
    PotGraph _graph;
    int8_t _pin;
    int _max;
    int _prevValue;
    int _value;
    int _moveStart;
    int _timer;
    String _label;
};

#endif
