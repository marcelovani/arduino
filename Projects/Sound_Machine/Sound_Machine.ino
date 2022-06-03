// Sound Machine
// This app emulates the sound of Turbo when the car accelerates
#include <dmtimer.h>

DMTimer recalibration(6 * 1000000); // Create a timer to recalibratevevery 6 seconds

char str[24];
int SERIAL_BAUD = 19200;

void setup()
{
  // Knobs
  setupKnob();

  // Player
  setupPlayer();

  // Accelerometer on Y axis
  ACCSetup('y');

  //detectChange();
}

void loop()
{
  readKnobs();
  readAcc();
  calcSma();
  detectChange();
  plot();

  if (recalibration.isTimeReached() && SMAMoving() == false) {
    recalibrateACC();
  }
}

void plot()
{
  Serial.println("");
}
