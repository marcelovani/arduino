/*
 Fade

 This example shows how to fade the Red LED on pin 12 
 using the analogWrite() function.

 */

// Include the Denbit library.
#include <Denbit.h>
// Initialize the denbit.
Denbit denbit;

int led = 12;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

/**
 * The setup function runs once when you press reset or power the board
 */
void setup() {
  // Start the Over The Air programming.
  denbit.OTAsetup();
  
  // declare LED pin to be an output:
  pinMode(led, OUTPUT);
}

/**
 * The loop function runs over and over again forever
 */
void loop() {
  // Check for any Over The Air updates.
  denbit.OTAhandle();
  
  // set the brightness of the LED:
  analogWrite(15, brightness - 20);
  analogWrite(14, brightness);
  analogWrite(10, brightness + 20);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount + 10;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness >= 230) {
    fadeAmount = -fadeAmount ;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(5);
}

