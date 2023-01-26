class Target: public Runnable {
    const byte brakeSensePin;
    Laser &laser;
    RgbLed &rgb;
    Servos &servo;
    Infra &infra;
    byte targetId;

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
    }

    void loop() {
      byte gun;
      gun = infra.getShot();
      if (digitalRead(brakeSensePin) == LOW || gun) {
        Serial.print("Target ");
        Serial.print(this->targetId);
        Serial.print(" Gun ");
        Serial.println(gun);
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
