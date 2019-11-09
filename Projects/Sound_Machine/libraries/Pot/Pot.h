/* Potentiometer
 * Reads potentiometers
 */
#include "Arduino.h"
#include "LCD.h"

#ifndef Pot_H
#define Pot_H

class Pot : public PotLCD
{
  public:
    Pot(int8_t pin, int max, char *label, short int type);

    // Read the analog pin
    int read();

    // Check if potentiometer is being moved
    bool knobMoving();

    // Lcd display
    void display();

  private:
    int8_t _pin;
    int _max;
    int _prevValue;
    int _value;
    int _moveStart;
    int _timer;

    // Lcd
    short int _type;
    boolean _redraw;
    char _label;
};

#endif
