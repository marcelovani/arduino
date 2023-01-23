class Target: public Runnable {
    const byte brakeSensePin;
    Laser &laser;
    RgbLed &rgb;
    Servos &servo;

  public:
    Target(byte attachToBrakeSense, Laser &laserInstance, RgbLed &rgbInstance, Servos &servoInstance) :
      servo(servoInstance),
      // @todo replace this with IR receiver
      brakeSensePin(attachToBrakeSense),
      laser(laserInstance),
      rgb(rgbInstance) {
    }

    byte getPin() {
      return brakeSensePin;
    }

    void setup() {
      pinMode(brakeSensePin, INPUT_PULLUP);
      laser.off();
      rgb.yellow();
      rgb.blink();
    }

    void loop() {
      if (digitalRead(brakeSensePin) == LOW) {
        laser.blink();
        rgb.red();
        servo.drop();
      }
      else {
        // laser.off();
        // rgb.blue();
      }
      if (servo.isOn()) {
        rgb.green();
      }
    }
};
