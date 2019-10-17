
// The minimum value to be considered a good acceleration
float getThreshold()
{
    // @todo: Read from knob
    int t = 200;
    Serial.print(t);
    Serial.print(",");

    return t;
}


// Number of samples to collect
int getSamples() {
    // @todo: Read from knob
    int s = 20;
    Serial.print(s);
    Serial.print(",");

    return s;
}

// The range used to calculate SMA
int getRange() {
    // @todo: Read from knob
    int r = 10;
    Serial.print(r);
    Serial.print(",");

    return r;
}

// The delay between acceleration readings. Useful to get a smoother line
int getDelay() {
    // @todo: Read from knob
    int d = 3;
    Serial.print(d);
    Serial.print(",");

    return d;
}
