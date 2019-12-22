#include "Arduino.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "xyGraph.h"
#include "PotGraph.h"
#include "Pot.h"
#include "config.h"

int ClearScreen = false;

Adafruit_SSD1306 screen(LCD_WIDTH, LCD_HEIGHT, &Wire, LCD_RST_PIN);

xyGraph graph;
PotGraph potGraph;

Pot samplesPot  (PotGraphTypeDial,   A0, 20,   "Samples     ideal:10"); // Create an instance of Pot on pin 14 and max of 20 ideal 10
Pot rangePot    (PotGraphTypeDial,   A1, 10,   "Range        ideal:4"); // Create an instance of Pot on pin 15 and max of 10 ideal 4
//@todo this library is too heavy to be instantiated 4 times
// need to split pot and PotGraph, instantiate potGraph only once
//Pot delayPot    (PotGraphTypeDial,   A2, 10,   "Delay       ideal:20"); // Create an instance of Pot on pin 16 and max of 40 ideal 20
//Pot thresholdPot(PotGraphTypeChartH, A3, 1000, "Threshold  ideal:600"); // Create an instance of Pot on pin 17 and max of 1K ideal 600

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("PotGraph example");

  screen.begin(SSD1306_SWITCHCAPVCC, LCD_ADDR);
  screen.display();
  delay(2000);
  screen.clearDisplay();
  screen.display();
  splash(screen);
  delay(2000);
  screen.clearDisplay();
  screen.display();
  Serial.println("Screen attached");

//  samplesPot.attach(screen);
//  rangePot.attach(screen);
//  delayPot.attach(screen);
//  thresholdPot.attach(screen);
}

void loop() {
  Serial.print(freeMemory());
  Serial.print("\t");

  samplesPot.read();
  rangePot.read();
//  delayPot.read();
//  thresholdPot.read();

  if (samplesPot.knobMoving()) {
    potGraph.draw(screen, samplesPot);
    Serial.print(samplesPot.getValue());
    Serial.print("\t");
  } else if (rangePot.knobMoving()) {
    potGraph.draw(screen, rangePot);
    Serial.print(rangePot.getValue());
    Serial.print("\t");
//  } else if (thresholdPot.knobMoving()) {
//    potGraph.draw(screen, thresholdPot);
//  } else if (delayPot.knobMoving()) {
//    potGraph.draw(screen, delayPot);
  } else {
    // Display x/y
    //delay(1000);
//    screen.clearDisplay();
//    screen.display();
    //graph.draw(screen, samplesPot.getValue()); //@todo use accelerometer value
  }
  
  Serial.println(" ");
}

/*
 * Check if any knob is being moved
 */
bool knobsMoving()
{
  return samplesPot.knobMoving() || rangePot.knobMoving();// || thresholdPot.knobMoving() || delayPot.knobMoving();
}

/*
   Splash screen
*/
void splash(Adafruit_SSD1306 &screen) {
  screen.setTextSize(1);
  screen.setTextColor(SSD1306_WHITE);
  screen.setCursor(0, 0);
  screen.print("PotGraph v1.0\nCopyright (c) 2019\nBy MarlovaSoft Tm");
  screen.display();
}
