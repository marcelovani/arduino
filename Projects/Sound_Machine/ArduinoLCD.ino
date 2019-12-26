// From http://arduino-er.blogspot.com/2015/04/display-waveform-on-mini-oled-with.html

// ref u8glib: https://code.google.com/p/u8glib/
// To install u8glib on Arduino IDE: http://goo.gl/j3olBA
// https://github.com/olikraus/u8g2/wiki
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

const int LCD_WIDTH = 128;
const int LCD_HEIGHT = 64;

int x;
int y[LCD_WIDTH];

void clearXY() {
  for (int i = 0; i < LCD_WIDTH; i++) {
    y[i] = -1;
  }
}

void drawXY() {
  if (knobsMoving()) {
    return;
  }

  y[x] = map(getSma(), 0, 1023, LCD_HEIGHT - 1, 0) - LCD_HEIGHT / 2 ;

  u8g.firstPage();
  do {
    u8g.drawPixel(0, y[0]);
    for (int i = 1; i < LCD_WIDTH; i++) {
      if (y[i] != -1) {
        //u8g.drawPixel(i, y[i]);
        u8g.drawLine(i - 1, y[i - 1], i, y[i]);
      } else {
        break;
      }
    }
  } while ( u8g.nextPage() );

  x++;
  if (x >= LCD_WIDTH) {
    x = 0;
    clearXY();
  }
}

void LCDsetup(void) {
  // flip screen, if required
  //u8g.setRot180();

  splash();

  x = 0;
  clearXY();
}

/*
   Splash screen
*/
void splash() {
  u8g.firstPage();
  do {
    u8g.setFontPosTop();
    u8g.setFont(u8g_font_5x7r);
    u8g.drawStr( 0, 10,  " Sound Machine v1.0");
    u8g.drawStr( 0, 20, "Copyright (c) 2019/20");
    u8g.drawStr( 0, 30, "  By MarlovaSoft Tm");
  } while ( u8g.nextPage() );
  delay(1000);
}

void LCDloop(void) {
  drawXY();

  displayKnobs();

  //delay(10);
}
