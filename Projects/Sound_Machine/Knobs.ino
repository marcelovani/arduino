#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//@todo move these to lcd class
#define READ_PIN            A0
#define OLED_RESET          -1 // -1 or A4

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

int knobMoveStart = 0; // Detect movement of knobs to pause waveform and show dial.
int knobPrevVal0 = 0;
int knobPrevVal1 = 0;
int timer; // Used to add a delay after the know stops being moved.
bool Redraw1 = true;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void KnobsSetup(void) {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
}

// Used to detect when the knob is being moved.
bool knobMoving() {
  return knobMoveStart != 0;
}

// The minimum value to be considered a good acceleration
const int thresholdMax = 800; // Default 600
const int thresholdPin = A1;
float getThreshold()
{
  int t = millis();  
  int value = map(analogRead(thresholdPin), 0, 1023, thresholdMax, 0);
    
  if (knobPrevVal0 != value) {
    int diff = knobPrevVal0 - value;
    if (diff < -5 || diff > 5) { // Eliminate noise
      knobPrevVal0 = value;
      knobMoveStart = t;
      timer = t + 500; // Set timer
    }
  }
  if (knobMoveStart != 0 && timer < t) {
    knobMoveStart = 0;
  }
  if (knobMoving()) {
    //DrawDial(display, value / 204.6, 65, 50, 25, 0, 5 , 1, 0, 200, "Threshold", Redraw1);
  }

  Serial.print(value);
  Serial.print(",");

  return value;
}


// Number of samples to collect
short int getSamples() {
    // @todo: Read from knob
    short int s = 10;
//    Serial.print(s);
//    Serial.print(",");

//    Lcd::setCursor(2, 1); 
//    Lcd::printM("Samples");
//    Lcd::printV(s);

    return s;
}

// The range used to calculate SMA
const int rangeMax = 10; // Default 4
const int rangePin = A0;
short int getRange() {
  int t = millis();
  int value = map(analogRead(rangePin), 0, 1023, rangeMax, 0);
    
  if (knobPrevVal1 != value) {
    int diff = knobPrevVal1 - value;
    if (diff < -5 || diff > 5) { // Eliminate noise
      knobPrevVal1 = value;
      knobMoveStart = t;
      timer = t + 500; // Set timer
    }
  }
  if (knobMoveStart != 0 && timer < t) {
    knobMoveStart = 0;
  }
  if (knobMoving()) {
    //DrawDial(display, value / 204.6, 65, 50, 25, 0, 5 , 1, 0, 200, "Threshold", Redraw1);
  }

  Serial.print(value);
  Serial.print(",");

  return value;
}

// The delay between acceleration readings. Useful to get a smoother line
short int getDelay() {
    // @todo: Read from knob
    short int d = 20;
//    Serial.print(d);
//    Serial.print(",");

//    Lcd::setCursor(2, 1); 
//    Lcd::printM("Delay");
//    Lcd::printV(d);

    return d;
}
