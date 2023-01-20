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

    void blink() {
        gLed.blink(100, 500, 5);
    }
};
