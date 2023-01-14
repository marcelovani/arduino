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
