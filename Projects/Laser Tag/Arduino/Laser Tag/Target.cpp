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
      laser.off();
      rgb.blink();
    }

    void loop() {
      if (digitalRead(brakeSensePin) == LOW) {
        Serial.println("Target: " + String(brakeSensePin));
        laser.blink();
        rgb.red();
        servo.drop();
      }
      else {
        // laser.off();
        // rgb.blue();
      }
    }
};
