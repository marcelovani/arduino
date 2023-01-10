#include "Pot.h"
#include "U8glib.h"

Pot thresholdPot(A3, 1, 1000); // "Threshold  ideal:600" Create an instance of Pot on pin 17 and min 1 max 1K ideal 600
Pot delayPot    (A2, 1, 40);   // "Delay       ideal:20" Create an instance of Pot on pin 16 and min 1 max 40 ideal 20
Pot samplesPot  (A0, 10, 19);  // "Samples     ideal:10" Create an instance of Pot on pin 14 and min 10 max 19 ideal 10
// Range cannot be greater than samples, see SMA
Pot rangePot    (A1, 2, 10);   // "Range       ideal:4"  Create an instance of Pot on pin 15 and min 2 max 10 ideal 4

void setupKnob() {
  readKnobs();
}

void readKnobs() {
  samplesPot.read();
  rangePot.read();
  delayPot.read();
  thresholdPot.read();
}

void displayKnobs() {
  //  Serial.print("Thres POT:"); Serial.print(getThreshold()); Serial.print(" ");
  //  Serial.print("Delay POT:"); Serial.print(getDelay());     Serial.print(" ");
  //  Serial.print("Sampl POT:"); Serial.print(getSamples());   Serial.print(" ");
  //  Serial.print("Range POT:"); Serial.print(getRange());     Serial.print("\t");

  if (!knobsMoving()) {
    return;
  }
}

bool knobsMoving() {
  return samplesPot.knobMoving() || rangePot.knobMoving() || thresholdPot.knobMoving() || delayPot.knobMoving();
}

// The range used to calculate SMA
short int getRange() {
  return rangePot.getValue();
}

// The minimum value to be considered a good acceleration
short int getThreshold()
{
  return thresholdPot.getValue();
}

// Number of samples to collect
short int getSamples() {
  return samplesPot.getValue();
}

// The delay between acceleration readings. Useful to get a smoother line
short int getDelay() {
  return delayPot.getValue();
}
