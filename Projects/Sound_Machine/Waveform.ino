// From http://arduino-er.blogspot.com/2015/04/display-waveform-on-mini-oled-with.html

// ref u8glib: https://code.google.com/p/u8glib/
// To install u8glib on Arduino IDE: http://goo.gl/j3olBA
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

const int LCD_WIDTH=128;
const int LCD_HEIGHT=64;

int x;
int y[LCD_WIDTH];

void clearY(){
  for(int i=0; i<LCD_WIDTH; i++){
    y[i] = -1;
  }
}

void drawY(){
  if (knobMoving()) {
    return;
  }
  u8g.drawPixel(0, y[0]);
  for(int i=1; i<LCD_WIDTH; i++){
    if(y[i]!=-1){
      //u8g.drawPixel(i, y[i]);
      u8g.drawLine(i-1, y[i-1], i, y[i]);
    }else{
      break;
    }
  }
}

void LCDsetup(void) {
  x = 0;
  clearY();
}

void LCDloop(void) {
    
  y[x] = map(getSma(), 0, 1023, LCD_HEIGHT-1, 0);

  u8g.firstPage();  
  do {
    drawY();
  } while( u8g.nextPage() );
  
  //delay(10);

  x++;
  if(x >= LCD_WIDTH){
    x = 0;
    clearY();
  }
}
