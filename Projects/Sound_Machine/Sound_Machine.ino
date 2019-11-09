// Sound Machine
// This app emulates the sound of Turbo when the car accelerates

void setup()
{
    // LCD
    //LCDsetup();

    // LED
    //setupLED();

    // Player
    //setupPlayer();

    // Accelerometer
    calibrateACC();

    //detectChange(); //temp
}

void loop()
{
    readAccX();
    calcSma();
    detectChange();
    plot();
    //LCDloop();
}

void plot()
{
    Serial.println("");
}
