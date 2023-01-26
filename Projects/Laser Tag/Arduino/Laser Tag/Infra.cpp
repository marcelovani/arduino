#include <IRremote.h>

// Infra Red Receiver.
class Infra: public Runnable {
    byte pin;
    IRrecv receiver;

  private:
    byte translateIR()
    {
      // Takes command based on IR code received
      switch (receiver.decodedIRData.command) {
        case 48:
          // Gun 1
          return 1;
          break;

        case 24:
          // Gun 2
          return 2;
          break;

        default:
          Serial.println(receiver.decodedIRData.command);
      }
    }

  public:
    Infra(byte pin) :
      receiver(pin) {
    }

    void setup() {
      receiver.enableIRIn();
    }

    byte getShot() {
      byte gun;
      // Checks received an IR signal
      if (receiver.decode()) {
        gun = this->translateIR();
        // Receive the next value
        receiver.resume();
        return gun;
      }
      return 0;
    }

    void loop() {
    }
};
