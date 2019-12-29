// Sound Machine
// This app emulates the sound of Turbo when the car accelerates
//#include <timer.h>
//auto timer = timer_create_default(); // create a timer with default settings
#include <dmtimer.h>

DMTimer recalibration(6 * 1000000); // Create a timer to recalibratevevery 6 seconds

void setup()
{
  // Knobs
  setupKnob();

  // LCD
  LCDsetup();

  // LED
  setupLED();

  // Player
  setupPlayer();

  // Accelerometer
  ACCSetup();

  //detectChange();
}

void loop()
{
  Serial.print(freeMemory());
  Serial.print("\t");

  readKnobs();
  readAccX();
  calcSma();
  detectChange();

  LCDloop();
  plot();

  if (recalibration.isTimeReached() && SMAMoving() == false) {
    Serial.println("Calibrate");
    recalibrateACC();
  }
}

void plot()
{
  //displayKnobs();
  Serial.println("");
}
