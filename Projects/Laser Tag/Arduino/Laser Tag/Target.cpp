class Target: public Runnable {
    const byte brakeSensePin;
    Laser &laser;
    RgbLed &rgb;
    Servos &servo;
    Infra &infra;
    byte targetId;
    byte isReady;

  public:
    Target(
        byte id,
        byte attachToBrakeSense,
        Laser &laserInstance,
        RgbLed &rgbInstance,
        Servos &servoInstance,
        Infra &infraInstance
      ) :
        targetId(id),
        servo(servoInstance),
        brakeSensePin(attachToBrakeSense),
        laser(laserInstance),
        rgb(rgbInstance),
        infra(infraInstance) {
    }

    byte getPin() {
      return brakeSensePin;
    }

    void setup() {
      pinMode(brakeSensePin, INPUT_PULLUP);
      laser.off();
      rgb.yellow();
      rgb.blink();
      this->isReady = 0;
    }

    void loop() {
      byte gunShot;

      if (servo.isOn()) {
        rgb.green();
        this->isReady = 1;
      }
      else {
        rgb.red();
        this->isReady = 0;
      }

      // Check for shots.
      if (this->isReady) {
        gunShot = infra.getShot();
        if (gunShot || digitalRead(brakeSensePin) == LOW) {
          Serial.print("Gun " + String(gunShot) + " shot target " + String(this->targetId) + " - ");
            Serial.println("Hit");
            laser.blink();
            rgb.red();
            servo.drop();
        }
      }
    }
};
