// https://www.i2cdevlib.com/forums/topic/312-velocity-from-acceleration/

#include "Wire.h" // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x[2], accelerometer_y[2], accelerometer_z[2]; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
float velocity = 0;
float currAccel;
float prevAccel = 0;
unsigned long prevTime = millis();
unsigned long currTime;
typedef struct {
  int16_t ax;
  int16_t ay;
  int16_t az;
} Accel_Data; // 6 bytes. 

typedef struct {
  uint16_t voltage;
  uint8_t l_clicked;
  uint8_t r_clicked; 
  Accel_Data ad;
} Data; // 16 bytes. 

Data d;


void setup() {
  //pinMode(LED, OUTPUT);
  //digitalWrite(LED, LOW);

  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {
  getAccelData(&(d.ad.ax));
  currAccel = d.ad.ax;

  currTime = millis();
  velocity = (currAccel + prevAccel)/2*(currTime - prevTime)/1000; //1000 added to get the same units
  prevAccel = currAccel;
  prevTime = currTime;
  
    Serial.print(velocity);
    Serial.println();
    delay(10);
}

void getAccelData(int16_t* ax){
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 2, true);
  *ax = (Wire.read() << 8 | Wire.read()) / 2;
  Wire.endTransmission(true);
}
