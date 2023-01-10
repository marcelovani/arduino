#include "Arduino.h"

#ifndef Pot_h
#define Pot_h

class Pot {
  public:

    Pot(void);

    Pot(int8_t pin, int min, int max);

    int read();

    int getValue();

    int getMax();

    int getPin();

    String getLabel();

    // Check if potentiometer is being moved
    bool knobMoving();

  private:
    int8_t _pin;
    short int _min;
    short int _max;
    short int _value;

    int _prevValue=-9999;
    int _moveStart;
    int _timer;

};

#endif
