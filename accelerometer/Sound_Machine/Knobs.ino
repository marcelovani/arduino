#include "Lcd.h"

// The minimum value to be considered a good acceleration
float getThreshold()
{
    // @todo: Read from knob
    float t = 150;
    Serial.print(t);
    Serial.print(",");

    // @todo Only show this when the person is using this knob
    Lcd::setCursor(2, 1); 
    Lcd::printM("Threshold");
    Lcd::printV(t);

    return t;
}


// Number of samples to collect
short int getSamples() {
    // @todo: Read from knob
    short int s = 10;
    Serial.print(s);
    Serial.print(",");

    Lcd::setCursor(2, 1); 
    Lcd::printM("Samples");
    Lcd::printV(s);

    return s;
}

// The range used to calculate SMA
short int getRange() {
    // @todo: Read from knob
    short int r = 4;
    Serial.print(r);
    Serial.print(",");

    Lcd::setCursor(2, 1); 
    Lcd::printM("Range");
    Lcd::printV(r);

    return r;
}

// The delay between acceleration readings. Useful to get a smoother line
short int getDelay() {
    // @todo: Read from knob
    short int d = 20;
    Serial.print(d);
    Serial.print(",");

    Lcd::setCursor(2, 1); 
    Lcd::printM("Delay");
    Lcd::printV(d);

    return d;
}
