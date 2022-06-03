#include "Arduino.h"

#ifndef Pot_h
#define Pot_h

class Pot {
  public:
    int8_t type;
    int8_t pin;
    short int max;
    String label;
    short int value;

    Pot(void);

    Pot(short int type, int8_t pin, int max, String label);

    int read();

    // Check if potentiometer is being moved
    bool knobMoving();

  private:    
    int _prevValue=-9999;
    int _moveStart;
    int _timer;

};

#endif
