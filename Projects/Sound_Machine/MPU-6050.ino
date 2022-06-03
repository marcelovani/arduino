// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

//const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO

// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO

//int accelerationX;  // Last read of acceleration
int calibrationX;  // Calibration offset
int accelerationData[20] = {}; // Storage for the collection
char axis = 'x'; // Default axis to read accelaration

void ACCSetup(char _axis) {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif

  accelgyro.initialize();
    
  axis = _axis;

  Serial.begin(SERIAL_BAUD);

  calibrateACC();
}

int getCalibrationX()
{
  return calibrationX;
}

int * getAccelerationData()
{
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
  //accelgyro.calibrateGyro();

  DMTimer calibration(2 * 1000000); // Create a 2s timer

  calibrationX = 0;
  accelerationData[20] = { 0 };

  // Calibrate to have mainly positive readings
  short int i = 0;
  do {
    readAcc(); //temp
    calcSma();
    i++;
  } while (!calibration.isTimeReached());

  calibrationX = getSma();
  if (calibrationX < 0) {
    calibrationX = calibrationX * -1;
  }
}

// Read accelerometer
void readAcc()
{
  int16_t ax, ay, az;

  delay(getDelay()); // Add a bit of delay between readings
  accelgyro.getAcceleration(&ax, &ay, &az);

  // Push to the end of the array
  switch (axis) {
    case 'x':
      pushAccData(ax);
      break;

    case 'y':
      pushAccData(ay);
      break;
    
    case 'z':
      pushAccData(az);
      break;

    default:
      Serial.print("No axis specified:"); Serial.print("]t");
      break;
  }
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
