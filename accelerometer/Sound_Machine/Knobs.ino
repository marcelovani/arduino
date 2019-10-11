
// The minimum value to be considered a good acceleration
int getThreshold()
{
    // @todo: Read from knob
    return 0.8;
}

// Number of range to collect @todo: make it configurable
int getRange() {
    // @todo: Read from knob
    return 50;
}

// The delay betwwn acceleration readings. Useful to get a smoother line
int getDelay() {
    // @todo: Read from knob
    return 5;
}
