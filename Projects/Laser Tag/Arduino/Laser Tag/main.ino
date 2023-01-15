#include "Runnable.cpp"
#include "Led.cpp"
#include "Laser.cpp"
#include "RgbLed.cpp"
#include "Button.cpp"
#include "LedControlButton.cpp"
#include "Servos.cpp"
#include "Target.cpp"

Runnable *Runnable::headRunnable;

#include "Setup.cpp"

void setup() {
  Serial.begin(9600);
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();
}
