#if defined(__ARDUINO_AVR_UNO__) || defined(ARDUINO_AVR_UNO)

    Laser laser1(13);
    RgbLed rgb1(12, 10, 11);
    Servos servo1(9);
    Target target1(8, laser1, rgb1, servo1);

    Laser laser2(6);
    RgbLed rgb2(5, 3, 4);
    Servos servo2(2);
    Target target2(7, laser2, rgb2, servo2);

#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

    Laser laser1(6);
    RgbLed rgb1(4, 3, 2);
    Servos servo1(7);
    Target target1(5, laser1, rgb1, servo1);

    Laser laser2(12);
    RgbLed rgb2(10, 9, 8);
    Servos servo2(13);
    Target target2(11, laser2, rgb2, servo2);

#endif
