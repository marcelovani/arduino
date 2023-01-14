class Taillight: public Runnable {
    const byte brakeSensePin;
    Led &led;

  public:
    Taillight(byte attachToBrakeSense, Led &attachToLed) :
      brakeSensePin(attachToBrakeSense),
      led(attachToLed) {
    }

    void setup() {
      pinMode(brakeSensePin, INPUT_PULLUP);
      //led = new led(11);
    }

    void loop() {
      if (digitalRead(brakeSensePin) == LOW) {
        led.on();
      }
      else {
        led.off();
      }
    }
};
