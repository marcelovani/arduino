class ClickQueue: public Runnable {
    const byte pin;
    // make these slow for testing
    const unsigned CLICK_DOWN_MS = 250;
    const unsigned CLICK_TOTAL_MS = 1000;

    enum State {
      NOT_CLICKING = 0,
      CLICK_DOWN = 1,
      CLICK_PAUSE = 2
    } state;

    unsigned long clickStartMs;
    int pendingClicks;

  public:
    ClickQueue(byte attachTo) :
      pin(attachTo) {
    }

    void setup() {
      pinMode(pin, OUTPUT);
      state = NOT_CLICKING;
      pendingClicks = 0;
    }

    void loop() {
      switch (state) {
        case NOT_CLICKING:
          if (pendingClicks > 0) {
            pendingClicks --;
            digitalWrite(pin, HIGH);
            clickStartMs = millis();
            state = CLICK_DOWN;
          }
          break;
        case CLICK_DOWN:
          if (millis() - clickStartMs > CLICK_DOWN_MS) {
            digitalWrite(pin, LOW);
            state = CLICK_PAUSE;
          }
          break;
        case CLICK_PAUSE:
          if (millis() - clickStartMs > CLICK_TOTAL_MS) {
            state = NOT_CLICKING;
          }
          break;
      }
    }

    void addAClick() {
      pendingClicks++;
    }

    void addClicks(int clicks) {
      pendingClicks += clicks;
    }

    void cancel() {
      pendingClicks = 0;
      digitalWrite(pin, LOW);
      state = NOT_CLICKING;
    }
};
