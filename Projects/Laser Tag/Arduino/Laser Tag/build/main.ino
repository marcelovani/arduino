
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

#include <Servo.h>

class Servos: public Runnable {
    byte pin;
    Servo servo;

  public:
    Servos(byte pin) : pin(pin) {
    }

    void setup() {
      servo.attach(pin);
      set();
    }

    void loop() {
    }

    void set() {
        servo.write(90);
    }

    void drop() {
        servo.write(180);
    }
};

class Target: public Runnable {
    const byte brakeSensePin;
    Laser &laser;
    RgbLed &rgb;
    Servos &servo;

  public:
    Target(byte attachToBrakeSense, Laser &laserInstance, RgbLed &rgbInstance, Servos &servoInstance) :
      brakeSensePin(attachToBrakeSense),
      laser(laserInstance),
      rgb(rgbInstance),
      servo(servoInstance) {
    }

    byte getPin() {
      return brakeSensePin;
    }

    void setup() {
      pinMode(brakeSensePin, INPUT_PULLUP);
    }

    void loop() {
      if (digitalRead(brakeSensePin) == LOW) {
        Serial.println("Target: " + String(brakeSensePin));
        laser.on();
        rgb.green();
        servo.drop();
      }
      else {
        laser.off();
        rgb.blue();
      }
    }
};

#if defined(__ARDUINO_AVR_UNO__) || defined(ARDUINO_AVR_UNO)

    Laser laser1(13);
    RgbLed rgb1(12, 10, 11);
    Servos servo1(9);
    Target target1(8, laser1, rgb1, servo1);

    Laser laser2(6);
    RgbLed rgb2(5, 3, 4);
    Servos servo2(2);
    Target target2(7, laser2, rgb2, servo2);

#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

    Laser laser1(6);
    RgbLed rgb1(4, 3, 2);
    Servos servo1(7);
    Target target1(5, laser1, rgb1, servo1);

    Laser laser2(12);
    RgbLed rgb2(10, 9, 8);
    Servos servo2(13);
    Target target2(11, laser2, rgb2, servo2);

#endif


Runnable *Runnable::headRunnable;


void setup() {
  Serial.begin(9600);
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();
}
