
class Runnable {
    static Runnable *headRunnable;
    Runnable *nextRunnable;

  public:
    Runnable() {
      nextRunnable = headRunnable;
      headRunnable = this;
    }

    virtual void setup() = 0;
    virtual void loop() = 0;

    static void setupAll() {
      for (Runnable *r = headRunnable; r; r = r->nextRunnable)
        r->setup();
    }

    static void loopAll() {
      for (Runnable *r = headRunnable; r; r = r->nextRunnable)
        r->loop();
    }

};

class Led: public Runnable {
  const byte pin;

  public:
    byte status;

    Led(byte pin) : pin(pin) {
    }

    void setup() {
      status = LOW;
      pinMode(pin, OUTPUT);
      send();
    }

    void loop() {
    }

    void send() {
      digitalWrite(pin, status);
    }

    void powerToggle() {
      if (status) {
        status = LOW;
      }
      else {
        status = HIGH;
      }
      send();
    }

    byte getPin() {
      return pin;
    }

    void on() {
      if (!status) {
        status = HIGH;
        send();
      }
    }

    void off() {
      if (status) {
        status = LOW;
        send();
      }
    }
};
class Button: public Runnable {
    const byte pin;
    byte state;
    unsigned long buttonDownMs;

  protected:
    virtual void click() = 0;

  public:
    Button(byte attachTo) : pin(attachTo) {
    }

    void setup() {
      pinMode(pin, INPUT_PULLUP);
      state = HIGH;
    }

    void loop() {
      int prevState = state;
      state = digitalRead(pin);
      if (prevState == HIGH && state == LOW) {
        buttonDownMs = millis();
      }
      else if (prevState == LOW && state == HIGH) {
        if (millis() - buttonDownMs < 100) {
          // debounce
        }
        else  {
          click();
        }
      }
    }
};
class LedControlButton: public Button {
    Led &led;

  public:
    LedControlButton(byte attachToPin, Led &attachToLed) :
      Button(attachToPin),
      led(attachToLed) {
    }
  protected:
    void click() {
      led.powerToggle();
    }
};

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
      led = new led(11);
    }

    void loop() {
      if (digitalRead(brakeSensePin) == LOW) {
        led.on();
      }
      else if (!led.status) {
        led.off();
      }
      else {
        led.off();
      }
    }
};


Runnable *Runnable::headRunnable;

Led led1(12);
// LedControlButton button1(7, led1);
Taillight taillight1(7, led1);

Led led2(11);
//LedControlButton button2(6, led2);
Taillight taillight2(6, led2);

void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();
}
