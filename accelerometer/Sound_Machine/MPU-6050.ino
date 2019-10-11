#include "Wire.h" // This library allows you to communicate with I2C devices.
#include <Statistic.h>

Statistic dataStats;

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

long accelerationX;  // Last read of acceleration
long calibrationX;  // Calibration offset

int range=50; // Number of range to collect @todo: make it configurable
int accelerationData[100]; // Storage for the collection

int d; // 10ms delay beween readings @todo: make it configurable
int sma; // SMA

long getSma()
{
  return sma;
}

long getAccX()
{
  return accelerationX;
}

int getRange() {
  return range;
}

int16_t getAccelerationData()
{
  return accelerationData;
}

// Calibrate accelerometer
void calibrateACC()
{
    d=1; // Set a small delay

    // Initialize
    Serial.begin(9600);
    Wire.begin();
    Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);

    // Acc config
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x1C);             //We want to write to the ACCEL_CONFIG register
    Wire.write(0x10);             //Set the register bits as 00010000 (+/- 8g full scale range)
    Wire.endTransmission(true);
    
    // Calibrate
    unsigned int count;
    count = 0;
    do {
        readAccX(d);
        calibrationX = calibrationX + accelerationX;
        count++;
    } while(count!=0x0FF);            // 256 times

    calibrationX = calibrationX >> 8;     // division between 256
}

// Read accelerometer
// Param d The delay between readings
void readAccX(int d)
{
    delay(d); // Add a bit of delay between readings

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 2, true);

    accelerationX = (Wire.read() << 8 | Wire.read()) / 2;

    // Push to the end of the array
    int i=0;
    while(i < range) {
      accelerationData[i] = accelerationData[i+1];
      i++;
    }
    accelerationData[i] = accelerationX;

    Wire.endTransmission(true);
}

// Calculate the simple moving accelaration
int calcSma() {
  dataStats.clear();

  // Update stats.
  int i=0;
  while(i < range) {
    dataStats.add(accelerationData[i]);
    i++; 
  }

  return dataStats.average();
}

void detectChange() {
  sma = calcSma();
  if (sma < -120) {
    ledOn();
  }
  else {
    ledOff();
  }
}
