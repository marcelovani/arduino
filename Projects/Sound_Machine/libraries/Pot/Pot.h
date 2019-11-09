/* Potentiometer
 * Reads potentiometers
 */

#ifndef Pot_H
#define Pot_H

#include "Arduino.h"

class Pot
{
  public:
    Pot(int8_t pin, int max);

    // Read the analog pin
    int Read();

    // Check if potentiometer is being moved
    int Moving();

    // Lcd display
    void Display();

  private:
    int8_t _pin;
    int _max;
    int _prevValue;
    int _moveStart;
    int _timer;
};

#endif
