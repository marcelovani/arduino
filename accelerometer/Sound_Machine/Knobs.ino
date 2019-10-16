
// The minimum value to be considered a good acceleration
float getThreshold()
{
    // @todo: Read from knob
    return 200;
}


// Number of samples to collect
int getSamples() {
    // @todo: Read from knob
    return 20;
}

// The range used to calculate SMA
int getRange() {
    // @todo: Read from knob
    return 3;
}

// The delay between acceleration readings. Useful to get a smoother line
int getDelay() {
    // @todo: Read from knob
    return 5;
}
