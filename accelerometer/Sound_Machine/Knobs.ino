
// The minimum value to be considered a good acceleration
float getThreshold()
{
    // @todo: Read from knob
    float t = 200;
    Serial.print(t);
    Serial.print(",");

    return t;
}


// Number of samples to collect
short int getSamples() {
    // @todo: Read from knob
    short int s = 10;
    Serial.print(s);
    Serial.print(",");

    return s;
}

// The range used to calculate SMA
short int getRange() {
    // @todo: Read from knob
    short int r = 4;
    Serial.print(r);
    Serial.print(",");

    return r;
}

// The delay between acceleration readings. Useful to get a smoother line
short int getDelay() {
    // @todo: Read from knob
    short int d = 3;
    Serial.print(d);
    Serial.print(",");

    return d;
}
