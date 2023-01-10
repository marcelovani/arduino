class Headlamp: public Runnable {
    const byte powerOutPin;
    ClickQueue brightnessClicker;
    int brightness;

  public:
    boolean isOn;

    Headlamp(byte powerOutAttach, byte brightnessOutAttach) :
      powerOutPin(powerOutAttach),
      brightnessClicker(brightnessOutAttach)
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
        brightnessClicker.cancel();
        digitalWrite(powerOutPin, LOW);
        isOn = false;
      }
      else {
        digitalWrite(powerOutPin, HIGH);
        delay(50);
        brightnessClicker.addClicks(brightness);
        isOn = true;
      }
    }

    void brightnessClick() {
      if (isOn) {
        brightnessClicker.addAClick();
        brightness = (brightness + 1 ) % 5;
      }
    }

} ;