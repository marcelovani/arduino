#include "Runnable.cpp"
#include "Led.cpp"
#include "Button.cpp"
#include "LedControlButton.cpp"
#include "Taillight.cpp"

Runnable *Runnable::headRunnable;

Led led1(12);
// LedControlButton button1(7, led1);
Taillight taillight1(7, led1);

Led led2(11);
LedControlButton button2(6, led2);
//Taillight taillight2(6, led2);

void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();
}
