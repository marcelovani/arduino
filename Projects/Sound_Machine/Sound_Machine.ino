// Sound Machine
// This app emulates the sound of Turbo when the car accelerates
//#include <timer.h>
//auto timer = timer_create_default(); // create a timer with default settings
#include <dmtimer.h>

DMTimer recalibration(6 * 1000000); // Create a timer to recalibratevevery 6 seconds

char str[24];

void setup()
{
  // Knobs
  setupKnob();

  // LCD
  // LCDsetup();
  // LCDdisable();

  // LED
  // setupLED();

  // Player
  setupPlayer();

  // Accelerometer
  ACCSetup();

  //detectChange();
}

void loop()
{
  // sprintf(str, "Mem: %d", freeMemory());
  // Serial.print(str); Serial.print("\t");

  readKnobs();
  readAccX();
  calcSma();
  detectChange();

  // LCDloop();
  plot();

  if (recalibration.isTimeReached() && SMAMoving() == false) {
    // sprintf(str, "Calibrate:");
    // Serial.print(str); Serial.print("\t");
    recalibrateACC();
  }
}

void plot()
{
  // displayKnobs();
  //Serial.print("Calib:");   Serial.print(getCalibrationX()); Serial.print(" ");
//  Serial.print("Thres:"); Serial.print(getThreshold()); Serial.print(" ");
  //Serial.print("Offset:");  Serial.print(getCalibrationX() + getThreshold()); Serial.print(" ");
//  Serial.print("Perc:");    Serial.print((int) getPerc()); Serial.print(" ");
  Serial.println("");
}
