//https://github.com/jimmery/IEEE-Advanced-Projects/blob/0825aa87f889103e7fcc23b9956ad13398499d6b/AirMouse/AirMouse.ino

#include <Wire.h>

#define BATT_CHECK A3
#define CS_Pin 10
#define CE_Pin 14
#define l_click 9
#define r_click 8

const int MPU_addr = 0x68;
long sstatex;
float Sample_X;
int16_t accelerationx[2];
long velocityx[2];
long positionX[2];
float countx;

bool lbutt[3] = {false, false, false};
bool rbutt[3] = {false, false, false};

typedef struct {
  int16_t ax;
  int16_t ay;
  int16_t az;
} Accel_Data; // 6 bytes. 

typedef struct {
  int16_t gx;
  int16_t gy;
  int16_t gz;
} Gyro_Data; // 6 bytes. 

typedef struct {
  uint16_t voltage;
  uint8_t l_clicked;
  uint8_t r_clicked; 
  Accel_Data ad;
  Gyro_Data gd;
} Data; // 16 bytes. 

Data d;

typedef enum : uint8_t {
  GYRO_PREC_250 = 0,
  GYRO_PREC_500,
  GYRO_PREC_1000,
  GYRO_PREC_2000,
} gyro_precision_e; //declares a type gyro_precision_e that consists of 4 8bit unsigned integers

typedef enum : uint8_t
{
  ACCEL_PREC_2 = 0,
  ACCEL_PREC_4,
  ACCEL_PREC_8,
  ACCEL_PREC_16
} accel_precision_e; //declares accel_precision_e

void getAccelData(int16_t* ax){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 2, true);
  *ax = (Wire.read() << 8 | Wire.read()) / 2;
  Wire.endTransmission(true);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Calibrate();
}

void loop() {
  // put your main code here, to run repeatedly:

    unsigned char count2;
    count2 = 0;

    do
    {

        getAccelData(&(d.ad.ax));
        accelerationx[1] = accelerationx[1] + Sample_X; //filtering routine for noise attenuation
        //an instant
        count2++;

    } while (count2 != 0x40); // 64 sums of the acceleration sample

    accelerationx[1] = accelerationx[1] >> 6; // division by 64
    accelerationx[1] = accelerationx[1] - (int)sstatex; //eliminating zero reference
    if ((accelerationx[1] <= 3) && (accelerationx[1] >= -3)) //Discrimination window applied
    {
        accelerationx[1] = 0;
    } // to the X axis acceleration
    
    //first X integration:
    velocityx[1] = velocityx[0] + accelerationx[0] + ((accelerationx[1] - accelerationx[0]) >> 1);
    accelerationx[0] = accelerationx[1]; //The current acceleration value must be sent
    velocityx[0] = velocityx[1]; //Same done for the velocity variable
    
    positionX[1] = positionX[1] << 18; //The idea behind this shifting (multiplication)


    //if (d.ad.ax < 0) {
    //  d.ad.ax = d.ad.ax * -1;
   // }
    
    Serial.print(d.ad.ax);
    Serial.print(",");
    Serial.print(velocityx[1]);
    Serial.print(",");
    Serial.print(Sample_X);
    Serial.println();

    positionX[1] = positionX[1] >> 18; //once the variables are sent them must return to
    movement_end_check();
    positionX[0] = positionX[1]; //actual position data must be sent to the

    delay(10);
}

void Calibrate()
{
    unsigned int count1;
    count1 = 0;
    do
    {
        getAccelData(&(d.ad.ax));
        sstatex = sstatex + Sample_X; // Accumulate Samples
        count1++;
    } while (count1 != 0x0400); // 1024 times
    sstatex = sstatex >> 10;    // division between 1024
}

void movement_end_check()
{
    if (accelerationx[1] == 0) //we count the number of acceleration samples that equals cero
    {
        countx++;
    }
    else
    {
        countx = 0;
    }
}
