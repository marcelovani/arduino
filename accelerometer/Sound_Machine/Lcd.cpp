/*
 * See https://www.arduino.cc/en/Tutorial/LiquidCrystalCursor
 * https://www.instructables.com/id/Arduino-Nano-Directly-Connected-2-X-16-LCD-Display/
 * The circuit:
 * LCD RS pin to digital pin 2
 * LCD Enable pin to digital pin 3
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */
#include "Lcd.h"
#include<LiquidCrystal.h>

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

namespace Lcd{

  void setupLcd() {
    lcd.begin(16,2);
    lcd.clear();
    lcd.print("Loading...");
  }

  void setCursor(int posX, int posY) {
    lcd.setCursor(posX, posY);
  }

  void printV(float val) {
    lcd.print(val);
  }

  void printM(char msg) {
    lcd.print(msg);
  }
};
