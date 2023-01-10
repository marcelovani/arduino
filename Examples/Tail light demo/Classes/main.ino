#include "Runnable.cpp"
#include "ClickQueue.cpp"
#include "Headlamp.cpp"
#include "Button.cpp"
#include "HeadlampControlButton.cpp"
#include "Taillight.cpp"

Runnable *Runnable::headRunnable = NULL;

Headlamp headlamp(10, 11);
HeadlampControlButton button(6, headlamp);
Taillight taillight(7, headlamp, 12);


void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();
}
