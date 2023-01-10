
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

class Headlamp: public Runnable {
    const byte powerOutPin;
    int brightness;

  public:
    boolean isOn;

    Headlamp(byte powerOutAttach) :
      powerOutPin(powerOutAttach)
    {
    }

    void setup() {
      pinMode(powerOutPin, OUTPUT);
      isOn = false;
      digitalWrite(powerOutPin, LOW);
      brightness = 0;
    }

    void loop() {
    }

    void powerToggle() {
      if (isOn) {
        digitalWrite(powerOutPin, LOW);
        isOn = false;
      }
      else {
        digitalWrite(powerOutPin, HIGH);
        delay(50);
        isOn = true;
      }
    }

    void brightnessClick() {
      if (isOn) {
        brightness = (brightness + 1 ) % 5;
      }
    }

} ;
class Button: public Runnable {
    const byte pin;
    int state;
    unsigned long buttonDownMs;

  protected:
    virtual void shortClick() = 0;
    virtual void longClick() = 0;

  public:
    Button(byte attachTo) :
      pin(attachTo)
    {
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
        if (millis() - buttonDownMs < 50) {
          // ignore this for debounce
        }
        else if (millis() - buttonDownMs < 250) {
          shortClick();
        }
        else  {
          longClick();
        }
      }
    }

};
class HeadlampControlButton: public Button {
    Headlamp &lamp;

  public:
    HeadlampControlButton(byte attachToPin, Headlamp &attachToHeadlamp) :
      Button(attachToPin),
      lamp(attachToHeadlamp) {
    }
  protected:
    void shortClick() {
      // short click
      lamp.brightnessClick();
    }

    void longClick() {
      // long click
      lamp.powerToggle();
    }
};

class Taillight: public Runnable {
    const byte brakeSensePin;
    const byte ledOutPin;
    Headlamp &headlamp;

  public:
    Taillight(byte attachToBrakeSense, Headlamp &attachToHeadlamp, byte attachToLedPin) :
      brakeSensePin(attachToBrakeSense),
      ledOutPin(attachToLedPin),
      headlamp(attachToHeadlamp) {
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
      else if (!headlamp.isOn) {
        digitalWrite(ledOutPin, LOW);
      }
      else {
        digitalWrite(ledOutPin, (millis() & 0b1110000000) == 0 ? HIGH : LOW);
      }
    }
};


Runnable *Runnable::headRunnable = NULL;

Headlamp headlamp(10);
HeadlampControlButton button(6, headlamp);
Taillight taillight(7, headlamp, 12);


void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();
}
