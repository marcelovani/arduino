// Potentiometer example
#include "Arduino.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Pot.h"
//#include "PotGraph.h"
#include "config.h"

//Adafruit_SSD1306 display(LCD_WIDTH, LCD_HEIGHT, &Wire, LCD_RST_PIN, 400000UL, 100000UL);
extern Adafruit_SSD1306 display(LCD_WIDTH, LCD_HEIGHT);

Pot thresholdPot(PotGraphTypeChartH, A1, 1000, "Thres: [600]"); // Create an instance of Pot on pin 14 and max of 1000
//Pot rangePot(PotGraphTypeDial, A0, 10, "Range [4]"); // Create an instance of Pot on pin 15 and max of 10
//Pot delayPot(PotGraphTypeDial, A2, 40, "Delay [20]"); // Create an instance of Pot on pin 16 and max of 40
//Pot samplesPot(PotGraphTypeDial, A3, 20, "Samples [10]"); // Create an instance of Pot on pin 17 and max of 20

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
//Adafruit_SSD1306 _display = &display;
//_display.begin(SSD1306_SWITCHCAPVCC, LCD_ADDR);
//_display.display();
//delay(2000);
//_display.clearDisplay();
//_display.display();
//_display.setTextSize(1);
//_display.setTextColor(SSD1306_WHITE);
//_display.setCursor(0,0);
//_display.print("Connecting to SSID\n'adafruit':");
//_display.display();

    //potGraph.begin();
    // Instantiate graphs
    //PotGraph dialGraph(display, LCD_ADDR, PotGraphTypeDial);
    //PotGraph dialGraph(PotGraphTypeDial);
    //PotGraph barGraph(display, LCD_ADDR, PotGraphTypeChartH);
    //PotGraph barGraph(PotGraphTypeChartH);
//
    // Create pots
    //Pot volPot(PotGraphTypeDial, A0, 1000, "Volume"); // Create an instance of Pot on pin 14 and max of 1000
    thresholdPot.begin(display);
    //rangePot.begin();
    //delayPot.begin();
    //samplesPot.begin(display);

//    // Assign Graphs to pots
    //volPot.begin(barGraph);
    //bassPot.begin(dialGraph);
Serial.println("Pot example done");
}

bool _redraw = true;
void loop()
{
    short int threshold = getThreshold();
    short int range = getRange();
    short int delay = getDelay();
    short int samples = getSamples();

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
//  return thresholdPot.knobMoving() || rangePot.knobMoving() || delayPot.knobMoving() || samplesPot.knobMoving();
}

/*
 * Return the Threshold
 */
short int getThreshold()
{
  return thresholdPot.read();
}

/*
 * Return the Range
 */
short int getRange()
{
//  return rangePot.read();
}

/*
 * Return the Delay
 */
short int getDelay()
{
//  return delayPot.read();
}

/*
 * Return the Samples
 */
short int getSamples()
{
//  return samplesPot.read();
}
