#include <Servo.h>

class Servos: public Runnable {
    byte pin;
    Servo servo;

  public:
    Servos(byte pin) : pin(pin) {
    }

    void setup() {
      servo.attach(pin);
      set();
    }

    void loop() {
    }

    void set() {
        servo.write(160);
    }

    void drop() {
        servo.write(90);
    }
};
