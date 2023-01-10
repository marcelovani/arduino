#include "PotGraph.h"
#include "config.h"

Adafruit_SSD1306 screen(LCD_WIDTH, LCD_HEIGHT, &Wire, LCD_RST_PIN);
//PotGraph samplesPot(PotGraphTypeDial, A0, 20, "Samples        [10]"); // Create an instance of Pot on pin 14 and max of 20 default 10
PotGraph rangePot  (PotGraphTypeDial, A1, 10, "Range           [4]"); // Create an instance of Pot on pin 15 and max of 10 default 4

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("PotGraph example");

  screen.begin(SSD1306_SWITCHCAPVCC, LCD_ADDR);

//  samplesPot.attach(screen);
  rangePot.attach(screen);
}

void loop() {
  //samplesPot.read();
  rangePot.read();

  if (knobsMoving()) {
    //samplesPot.draw(screen);
    rangePot.draw(screen);
  } else {
    // Display x/y
  }
}

/*
 * Check if any knob is being moved
 */
bool knobsMoving()
{
  return rangePot.knobMoving();
//  return samplesPot.knobMoving();// || rangePot.knobMoving(); //thresholdPot.knobMoving() || delayPot.knobMoving()
}
