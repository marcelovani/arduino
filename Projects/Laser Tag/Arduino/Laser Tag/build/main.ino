
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
class Laser: public Runnable {
    byte pin;
    Led led;

  public:
    Laser(byte pin) :
      led(pin) {
    }

    void setup() {
    }

    void loop() {
    }

    void on() {
        led.on();
    }

    void off() {
        led.off();
    }
};

class RgbLed: public Runnable {
    byte rPin;
    byte gPin;
    byte bPin;
    Led rLed;
    Led gLed;
    Led bLed;

  public:
    RgbLed(byte rPin, byte gPin, byte bPin) :
      rLed(rPin),
      gLed(gPin),
      bLed(bPin)
      {
    }

    void setup() {
    }

    void loop() {
    }

    void red() {
        rLed.on();
        gLed.off();
        bLed.off();
    }

    void green() {
        rLed.off();
        gLed.on();
        bLed.off();
    }
    
    void blue() {
        rLed.off();
        gLed.off();
        bLed.on();
    }

    void off() {
        gLed.off();
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

class Target: public Runnable {
    const byte brakeSensePin;
    Laser &laser;
    RgbLed &rgb;

  public:
    Target(byte attachToBrakeSense, Laser &laserInstance, RgbLed &rgbInstance) :
      brakeSensePin(attachToBrakeSense),
      laser(laserInstance),
      rgb(rgbInstance) {
    }

    void setup() {
      pinMode(brakeSensePin, INPUT_PULLUP);
    }

    void loop() {
      if (digitalRead(brakeSensePin) == LOW) {
        laser.on();
        rgb.green();
      }
      else {
        laser.off();
        rgb.blue();
      }
    }
};


Runnable *Runnable::headRunnable;

Laser laser1(13);
RgbLed rgb1(12, 10, 11);
// LedControlButton button1(7, laser1);
Target target1(8, laser1, rgb1);

// Led laser2(6);
Laser laser2(6);
RgbLed rgb2(5, 3, 4);
// LedControlButton button2(6, laser2);
Target target2(7, laser2, rgb2);

void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();
}
