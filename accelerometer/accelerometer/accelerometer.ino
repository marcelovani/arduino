/* http://www.youtube.com/c/electronoobs/eng_arduino_tut76.php * 
 * This is an example where we configure te data of the MPU6050
 * and read the Acceleration data and detect movement 
 * Arduino pin    |   MPU6050
 * 5V             |   Vcc
 * GND            |   GND
 * A4             |   SDA
 * A5             |   SCL
 */
#include <Wire.h>
// DFPlayer
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial SoftSerial(10, 11); // RX, TX
DFRobotDFPlayerMini DFPlayer;

int LED = 13;

//Gyro Variables
float elapsedTime, time, timePrev;        //Variables for time control  
int gyro_error = 0;                       //We use this variable to only calculate once the gyro data error
float Gyr_rawX, Gyr_rawY, Gyr_rawZ;       //Here we store the raw data read
float Gyro_angle_x, Gyro_angle_y;         //Here we store the angle value obtained with Gyro data
float Gyro_raw_error_x, Gyro_raw_error_y; //Here we store the initial gyro data error

//Acc Variables
int acc_error = 0;                          //We use this variable to only calculate once the Acc data error
float rad_to_deg = 180 / 3.141592654;       //This value is for pasing from radians to degrees values
float Acc_rawX, Acc_rawY, Acc_rawZ;         //Here we store the raw data read
float Acc_angle_x, Acc_angle_y;             //Here we store the angle value obtained with Acc data
float Acc_angle_error_x, Acc_angle_error_y; //Here we store the initial Acc data error
float Total_angle_x, Total_angle_y;
float prev_acc = 1000;
int mov = 0;
int perc = 0;

void setup()
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Wire.begin();                 //begin the wire comunication
  Wire.beginTransmission(0x68); //begin, Send the slave adress (in this case 68)
  Wire.write(0x6B);             //make the reset (place a 0 into the 6B register)
  Wire.write(0x00);
  Wire.endTransmission(true); //end the transmission
  //Gyro config
  Wire.beginTransmission(0x68); //begin, Send the slave adress (in this case 68)
  Wire.write(0x1B);             //We want to write to the GYRO_CONFIG register (1B hex)
  Wire.write(0x10);             //Set the register bits as 00010000 (1000dps full scale)
  Wire.endTransmission(true);   //End the transmission with the gyro
  //Acc config
  Wire.beginTransmission(0x68); //Start communication with the address found during search.
  Wire.write(0x1C);             //We want to write to the ACCEL_CONFIG register
  Wire.write(0x10);             //Set the register bits as 00010000 (+/- 8g full scale range)
  Wire.endTransmission(true);

  Serial.begin(9600); //Remember to set this same baud rate to the serial monitor
  time = millis();    //Start counting time in milliseconds

  /*Here we calculate the acc data error before we start the loop
 * I make the mean of 20 values, that should be enough*/
  if (acc_error == 0)
  {
    for (int a = 0; a < 20; a++)
    {
      Wire.beginTransmission(0x68);
      Wire.write(0x3B); //Ask for the 0x3B register- correspond to AcX
      Wire.endTransmission(false);
      Wire.requestFrom(0x68, 6, true);

      Acc_rawX = (Wire.read() << 8 | Wire.read()) / 4096.0; //each value needs two registres
      Acc_rawY = (Wire.read() << 8 | Wire.read()) / 4096.0;
      Acc_rawZ = (Wire.read() << 8 | Wire.read()) / 4096.0;

      /*---X---*/
      Acc_angle_error_x = Acc_angle_error_x + ((atan((Acc_rawY) / sqrt(pow((Acc_rawX), 2) + pow((Acc_rawZ), 2))) * rad_to_deg));
      /*---Y---*/
      Acc_angle_error_y = Acc_angle_error_y + ((atan(-1 * (Acc_rawX) / sqrt(pow((Acc_rawY), 2) + pow((Acc_rawZ), 2))) * rad_to_deg));

      if (a == 199)
      {
        Acc_angle_error_x = Acc_angle_error_x / 20;
        Acc_angle_error_y = Acc_angle_error_y / 20;
        acc_error = 1;
      }
    }
  } //end of acc error calculation

  /*Here we calculate the gyro data error before we start the loop
 * I make the mean of 20 values, that should be enough*/
  if (gyro_error == 0)
  {
    for (int i = 0; i < 20; i++)
    {
      Wire.beginTransmission(0x68); //begin, Send the slave adress (in this case 68)
      Wire.write(0x43);             //First adress of the Gyro data
      Wire.endTransmission(false);
      Wire.requestFrom(0x68, 4, true); //We ask for just 4 registers

      Gyr_rawX = Wire.read() << 8 | Wire.read(); //Once again we shif and sum
      Gyr_rawY = Wire.read() << 8 | Wire.read();

      /*---X---*/
      Gyro_raw_error_x = Gyro_raw_error_x + (Gyr_rawX / 32.8);
      /*---Y---*/
      Gyro_raw_error_y = Gyro_raw_error_y + (Gyr_rawY / 32.8);
      if (i == 199)
      {
        Gyro_raw_error_x = Gyro_raw_error_x / 20;
        Gyro_raw_error_y = Gyro_raw_error_y / 20;
        gyro_error = 1;
      }
    }
  } //end of gyro error calculation

  // DFPlayer
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

  //DFPlayer.play(1); // Play the first mp3

} //end of setup void

void loop()
{
  //////////////////////////////////////Acc read/////////////////////////////////////

  Wire.beginTransmission(0x68);    //begin, Send the slave adress (in this case 68)
  Wire.write(0x3B);                //Ask for the 0x3B register- correspond to AcX
  Wire.endTransmission(false);     //keep the transmission and next
  Wire.requestFrom(0x68, 2, true); //We ask for next 6 registers starting withj the 3B
  /*We have asked for the 0x3B register. The IMU will send a brust of register.
  * The amount of register to read is specify in the requestFrom function.
  * In this case we request 6 registers. Each value of acceleration is made out of
  * two 8bits registers, low values and high values. For that we request the 6 of them  
  * and just make then sum of each pair. For that we shift to the left the high values 
  * register (<<) and make an or (|) operation to add the low values.
  If we read the datasheet, for a range of+-8g, we have to divide the raw values by 4096*/
  Acc_rawX = abs((Wire.read() << 8 | Wire.read())) / 2048.0; //each value needs two registres
  //Acc_rawY = (Wire.read() << 8 | Wire.read()) / 2048.0;
  //Acc_rawZ = (Wire.read() << 8 | Wire.read()) / 2048.0;

  //if the actual acc is 2 times bigger than the previous one, we
  //detect movement...

//Vf = Vi + a*t
  perc = abs(Acc_rawX * 100 / prev_acc);
  if (perc > 2) // check if the variation is 10% bigger
  {
    mov = 1;
    digitalWrite(LED, HIGH);
    Serial.print(mov);
    Serial.print(",");
    Serial.print(perc);
    Serial.print(",");
    Serial.print(Acc_rawX);
    Serial.println();
    delay(200);
    prev_acc = Acc_rawX;
  }
  else
  {
    mov = 0;
    digitalWrite(LED, LOW);
    prev_acc = Acc_rawX;
    //DFPlayer.play(1);
  }

  Serial.print(mov);
  Serial.print(",");
  Serial.print(perc);
  Serial.print(",");
  Serial.print(Acc_rawX);
  //Serial.print(",");
  //Serial.print(Acc_rawY);
  //Serial.print(",");
  //Serial.println(Acc_rawZ);
  Serial.println();

  delay(100);
}
