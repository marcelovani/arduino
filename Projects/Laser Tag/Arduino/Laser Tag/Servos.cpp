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
        servo.write(90);
    }

    void drop() {
        servo.write(180);
    }
};
