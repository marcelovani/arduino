#include "Arduino.h"

#ifndef Pot_h
#define Pot_h

class Pot {
  public:

    Pot(void);

    Pot(short int type, int8_t pin, int max, String label);

    int read();

    int getType();

    int getValue();

    int getMax();

    int getPin();

    String getLabel();

    // Check if potentiometer is being moved
    bool knobMoving();

  private:
    int8_t _type;
    int8_t _pin;
    short int _max;
    String _label;
    short int _value;

    int _prevValue=-9999;
    int _moveStart;
    int _timer;

};

#endif
