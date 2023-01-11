class Taillight: public Runnable {
    const byte brakeSensePin;
    const byte ledPin;
    Led &led;

  public:
    Taillight(byte attachToBrakeSense, Led &attachToLed, byte attachToLedPin) :
      brakeSensePin(attachToBrakeSense),
      led(attachToLed),
      ledPin(attachToLedPin) {
    }

    void setup() {
      pinMode(brakeSensePin, INPUT_PULLUP);
      // @todo try to use led.status instead of writing to the output diretly
      pinMode(ledPin, OUTPUT);
      digitalWrite(ledPin, LOW);
    }

    void loop() {
      if (digitalRead(brakeSensePin) == LOW) {
        digitalWrite(ledPin, HIGH);
      }
      else if (!led.status) {
        digitalWrite(ledPin, LOW);
      }
      else {
        digitalWrite(ledPin, (millis() & 0b1110000000) == 0 ? HIGH : LOW);
      }
    }
};
