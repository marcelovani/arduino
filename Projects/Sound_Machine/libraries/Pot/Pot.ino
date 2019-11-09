// Potentiometer example

#include <Wire.h>
#include <SoftwareSerial.h>
#include "Pot.h"

Pot volPot(A0, 1000, "Volume", PotLCDTypeChartH); // Create an instance of Pot on pin 14 and max of 1000
// Pot bassPot(A1, 100, "Bass", PotLCDTypeDial); // Create an instance of Pot on pin 15 and max of 100

void setup()
{
    Serial.begin(9600);
    delay(1000);
    Serial.println("Pot example");

    //Pot volPot(A0, 1000, "Volume", PotLCDTypeChartH); // Create an instance of Pot on pin 14 and max of 1000

    //Pot bassPot(A1, 100, "Bass", PotLCDTypeDial); // Create an instance of Pot on pin 15 and max of 100

}

void loop()
{
    short int vol = getVolume();
    short int bass = getBass();

    Serial.println(vol);
    delay(10);
}

/*
 * Check if any knob is being moved
 */
bool knobsMoving()
{
  //return volPot.knobMoving() || bassPot.knobMoving();
}

/*
 * Return the volume
 */
short int getVolume()
{
  Serial.println(volPot.read());
  return volPot.read();
}

/*
 * Return the bass
 */
short int getBass()
{
  //return bassPot.read();
}
