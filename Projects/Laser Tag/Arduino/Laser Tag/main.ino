#include "Runnable.cpp"
#include "Led.cpp"
#include "Button.cpp"
#include "LedControlButton.cpp"
#include "Taillight.cpp"

Runnable *Runnable::headRunnable;

Led led1(10);
LedControlButton button1(5, led1);

Led led2(11);
LedControlButton button2(6, led2);

Led led3(12);
Taillight taillight(7, led3, 12);

void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();
}
