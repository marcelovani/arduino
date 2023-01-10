class Taillight: public Runnable {
    const byte brakeSensePin;
    const byte ledOutPin;
    Headlamp &headlamp;

  public:
    Taillight(byte attachToBrakeSense, Headlamp &attachToHeadlamp, byte attachToLedPin) :
      brakeSensePin(attachToBrakeSense),
      ledOutPin(attachToLedPin),
      headlamp(attachToHeadlamp) {
    }

    void setup() {
      pinMode(brakeSensePin, INPUT_PULLUP);
      pinMode(ledOutPin, OUTPUT);
      digitalWrite(ledOutPin, LOW);
    }

    void loop() {
      if (digitalRead(brakeSensePin) == LOW) {
        digitalWrite(ledOutPin, HIGH);
      }
      else if (!headlamp.isOn) {
        digitalWrite(ledOutPin, LOW);
      }
      else {
        digitalWrite(ledOutPin, (millis() & 0b1110000000) == 0 ? HIGH : LOW);
      }
    }
};
