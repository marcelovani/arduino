//https://github.com/Javierix/Ardutest/blob/0db1e79e10cc8b13ea0802dfd8ca68db7c5b330b/Arduino/ITG3200_ADXL345_test.ino

#include <Wire.h> // I2C library, gyroscope

#define TO_READ+2 8 // 2 bytes for each axis x, y, z and temp

// Gyroscope offsets are chip specific. 
int offx = 23;
int offy = -2;
int offz = -19;


#define DEVICE 0x68    // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
#define TO_READ 6      //num of bytes we are going to read each time (two bytes for each axis)
byte buff[TO_READ] ;     //6 bytes buffer for saving data read from the device
char str[512];           //string buffer to transform data before sending it to the serial port
int x, y, z;
long statex, statey, statez;
int regAddress = 0x3B;    // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]


void setup()
{
  Serial.begin(9600);
  Wire.begin();

  // Begins a transmission to the I2C slave (GY-521 board)
  writeTo(DEVICE, 0x6B, 0); 

  //We want to write to the ACCEL_CONFIG register
  writeTo(DEVICE, 0x1C, 0x10); 
  
  calibrate_Acc();
}


void loop()
{
  getAccData();
  delay(100);
}

void getAccData()
{ 
  readFrom(DEVICE, regAddress, TO_READ, buff); //read the acceleration data from the ADXL345
  //each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
  //thus we are converting both bytes in to one int
  x = ((((int)buff[1]) << 8) | buff[0]) - statex;  
  y = ((((int)buff[3]) << 8) | buff[2]) - statey;
  z = ((((int)buff[5]) << 8) | buff[4]);
  
  if ((x <= 3) && (x >= -3))  {x = 0;}        // Ventana de filtrado 
  if ((y <= 3) && (y >= -3))  {y = 0;}
  if ((z <= 3) && (z >= -3))  {z = 0;}  
 
  //we send the x y z values as a string to the serial port
  //sprintf(str, "x:%d y:%d z:%d", x, y, z); 
  sprintf(str, "%d,%d,%d,", x, y, z);
  Serial.write(str);
  Serial.write(10);
 }

/*******************************************************************************
The purpose of the calibration routine is to obtain the value of the reference threshold.
It consists on a 1024 samples average in no-movement condition.
********************************************************************************/
void calibrate_Acc(void){
  unsigned int count1;
  count1 = 0;
  do{
     readFrom(DEVICE, regAddress, TO_READ, buff); //read the acceleration data from the ADXL345
     x = (((int)buff[1]) << 8) | buff[0];  
     y = (((int)buff[3]) << 8) | buff[2];
     z = (((int)buff[5]) << 8) | buff[4];
     statex = statex + x;                        // Accumulate Samples
     statey = statey + y;
     statez = statez + z;
     count1++;
  }while(count1!=0x0FF);             // 256 times
  
  statex=statex>>8;                  // division between 256
  statey=statey>>8;
  statez=statez>>8;
}  


/***************************************************************************
  Writes val to address register on device
***************************************************************************/
void writeTo(int device, byte address, byte val) {
  Wire.beginTransmission(device); //start transmission to device
  Wire.write(address);        // send register address
  Wire.write(val);        // send value to write
  Wire.endTransmission(); //end  transmission
}

 
/*************************************************************************** 
  Reads num bytes starting from address register on device in to buff array
***************************************************************************/
void readFrom(int device, byte address, int num, byte buff[]) {
  Wire.beginTransmission(device); //start transmission to device
  Wire.write(address);        //sends address to read from
  Wire.endTransmission(false);    //end transmission
  //Wire.beginTransmission(device); //start transmission to device
  Wire.requestFrom(device, num, true);    // request 6 bytes from device
 
  int i = 0;
  while(Wire.available())    //device may send less than requested (abnormal)
  {
    buff[i] = Wire.read(); // receive a byte
    i++;
  }
  //Wire.endTransmission(); //end transmission
}
