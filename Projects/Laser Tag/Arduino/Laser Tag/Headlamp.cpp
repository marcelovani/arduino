class Headlamp: public Runnable {
    const byte powerOutPin;
    int brightness;

  public:
    boolean isOn;

    Headlamp(byte powerOutAttach) :
      powerOutPin(powerOutAttach)
    {
    }

    void setup() {
      pinMode(powerOutPin, OUTPUT);
      isOn = false;
      digitalWrite(powerOutPin, LOW);
      brightness = 0;
    }

    void loop() {
    }

    void powerToggle() {
      if (isOn) {
        digitalWrite(powerOutPin, LOW);
        isOn = false;
      }
      else {
        digitalWrite(powerOutPin, HIGH);
        delay(50);
        isOn = true;
      }
    }

    void brightnessClick() {
      if (isOn) {
        brightness = (brightness + 1 ) % 5;
      }
    }

} ;