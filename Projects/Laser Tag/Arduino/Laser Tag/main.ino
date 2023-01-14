#include "Runnable.cpp"
#include "Led.cpp"
#include "Laser.cpp"
#include "RgbLed.cpp"
#include "Button.cpp"
#include "LedControlButton.cpp"
#include "Target.cpp"

Runnable *Runnable::headRunnable;

Laser laser1(13);
RgbLed rgb1(12, 10, 11);
// LedControlButton button1(7, laser1);
Target target1(8, laser1, rgb1);

// Led laser2(6);
Laser laser2(6);
RgbLed rgb2(5, 3, 4);
// LedControlButton button2(6, laser2);
Target target2(7, laser2, rgb2);

void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();
}
