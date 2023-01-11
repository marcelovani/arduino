#include "Runnable.cpp"
#include "Led.cpp"
#include "Button.cpp"
#include "LedControlButton.cpp"
#include "Taillight.cpp"

Runnable *Runnable::headRunnable;

Led led(10);
LedControlButton button(6, led);
Taillight taillight(7, led, 12);

void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();
}
