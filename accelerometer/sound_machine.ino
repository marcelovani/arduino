// Sound Machine
// This app emulates the sound of Turbo when the car accelerates

#include "Wire.h" // This library allows you to communicate with I2C devices.
#include "SoftwareSerial.h" // Serial for Player
#include "DFRobotDFPlayerMini.h" // DFPlayer

SoftwareSerial SoftSerial(10, 11); // RX, TX
DFRobotDFPlayerMini DFPlayer; // Player

int LED = 13; // Led number

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
long accelerationX  // Last read of acceleration
long calibrationX  // Calibration offset
int16_t accelerationData[4] // Store last 4 read data
long sma // Simple moving average
bool smaThreshold // Used to calculate the drop.

void setup()
{
    // LED
    pinMode(LED, OUTPUT);
    ledOff()

    // Player
    setupPlayer()

    // Accelerometer
    calibrateACC()
}

// Initialize player
void setupPlayer()
{
  SoftSerial.begin(9600);
  if (!DFPlayer.begin(SoftSerial))
  { // Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    //@todo flash led to indicate error condition
    while (true)
      ;
  }
  Serial.println(F("DFPlayer Mini online."));

  DFPlayer.setTimeOut(500); // Set serial communication time out 500ms
  DFPlayer.volume(25);      // Set volume value (0~30).
  DFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  DFPlayer.outputDevice(DFPLAYER_DEVICE_SD); // Set device we use SD as default
  //DFPlayer.play(1);
}

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
        readAcc();
        calibrationX = calibrationX + acceleration;
        count++;
    } while(count!=0x0FF);            // 256 times

    calibrationX=calibrationX>>8;     // division between 256
}

void loop()
{
    readSmaThreshold();
    readAcc();
    calcSma();
    plot();
}

void readAcc()
{
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 2, true);

    acceleration = (Wire.read() << 8 | Wire.read()) / 2;

    // Push to the end of the array
    accelerationx[0] = accelerationx[1];
    accelerationx[1] = accelerationx[2];
    accelerationx[2] = accelerationx[3];
    accelerationx[3] = acceleration;

    Wire.endTransmission(true);
}

void readSmaThreshold()
{
    // todo: Read from knob
    return 0.8;
}

// Calculate Simple Moving Average and detects drop
void calcSma()
{
    // Todo; calculate properly
    sma = accelerationx[0] + accelerationx[1] + accelerationx[2] + accelerationx[3] / 4;
}

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

void ledOn()
{
    digitalWrite(LED, HIGH);
}

void ledOff()
{
    digitalWrite(LED, LOW);
}
