#include "Wire.h" // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int accelerationX;  // Last read of acceleration
int calibrationX;  // Calibration offset
int accelerationData[20] = {}; // Storage for the collection

void ACCSetup() {
  // Initialize board
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  // Acc config
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1C);             // We want to write to the ACCEL_CONFIG register
  Wire.write(0x10);             // Set the register bits as 00010000 (+/- 8g full scale range)
  Wire.endTransmission(true);

  calibrateACC();
}

int getCalibrationX()
{
  return calibrationX;
}

int getAccX()
{
  return accelerationX;
}

int * getAccelerationData()
{
  //  Test data
  //  accelerationData[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  return accelerationData;
}

void recalibrateACC() {
  calibrationX = getSma();
  if (calibrationX < 0) {
    calibrationX = calibrationX * -1;
  }
}

// Calibrate accelerometer
// @todo if the inclination changes for some period, the calibration should be re-done
void calibrateACC()
{
  DMTimer calibration(2 * 1000000); // Create a 2s timer

  calibrationX = 0;
  accelerationData[20] = { 0 };

  // Calibrate to have mainly positive readings
  short int i = 0;
  do {
    readAccX(); //temp
    calcSma();
    i++;
    Serial.println(getSma());
  } while (!calibration.isTimeReached());

  calibrationX = getSma();
  if (calibrationX < 0) {
    calibrationX = calibrationX * -1;
  }
  Serial.print("Calibration done: ");
  Serial.println(getCalibrationX());
}

// Read accelerometer
void readAccX()
{
  short int d = getDelay();
  delay(d); // Add a bit of delay between readings

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 2, true);

  accelerationX = (Wire.read() << 8 | Wire.read()) / 2;

  // Push to the end of the array
  pushAccData(accelerationX);

  Wire.endTransmission(true);
}

// Push to the end of the array
void pushAccData(int acc) {
  short int s = getSamples();
  short int i = 0;
  while (i < s) {
    // Move from bottom to top.
    accelerationData[i] = accelerationData[i + 1];
    i++;
  }
  // Set bottom value.
  accelerationData[s - 1] = acc;
}
