
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
      digitalWrite(pin, status);
    }

    void loop() {
    }

    void powerToggle() {
      if (status) {
        status = LOW;
      }
      else {
        status = HIGH;
      }
      digitalWrite(pin, status);
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
    Led &lamp;

  public:
    LedControlButton(byte attachToPin, Led &attachToLed) :
      Button(attachToPin),
      lamp(attachToLed) {
    }
  protected:
    void click() {
      lamp.powerToggle();
    }
};

class Taillight: public Runnable {
    const byte brakeSensePin;
    const byte ledOutPin;
    Led &headlamp;

  public:
    Taillight(byte attachToBrakeSense, Led &attachToLed, byte attachToLedPin) :
      brakeSensePin(attachToBrakeSense),
      ledOutPin(attachToLedPin),
      headlamp(attachToLed) {
    }

    void setup() {
      pinMode(brakeSensePin, INPUT_PULLUP);
      pinMode(ledOutPin, OUTPUT);
      digitalWrite(ledOutPin, LOW);
    }

    void loop() {
      if (digitalRead(brakeSensePin) == LOW) {
        digitalWrite(ledOutPin, HIGH);
      }
      else if (!headlamp.status) {
        digitalWrite(ledOutPin, LOW);
      }
      else {
        digitalWrite(ledOutPin, (millis() & 0b1110000000) == 0 ? HIGH : LOW);
      }
    }
};


Runnable *Runnable::headRunnable;

Led headlamp(10);
LedControlButton button(6, headlamp);
Taillight taillight(7, headlamp, 12);

void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();
}
