#include <Wire.h>
#include "libraries/Pot/Pot.h"

Pot thresholdPot(A1, 900); // Recommended 800
Pot rangePot(A0, 10); // Recommended 4
Pot delayPot(A2, 50); // Recommended 20
Pot samplesPot(A3, 20); // Recommended 10

bool knobMoving() {
  return rangePot.Moving() || thresholdPot.Moving() || delayPot.Moving() || samplesPot.Moving();
}

// The range used to calculate SMA
short int getRange() {
  return rangePot.Read();
}

// The minimum value to be considered a good acceleration
int getThreshold()
{
  return thresholdPot.Read();
}

// Number of samples to collect
short int getSamples() {
  return samplesPot.Read();
}

// The delay between acceleration readings. Useful to get a smoother line
short int getDelay() {
  return delayPot.Read();
}
