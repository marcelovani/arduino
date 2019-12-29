#include "Pot.h"
#include "U8glib.h"

Pot samplesPot  (A0, 20);   // "Samples     ideal:10" Create an instance of Pot on pin 14 and max of 20 ideal 10
Pot rangePot    (A1, 10);   // "Range        ideal:4" Create an instance of Pot on pin 15 and max of 10 ideal 4
Pot delayPot    (A2, 40);   // "Delay       ideal:20" Create an instance of Pot on pin 16 and max of 40 ideal 20
Pot thresholdPot(A3, 1000); // "Threshold  ideal:600" Create an instance of Pot on pin 17 and max of 1K ideal 600

void readKnobs() {
  samplesPot.read();
  rangePot.read();
  delayPot.read();
  thresholdPot.read();
}

void displayKnobs() {
  if (!knobsMoving()) {
    return;
  }

  char str[24];
  u8g.firstPage();
  u8g.setFontPosTop();
  u8g.setFont(u8g_font_5x7r);

  do {
    if (samplesPot.knobMoving()) {
      sprintf(str, "Samples: %d    ideal: 10", samplesPot.getValue());
      u8g.drawStr(0, 0, str);
      Serial.print(samplesPot.getValue()); Serial.print("\t");
    } else if (rangePot.knobMoving()) {
      sprintf(str, "Range: %d       ideal: 4", rangePot.getValue());
      u8g.drawStr(0, 0, str);
      Serial.print(rangePot.getValue()); Serial.print("\t");
    } else if (thresholdPot.knobMoving()) {
      sprintf(str, "Threshold: %d ideal: 600", thresholdPot.getValue());
      u8g.drawStr(0, 0, str);
      Serial.print(thresholdPot.getValue()); Serial.print("\t");
    } else if (delayPot.knobMoving()) {
      sprintf(str, "Delay: %d     ideal: 20", delayPot.getValue());
      u8g.drawStr(0, 0, str);
      Serial.print(delayPot.getValue()); Serial.print("\t");
    }
  } while (u8g.nextPage());
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
