#include <Servo.h>

class Servos: public Runnable {
    byte pin;
    Servo servo;

  private:
    byte position;

  public:
    Servos(byte pin) : pin(pin) {
    }

    void setup() {
      servo.attach(pin);
      // @todo make this configurable.
      set(160);
    }

    void loop() {
    }

    void set(byte position) {
      this->position = position;
      this->send();
    }

    void drop() {
      this->position = 90;
      this->send();
    }

    void send() {
      servo.write(this->position);
    }
};
