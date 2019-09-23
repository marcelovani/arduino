// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include "Wire.h" // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x[2], accelerometer_y[2], accelerometer_z[2]; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data

char tmp_str[7]; // temporary variable used in convert function

float countx, county;
long sstatex, sstatey;
float Sample_X, Sample_Y, Sample_Z;
long velocityx[2], velocityy[2];
long positionX[2], positionY[2], positionZ[2];
char direction;

float prev_acc_x = 1000;
int mov = 0;
int LED = 13;

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Calibrate();
  Serial.println(accelerometer_x[1]);
}
void loop() {
    unsigned char count2;
    count2 = 0;

    do
    {

        ADC_GetAllAxis();

        accelerometer_x[1] = accelerometer_x[1] + Sample_X; //filtering routine for noise attenuation
        accelerometer_y[1] = accelerometer_y[1] + Sample_Y; //64 samples are averaged. The resulting
                                                        //average represents the acceleration of
        //an instant
        count2++;

    } while (count2 != 0x40); // 64 sums of the acceleration sample

accelerometer_x[1] = accelerometer_x[1] >> 6; // division by 64
    accelerometer_y[1] = accelerometer_y[1] >> 6;

    accelerometer_x[1] = accelerometer_x[1] - (int)sstatex; //eliminating zero reference
    //offset of the acceleration data
    accelerometer_y[1] = accelerometer_y[1] - (int)sstatey; // to obtain positive and negative
    //acceleration

    if ((accelerometer_x[1] <= 3) && (accelerometer_x[1] >= -3)) //Discrimination window applied
    {
        accelerometer_x[1] = 0;
    } // to the X axis acceleration
    //variable

    if ((accelerometer_y[1] <= 3) && (accelerometer_y[1] >= -3))
    {
        accelerometer_y[1] = 0;
    }

    //first X integration:
    velocityx[1] = velocityx[0] + accelerometer_x[0] + ((accelerometer_x[1] - accelerometer_x[0]) >> 1);
    //second X integration:
    positionX[1] = positionX[0] + velocityx[0] + ((velocityx[1] - velocityx[0]) >> 1);
    //first Y integration:
    velocityy[1] = velocityy[0] + accelerometer_y[0] + ((accelerometer_y[1] - accelerometer_y[0]) >> 1);
    //second Y integration:
    positionY[1] = positionY[0] + velocityy[0] + ((velocityy[1] - velocityy[0]) >> 1);

    accelerometer_x[0] = accelerometer_x[1]; //The current acceleration value must be sent
                                         //to the previous acceleration
    accelerometer_y[0] = accelerometer_y[1]; //variable in order to introduce the new
                                         //acceleration value.

    velocityx[0] = velocityx[1]; //Same done for the velocity variable
    velocityy[0] = velocityy[1];

    positionX[1] = positionX[1] << 18; //The idea behind this shifting (multiplication)
    //is a sensibility adjustment.
    positionY[1] = positionY[1] << 18; //Some applications require adjustments to a
    //particular situation
    //i.e. mouse application
    //data_transfer();

    Serial.print(velocityx[1]);
    Serial.print(",");
    Serial.print(positionX[1]);
    Serial.println();

    positionX[1] = positionX[1] >> 18; //once the variables are sent them must return to
    positionY[1] = positionY[1] >> 18; //their original state
    movement_end_check();

    positionX[0] = positionX[1]; //actual position data must be sent to the
    positionY[0] = positionY[1]; //previous position

    direction = 0; // data variable to direction variable reset

    delay(50);

  // If the actual acc is 2 times bigger than the previous one, we have movement
  //if (abs(accelerometer_x[1]) > abs(1.05 * prev_acc_x))
  //{
  //  digitalWrite(LED, HIGH);
  //  //Serial.println(Acc_rawX);
  //  mov = 100;
  //  delay(100);
  //  prev_acc_x = accelerometer_x[1];

  //    Serial.print(mov);
  //    Serial.print(",");
  //    Serial.print(accelerometer_x[1]);
  //    Serial.println();
  //}

  //else
  //{
  //  digitalWrite(LED, LOW);
  //  prev_acc_x = accelerometer_x[1];
  //  mov = 0;
  //  //DFPlayer.play(1);
 // }
}

void ADC_GetAllAxis() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x[1] = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y[1] = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z[1] = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
}

/*******************************************************************************
 The purpose of the calibration routine is to obtain the value of the reference threshold.
 It consists on a 1024 samples average in no-movement condition.
********************************************************************************/
void Calibrate(void)
{
    unsigned int count1;
    count1 = 0;
    do
    {
        ADC_GetAllAxis();
        sstatex = sstatex + Sample_X; // Accumulate Samples
        sstatey = sstatey + Sample_Y;
        count1++;
    } while (count1 != 0x0400); // 1024 times
    sstatex = sstatex >> 10;    // division between 1024
    sstatey = sstatey >> 10;
}

/******************************************************************************************
This function allows movement end detection. If a certain number of acceleration samples are
equal to zero we can assume movement has stopped. Accumulated Error generated in the velocity
calculations is eliminated by resetting the velocity variables. This stops position increment
and greatly eliminates position error.
******************************************************************************************/
void movement_end_check(void)
{
    if (accelerometer_x[1] == 0) //we count the number of acceleration samples that equals cero
    {
        countx++;
    }
    else
    {
        countx = 0;
    }

    if (countx >= 25) //if this number exceeds 25, we can assume that velocity is cero
    {
        velocityx[1] = 0;
        velocityx[0] = 0;
    }

    if (accelerometer_y[1] == 0) //we do the same for the Y axis
    {
        county++;
    }
    else
    {
        county = 0;
    }

    if (county >= 25)
    {
        velocityy[1] = 0;
        velocityy[0] = 0;
    }
}
