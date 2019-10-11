#include "Wire.h" // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int accelerationX;  // Last read of acceleration
int calibrationX;  // Calibration offset
int accelerationData[100]; // Storage for the collection

int getAccX()
{
  return accelerationX;
}

int * getAccelerationData()
{
  return accelerationData;
}

// Calibrate accelerometer
void calibrateACC()
{
    // Initialize board
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
        readAccX();
        calibrationX = calibrationX + accelerationX;
        count++;
    } while(count!=0x0FF);            // 256 times

    calibrationX = calibrationX >> 8;     // division between 256
}

// Read accelerometer
void readAccX()
{
    int d = getDelay();
  
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
    int r = getRange();
    int i=0;
    while(i < r) {
      accelerationData[i] = accelerationData[i+1];
      i++;
    }
    accelerationData[i] = acc;
}
