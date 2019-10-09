// Sound Machine
// This app emulates the sound of Turbo when the car accelerates

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
long accelerationX;  // Last read of acceleration
long calibrationX;  // Calibration offset
int16_t accelerationData[4]; // Store last 4 read data
long sma; // Simple moving average
bool smaThreshold; // Used to calculate the drop.

void setup()
{
    // LED
    setupLED();

    // Player
    setupPlayer();

    // Accelerometer
    calibrateACC();
}

void loop()
{
    readSmaThreshold();
    readAcc();
    calcSma();
    plot();
}

// Plotter
void plot()
{
    //time = millis() / 1000;
    //Serial.print(time);
    //Serial.print(',');
    Serial.print(accelerationX);
    Serial.print(',');
    Serial.print(sma);
    Serial.print(',');
    Serial.println();
}
