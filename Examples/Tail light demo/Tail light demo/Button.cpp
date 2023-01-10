class Button: public Runnable {
    const byte pin;
    int state;
    unsigned long buttonDownMs;

  protected:
    virtual void shortClick() = 0;
    virtual void longClick() = 0;

  public:
    Button(byte attachTo) :
      pin(attachTo)
    {
    }


    void setup() {
      pinMode(pin, INPUT_PULLUP);
      state = HIGH;
    }

    void loop() {
      int prevState = state;
      state = digitalRead(pin);
      if (prevState == HIGH && state == LOW) {
        buttonDownMs = millis();
      }
      else if (prevState == LOW && state == HIGH) {
        if (millis() - buttonDownMs < 50) {
          // ignore this for debounce
        }
        else if (millis() - buttonDownMs < 250) {
          shortClick();
        }
        else  {
          longClick();
        }
      }
    }

};