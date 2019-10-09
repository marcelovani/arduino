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
    readAccX();
    calcSma();
    plot();
}

// Plotter
void plot()
{
    //time = millis() / 1000;
    //Serial.print(time);
    //Serial.print(',');
    Serial.print(getAccX());
    Serial.print(',');
    Serial.print(calcSma());
    Serial.print(',');
    Serial.println();
}
