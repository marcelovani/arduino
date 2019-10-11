// Sound Machine
// This app emulates the sound of Turbo when the car accelerates

void setup()
{
    // LED
    setupLED();

    // Player
    setupPlayer();

    // Accelerometer
    calibrateACC();

}

void loop()
{
    readSmaThreshold();
    readAccX(5);
    detectChange();
    plot();
}

// Plotter
void plot()
{
    Serial.print(getSma());
    Serial.println();
}
