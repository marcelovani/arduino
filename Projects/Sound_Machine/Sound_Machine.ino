// Sound Machine
// This app emulates the sound of Turbo when the car accelerates

void setup()
{
  // LCD
  LCDsetup();
  //AdaFruitLCDSetup();

  // LED
  //setupLED();

  // Player
  setupPlayer();

  // Accelerometer
  calibrateACC();

  detectChange(); //temp
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
}

void plot()
{
  //displayKnobs();
  Serial.println("");
}
