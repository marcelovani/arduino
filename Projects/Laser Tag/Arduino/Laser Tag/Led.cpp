class Led: public Runnable {
    const byte pin;

  public:
    byte status;

    Led(byte pin) : pin(pin) {
    }

    void setup() {
      status = LOW;
      pinMode(pin, OUTPUT);
      digitalWrite(pin, status);
    }

    void loop() {
    }

    void powerToggle() {
      if (status) {
        status = LOW;
      }
      else {
        status = HIGH;
      }
      digitalWrite(pin, status);
    }
};