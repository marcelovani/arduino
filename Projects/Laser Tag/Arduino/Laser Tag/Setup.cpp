#if defined(__ARDUINO_AVR_UNO__) || defined(ARDUINO_AVR_UNO)

    Servos servo1(9);
    Laser laser1(13);
    RgbLed rgb1(12, 10, 11);
    Target target1(8, laser1, rgb1, servo1);

    Servos servo2(2);
    Laser laser2(6);
    RgbLed rgb2(5, 3, 4);
    Target target2(7, laser2, rgb2, servo2);

#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

    Servos servo1(7);
    Laser laser1(6);
    RgbLed rgb1(4, 3, 2);
    Target target1(5, laser1, rgb1, servo1);

    Servos servo2(13);
    Laser laser2(12);
    RgbLed rgb2(10, 9, 8);
    Target target2(11, laser2, rgb2, servo2);

#endif

void setup() {
  Serial.begin(9600);
  Runnable::setupAll();
}
