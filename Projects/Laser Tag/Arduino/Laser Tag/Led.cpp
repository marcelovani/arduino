class Led: public Runnable {
  byte pin;

  unsigned long _timerInterval;
  unsigned long _timerDuration;
  short int _timerRepeat;

  private:
    MillisTimer _timerOn;
    MillisTimer _timerOff;

  public:
    byte status;

    Led(byte pin) : pin(pin) {
    }

    void setup() {
      status = LOW;
      pinMode(pin, OUTPUT);
      send();
    }

    void loop() {
      if (_timerRepeat == 0) {
        this->_timerOn.stop();
        this->_timerOff.stop();
        this->off();
      }

      if (this->status == LOW && _timerRepeat > 0) {
        this->_timerOn.run();
        if (this->_timerOn.isRunning())
        {
          this->send();
        }

        if (!this->_timerOn.isRunning())
        {
          this->on();
          _timerRepeat--;
          this->timerOffStart();
        }
      }

      if (this->status == HIGH && _timerRepeat > 0) {
        this->_timerOff.run();
        if (this->_timerOff.isRunning())
        {
          this->send();
        }

        if (!this->_timerOff.isRunning())
        {
          this->off();
          this->timerOnStart();
        }
      }
    }

    void send() {
      digitalWrite(pin, status);
    }

    void powerToggle() {
      if (status) {
        status = LOW;
      }
      else {
        status = HIGH;
      }
      send();
    }

    byte getPin() {
      return pin;
    }

    void on() {
      if (!status) {
        status = HIGH;
        send();
      }
    }

    void off() {
      if (status) {
        status = LOW;
        send();
      }
    }

    void timerOnStart()
    {
      this->_timerOn.setInterval(_timerDuration);
      this->_timerOn.setRepeats(1);
      this->_timerOn.start();
    }

    void timerOffStart()
    {
      this->_timerOff.setInterval(_timerInterval);
      this->_timerOff.setRepeats(1);
      this->_timerOff.start();
    }

    /**
     * Blink needs 3 arguments
     *  - Interval: How how long between blinks (when Repeat is > 1)
     *  - Duration: For how long the Led stays on when it blinks
     *  - Repeat: How many times it should blink
     */
    void blink(unsigned long interval, unsigned long duration, byte repeat)
    {
      // Serial.print("Blink repeat "); Serial.println(_timerRepeat);
      if (this->_timerOn.isRunning() || this->_timerOff.isRunning()) {
        // Serial.println(_id + " timer is running");
        return;
      }

      _timerRepeat = repeat;
      _timerInterval = interval;
      _timerDuration = duration;
      this->status = LOW;

      this->timerOnStart();
    }
};
