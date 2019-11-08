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

float AccX[200]; //array for the current acceleration after sampling
float AccX2[200];
float vXn2[200]; //array for the current velocity
float ActualAccelX2;
float ActualVelX2;

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
  currTime = millis();

  getAccelData(&(d.ad.ax));
  ActualAccelX2 = d.ad.ax;
  if(millis() % 1 == 0) //sampling at 1KHz
  {
    for(int n = 1; n<currTime; n++)
    {
      AccX2[n] = ActualAccelX2; //filling the array with the current accel
      vXn2[n] = vXn2[n-1] + (AccX2[n])*0.001; //vX2[n] is the current velocity, vX2[n-1] is the previous velocity and AccX2[n] is the current accel
      ActualVelX2 = vXn2[n];
    } 
  }
    Serial.print(ActualAccelX2);
    Serial.print(",");
    Serial.print(ActualVelX2);
    Serial.println();        

//  velocity = (currAccel + prevAccel)/2*(currTime - prevTime)/1000; //1000 added to get the same units
//  prevAccel = currAccel;
//  prevTime = currTime;
  

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
