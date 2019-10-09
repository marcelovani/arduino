#include "Wire.h" // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
long accelerationX;  // Last read of acceleration
long calibrationX;  // Calibration offset
int16_t accelerationData[4]; // Store last 4 read data

long getAccX()
{
  return accelerationX;
}

long getAccelerationData()
{
  return accelerationData;
}

// Calibrate accelerometer
void calibrateACC()
{
    // Initialize
    Serial.begin(9600);
    Wire.begin();
    Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);

    // Calibrate
    unsigned int count;
    count = 0;
    do {
        readAccX();
        calibrationX = calibrationX + accelerationX;
        count++;
    } while(count!=0x0FF);            // 256 times

    calibrationX = calibrationX >> 8;     // division between 256
}

// Read accelerometer
void readAccX()
{
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 2, true);

    accelerationX = (Wire.read() << 8 | Wire.read()) / 2;

    // Push to the end of the array
    accelerationData[0] = accelerationData[1];
    accelerationData[1] = accelerationData[2];
    accelerationData[2] = accelerationData[3];
    accelerationData[3] = accelerationX;

    Wire.endTransmission(true);
}
