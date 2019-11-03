// Sound Machine
// This app emulates the sound of Turbo when the car accelerates
#include "Lcd.h"

void setup()
{
    // LCD
    Lcd::setupLcd();

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
    calcSma();
    detectChange();
    plot();
}

void plot()
{
    Serial.println("");
}
