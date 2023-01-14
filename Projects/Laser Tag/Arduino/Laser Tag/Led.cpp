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