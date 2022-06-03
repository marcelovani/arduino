#include "xyGraph.h"

/*
    Constructor
*/
xyGraph::xyGraph(void) {
}

/*
   Draw graph
*/
void xyGraph::draw(Adafruit_SSD1306 &screen, int value) {
  if (_y > 128) {
    _y = 1;
    _redraw = true;
  }
  drawCGraph(screen, value, _y++, 30, 50, 75, 30, 0, 100, 25, 0, 1024, 512, 0, "Acceleration", _redraw);    
}

/*
   Draw a cartesian graph
*/
void xyGraph::drawCGraph(Adafruit_SSD1306 &display, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, double dig, String title, boolean &Redraw) {

  double i;
  double temp;

  if (Redraw == true) {
    Redraw = false;
    display.fillRect(0, 0,  127 , 16, SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(2, 4);
    display.println(title);
    _ox = (_x - xlo) * ( w) / (xhi - xlo) + gx;
    _oy = (_y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      // note my transform funcition is the same as the map function, except the map uses long and we need doubles
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
      if (i == 0) {
        display.drawFastHLine(gx - 3, temp, w + 3, SSD1306_WHITE);
      }
      else {
        display.drawFastHLine(gx - 3, temp, 3, SSD1306_WHITE);
      }
      display.setCursor(gx - 27, temp - 3);
      display.println(i, dig);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {
      // compute the transform
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        display.drawFastVLine(temp, gy - h, h + 3, SSD1306_WHITE);
      }
      else {
        display.drawFastVLine(temp, gy, 3, SSD1306_WHITE);
      }
      display.setCursor(temp, gy + 6);
      display.println(i, dig);
    }
  }

  // graph drawn now plot the data
  // the entire plotting code are these few lines...

  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  display.drawLine(_ox, _oy, _x, _y, SSD1306_WHITE);
  display.drawLine(_ox, _oy - 1, _x, _y - 1, SSD1306_WHITE);
  _ox = _x;
  _oy = _y;

  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  display.display();

}
