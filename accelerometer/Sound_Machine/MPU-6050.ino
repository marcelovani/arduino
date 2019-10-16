#include "Wire.h" // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int accelerationX;  // Last read of acceleration
int calibrationX;  // Calibration offset
int accelerationData[100] = {}; // Storage for the collection

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
  
// temp;
//  accelerationData[0] = 0.004100*100;
//  accelerationData[1] = 0.007197*100;
//  accelerationData[2] = 0.011027*100;
//  accelerationData[3] = 0.066737*100;
//  accelerationData[4] = 0.123896*100;
//  accelerationData[5] = 0.164286*100;
//  accelerationData[6] = 0.144007*100;
//  accelerationData[7] = 0.184352*100;
//  accelerationData[8] = 0.160792*100;
//  accelerationData[9] = 0.226908*100;
//  accelerationData[10] = 0.122142*100;
//  accelerationData[11] = 0.037059*100;
//  accelerationData[12] = 0.091420*100;

//  accelerationData[0] = 1;
//  accelerationData[1] = 2;
//  accelerationData[2] = 3;
//  accelerationData[3] = 4;
//  accelerationData[4] = 5;
//  accelerationData[5] = 6;
//  accelerationData[6] = 7;
//  accelerationData[7] = 8;
//  accelerationData[8] = 9;

  
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
    Wire.write(0x1C);             // We want to write to the ACCEL_CONFIG register
    Wire.write(0x10);             // Set the register bits as 00010000 (+/- 8g full scale range)
    Wire.endTransmission(true);
    
    // Calibrate to have mainly positive readings
//    int s = getSamples();
    int i = 0;
//    int sum = 0;
//    int avg = 0;
    while (i < 100) {
      readAccX(); //temp
      calcSma();
      i++;
    }
//    int * data = getSma();
    calibrationX = getSma();
    if (calibrationX < 0) {
      calibrationX = calibrationX * -1;
    }
    Serial.println();
    Serial.println("Calculating offset");
    Serial.println(calibrationX);
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
    pushAccData(accelerationX + calibrationX);

    Wire.endTransmission(true);
}

// Push to the end of the array
void pushAccData(int acc) {
    int s = getSamples();
    int i = 0;
    while (i < s) {
      // Move from bottom to top.
      accelerationData[i] = accelerationData[i+1];
      i++;
    }
    // Set bottom value.
    accelerationData[s-1] = acc;
}
