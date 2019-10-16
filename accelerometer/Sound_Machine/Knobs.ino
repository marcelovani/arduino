
// The minimum value to be considered a good acceleration
float getThreshold()
{
    // @todo: Read from knob
    return 500;
}

// Number of range to collect @todo: make it configurable
int getRange() {
    // @todo: Read from knob
    return 50;
}

// The delay between acceleration readings. Useful to get a smoother line
int getDelay() {
    // @todo: Read from knob
    return 5;
}
