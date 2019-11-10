#include "LCD.h"

/*
 * Constructor
 */
PotLCD::PotLCD(uint8_t w, uint8_t h, uint8_t addr, int8_t rst_pin)
{
  _w = w;
  _h = h;
  _addr = addr;
  _rst_pin = rst_pin;

    // create the display object
  Adafruit_SSD1306 _display(_w, _h, &Wire, _rst_pin);

  // initialize the display
  // note you may have to change the address
  // the most common are 0X3C and 0X3D
  _display.begin(SSD1306_SWITCHCAPVCC, _addr);

  // if you distribute your code, the adafruit license requires you show their splash screen
  // otherwise clear the video buffer memory then display
  _display.display();

  delay(20);
  _display.clearDisplay();
  _display.display();
}

/*
 * Draw a dial
 */
void PotLCD::drawDial(double curval, int cx, int cy, int r, double loval , double hival , double inc, double dig, double sa, String label, bool &Redraw) {

  double ix, iy, ox, oy, tx, ty, lx, rx, ly, ry, i, Offset, stepval, data, angle;
  double degtorad = .0174532778;
  static double pix = cx, piy = cy, plx = cx, ply = cy, prx = cx, pry = cy;

  if (Redraw) {
    Redraw = false;
    // draw the dial only one time--this will minimize flicker
    _display.fillRect(0, 0,  127 , 16, SSD1306_WHITE);
    _display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    _display.setTextSize(1);
    _display.setCursor(2, 4);
    _display.println(label);
    // center the scale about the vertical axis--and use this to offset the needle, and scale text
    Offset = (270 +  sa / 2) * degtorad;
    // find hte scale step value based on the hival low val and the scale sweep angle
    // deducting a small value to eliminate round off errors
    // this val may need to be adjusted
    stepval = ( inc) * (double (sa) / (double (hival - loval))) + .00;
    // draw the scale and numbers
    // note draw this each time to repaint where the needle was
    for (i = 0; i <= sa; i += stepval) {
      angle = ( i  * degtorad);
      angle = Offset - angle ;
      ox =  (r - 2) * cos(angle) + cx;
      oy =  (r - 2) * sin(angle) + cy;
      ix =  (r - 10) * cos(angle) + cx;
      iy =  (r - 10) * sin(angle) + cy;
      tx =  (r + 10) * cos(angle) + cx + 8;
      ty =  (r + 10) * sin(angle) + cy;
      _display.drawLine(ox, oy, ix, iy, SSD1306_WHITE);
      _display.setTextSize(1);
      _display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      _display.setCursor(tx - 10, ty );
      data = hival - ( i * (inc / stepval)) ;
      _display.println(data, dig);
    }
    for (i = 0; i <= sa; i ++) {
      angle = ( i  * degtorad);
      angle = Offset - angle ;
      ox =  (r - 2) * cos(angle) + cx;
      oy =  (r - 2) * sin(angle) + cy;
      _display.drawPixel(ox, oy, SSD1306_WHITE);
    }
  }
  // compute and draw the needle
  angle = (sa * (1 - (((curval - loval) / (hival - loval)))));
  angle = angle * degtorad;
  angle = Offset - angle  ;
  ix =  (r - 10) * cos(angle) + cx;
  iy =  (r - 10) * sin(angle) + cy;
  // draw a triangle for the needle (compute and store 3 vertiticies)
  lx =  2 * cos(angle - 90 * degtorad) + cx;
  ly =  2 * sin(angle - 90 * degtorad) + cy;
  rx =  2 * cos(angle + 90 * degtorad) + cx;
  ry =  2 * sin(angle + 90 * degtorad) + cy;

  // blank out the old needle
  _display.fillTriangle (pix, piy, plx, ply, prx, pry, SSD1306_BLACK);

  // then draw the new needle
  _display.fillTriangle (ix, iy, lx, ly, rx, ry, SSD1306_WHITE);

  // draw a cute little dial center
  _display.fillCircle(cx, cy, 3, SSD1306_WHITE);

  //save all current to old so the previous dial can be hidden
  pix = ix;
  piy = iy;
  plx = lx;
  ply = ly;
  prx = rx;
  pry = ry;
  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  _display.display();
}

/*
 * Draw a vertical bar chart
 */
void PotLCD::drawBarChartV(double curval, double x , double y , double w, double h , double loval , double hival , double inc , double dig, String label, bool &Redraw)
{
  double stepval, my, level, i, data;

  if (Redraw) {
    Redraw = false;
    _display.fillRect(0, 0,  127 , 14, SSD1306_WHITE);
    _display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    _display.setTextSize(1);
    _display.setCursor(2, 4);
    _display.println(label);
    // step val basically scales the hival and low val to the height
    // deducting a small value to eliminate round off errors
    // this val may need to be adjusted
    stepval = ( inc) * (double (h) / (double (hival - loval))) - .001;
    for (i = 0; i <= h; i += stepval) {
      my =  y - h + i;
      _display.drawFastHLine(x + w + 1, my,  5, SSD1306_WHITE);
      // draw lables
      _display.setTextSize(1);
      _display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      _display.setCursor(x + w + 12, my - 3 );
      data = hival - ( i * (inc / stepval));
      _display.print(data, dig);
    }
  }
  // compute level of bar graph that is scaled to the  height and the hi and low vals
  // this is needed to accompdate for +/- range
  level = (h * (((curval - loval) / (hival - loval))));
  // draw the bar graph
  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
  _display.drawRect(x, y - h, w, h, SSD1306_WHITE);
  _display.fillRect(x, y - h, w, h - level,  SSD1306_BLACK);
  _display.drawRect(x, y - h, w, h, SSD1306_WHITE);
  _display.fillRect(x, y - level, w,  level, SSD1306_WHITE);
  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  _display.display();
}

/*
 * Draw a horizontal chart
 */
void PotLCD::drawBarChartH(double curval, double x , double y , double w, double h , double loval , double hival , double inc , double dig, String label, bool &Redraw)
{
  double stepval, level, i, data;

  if (Redraw) {
    Redraw = false;
    _display.fillRect(0, 0,  127 , 16, SSD1306_WHITE);
    _display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    _display.setTextSize(1);
    _display.setCursor(2, 4);
    _display.println(label);
    // step val basically scales the hival and low val to the width
    stepval =  inc * (double (w) / (double (hival - loval))) - .00001;
    // draw the text
    for (i = 0; i <= w; i += stepval) {
      _display.drawFastVLine(i + x , y ,  5, SSD1306_WHITE);
      // draw lables
      _display.setTextSize(1);
      _display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      _display.setCursor(i + x , y + 10);
      // addling a small value to eliminate round off errors
      // this val may need to be adjusted
      data =  ( i * (inc / stepval)) + loval + 0.00001;
      _display.print(data, dig);
    }
  }
  // compute level of bar graph that is scaled to the width and the hi and low vals
  // this is needed to accompdate for +/- range capability
  // draw the bar graph
  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
  level = (w * (((curval - loval) / (hival - loval))));
  _display.fillRect(x + level, y - h, w - level, h,  SSD1306_BLACK);
  _display.drawRect(x, y - h, w,  h, SSD1306_WHITE);
  _display.fillRect(x, y - h, level,  h, SSD1306_WHITE);
  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  _display.display();

}

/*
 * Draw a cartesian graph
 */
void PotLCD::drawCGraph(double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, double dig, String title, boolean &Redraw) {

  double i;
  double temp;

  if (Redraw == true) {
    Redraw = false;
    _display.fillRect(0, 0,  127 , 16, SSD1306_WHITE);
    _display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    _display.setTextSize(1);
    _display.setCursor(2, 4);
    _display.println(title);
    _ox = (_x - xlo) * ( w) / (xhi - xlo) + gx;
    _oy = (_y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      // note my transform funcition is the same as the map function, except the map uses long and we need doubles
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
      if (i == 0) {
        _display.drawFastHLine(gx - 3, temp, w + 3, SSD1306_WHITE);
      }
      else {
        _display.drawFastHLine(gx - 3, temp, 3, SSD1306_WHITE);
      }
      _display.setCursor(gx - 27, temp - 3);
      _display.println(i, dig);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {
      // compute the transform
      _display.setTextSize(1);
      _display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        _display.drawFastVLine(temp, gy - h, h + 3, SSD1306_WHITE);
      }
      else {
        _display.drawFastVLine(temp, gy, 3, SSD1306_WHITE);
      }
      _display.setCursor(temp, gy + 6);
      _display.println(i, dig);
    }
  }

  // graph drawn now plot the data
  // the entire plotting code are these few lines...

  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  _display.drawLine(_ox, _oy, _x, _y, SSD1306_WHITE);
  _display.drawLine(_ox, _oy - 1, _x, _y - 1, SSD1306_WHITE);
  _ox = _x;
  _oy = _y;

  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  _display.display();

}
