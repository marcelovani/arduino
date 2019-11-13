// Potentiometer example
#include "Arduino.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include "Pot.h"
//#include "PotGraph.h"

Pot volPot(PotGraphTypeChartH, A0, 1000, "Volume"); // Create an instance of Pot on pin 14 and max of 1000
Pot bassPot(PotGraphTypeDial, A1, 100, "Bass"); // Create an instance of Pot on pin 15 and max of 100
Pot rangePot(PotGraphTypeDial, A2, 5, "Range"); // Create an instance of Pot on pin 16 and max of 10

//Adafruit_SSD1306 display;

void setup()
{
    Serial.begin(9600);
    delay(1000);
    Serial.println("Pot example");

    // Create an instance of LCD display
    //Adafruit_SSD1306 display(LCD_WIDTH, LCD_HEIGHT, &Wire, LCD_RST_PIN);

    // initialize the display
    // note you may have to change the address
    // the most common are 0X3C and 0X3D
//    display.begin(SSD1306_SWITCHCAPVCC, LCD_ADDR);
//    display.display();
//  delay(20);
//  display.clearDisplay();
//  display.display();

    //potGraph.begin();
    // Instantiate graphs
    //PotGraph dialGraph(display, LCD_ADDR, PotGraphTypeDial);
    //PotGraph dialGraph(PotGraphTypeDial);
    //PotGraph barGraph(display, LCD_ADDR, PotGraphTypeChartH);
    //PotGraph barGraph(PotGraphTypeChartH);
//
    // Create pots
    //Pot volPot(PotGraphTypeDial, A0, 1000, "Volume"); // Create an instance of Pot on pin 14 and max of 1000
    volPot.begin();
    bassPot.begin();
    rangePot.begin();

//    // Assign Graphs to pots
    //volPot.begin(barGraph);
    //bassPot.begin(dialGraph);

}

bool _redraw = true;
void loop()
{
    short int vol = getVolume();
    short int bass = getBass();
    short int range = getRange();

  if (!knobsMoving()) {
    // @todo use accel value
    //potGraph.drawCGraph(potGraph._display, potGraph._x++, 700, 30, 50, 75, 30, 0, 100, 25, 0, 1024, 512, 0, "Accelaration", _redraw);    
  }
//    Serial.print(vol);
//    Serial.print(",");
//    Serial.print(bass);
//  }
  Serial.println();
//    delay(1);
}

/*
 * Check if any knob is being moved
 */
bool knobsMoving()
{
//  return volPot.knobMoving() || bassPot.knobMoving() || rangePot.knobMoving();
}

/*
 * Return the volume
 */
short int getVolume()
{
  return volPot.read();
}

/*
 * Return the bass
 */
short int getBass()
{
  return bassPot.read();
}

/*
 * Return the range
 */
short int getRange()
{
  return rangePot.read();
}
