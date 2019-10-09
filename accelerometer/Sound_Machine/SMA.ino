long sma; // Simple moving average
bool smaThreshold; // Used to calculate the drop.

// Calculate Simple Moving Average and detects drop
long calcSma()
{
    // Todo; calculate properly
    sma = accelerationData[0] + accelerationData[1] + accelerationData[2] + accelerationData[3] / 4;
}
