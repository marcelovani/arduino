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
      byte gun;

      if (servo.isOn()) {
        rgb.green();
        this->isReady = 1;
      }
      else {
        this->isReady = 0;
      }

      // Check for shots.
      gun = infra.getShot();
      if (digitalRead(brakeSensePin) == LOW || gun) {
        if (this->isReady) {
          Serial.println("Gun " + String(gun) + " hit target " + String(this->targetId));
          laser.blink();
          rgb.red();
          servo.drop();
        }
        else {
          Serial.println("Target " + String(this->targetId) + " is not ready");
        }
      }
    }
};
