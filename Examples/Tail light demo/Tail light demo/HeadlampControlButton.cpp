class HeadlampControlButton: public Button {
    Headlamp &lamp;

  public:
    HeadlampControlButton(byte attachToPin, Headlamp &attachToHeadlamp) :
      Button(attachToPin),
      lamp(attachToHeadlamp) {
    }
  protected:
    void shortClick() {
      // short click
      lamp.brightnessClick();
    }

    void longClick() {
      // long click
      lamp.powerToggle();
    }
};
