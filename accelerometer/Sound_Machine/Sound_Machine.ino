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

//detectChange(); //temp
}

void loop()
{
    readAccX();
    calcSma(); // temp
    detectChange(); //temp
    plot();
}

void plot()
{
    Serial.println("");
}
