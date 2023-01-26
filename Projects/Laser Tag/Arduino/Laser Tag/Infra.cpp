#include <IRremote.h>

// Infra Red Receiver.
class Infra: public Runnable {
    byte pin;
    IRrecv receiver;

  private:
    void translateIR()
    {
      // Takes command based on IR code received
      // switch (receiver.decodedIRData.command) {
      //   case 162:
      //     break;
      //   case 226:
      //     break;

      //   default:
      //     Serial.println(receiver.decodedIRData.command);
      // }
    }

  public:
    Infra(byte pin) :
      receiver(pin) {
    }

    void setup() {
      // receiver.enableIRIn();
    }

    void loop()
    {
      // Checks received an IR signal
      // if (receiver.decode()) {
      //   this->translateIR();
      //   // Receive the next value
      //   receiver.resume();
      // }
    }
};
