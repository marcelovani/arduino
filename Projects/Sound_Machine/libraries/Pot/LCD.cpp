#include "LCD.h"

/*
 * Constructor
 */
PotLCD::PotLCD(uint8_t w, uint8_t h, uint8_t addr, int8_t rst_pin, short int type=PotLCDTypeDial)
{
  _w = w;
  _h = h;
  _addr = addr;
  _rst_pin = rst_pin;
  _type = type;

    // create the display object
  Adafruit_SSD1306 display(_w, _h, &Wire, _rst_pin);

  // initialize the display
  // note you may have to change the address
  // the most common are 0X3C and 0X3D
  display.begin(SSD1306_SWITCHCAPVCC, _addr);

  // if you distribute your code, the adafruit license requires you show their splash screen
  // otherwise clear the video buffer memory then display
  display.display();

  delay(20);
  display.clearDisplay();
  display.display();
}

/*
 * Draw a dial
 */
void PotLCD::DrawDial(Adafruit_SSD1306 &d, double curval, int cx, int cy, int r, double loval , double hival , double inc, double dig, double sa, String label, bool &Redraw) {

  double ix, iy, ox, oy, tx, ty, lx, rx, ly, ry, i, Offset, stepval, data, angle;
  double degtorad = .0174532778;
  static double px = cx, py = cy, pix = cx, piy = cy, plx = cx, ply = cy, prx = cx, pry = cy;

  if (Redraw) {
    Redraw = false;
    // draw the dial only one time--this will minimize flicker
    d.fillRect(0, 0,  127 , 16, SSD1306_WHITE);
    d.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    d.setTextSize(1);
    d.setCursor(2, 4);
    d.println(label);
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
      d.drawLine(ox, oy, ix, iy, SSD1306_WHITE);
      d.setTextSize(1);
      d.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      d.setCursor(tx - 10, ty );
      data = hival - ( i * (inc / stepval)) ;
      d.println(data, dig);
    }
    for (i = 0; i <= sa; i ++) {
      angle = ( i  * degtorad);
      angle = Offset - angle ;
      ox =  (r - 2) * cos(angle) + cx;
      oy =  (r - 2) * sin(angle) + cy;
      d.drawPixel(ox, oy, SSD1306_WHITE);
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
  d.fillTriangle (pix, piy, plx, ply, prx, pry, SSD1306_BLACK);

  // then draw the new needle
  d.fillTriangle (ix, iy, lx, ly, rx, ry, SSD1306_WHITE);

  // draw a cute little dial center
  d.fillCircle(cx, cy, 3, SSD1306_WHITE);

  //save all current to old so the previous dial can be hidden
  pix = ix;
  piy = iy;
  plx = lx;
  ply = ly;
  prx = rx;
  pry = ry;
  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  d.display();
}

/*
 * Draw a vertical bar chart
 */
void PotLCD::DrawBarChartV(Adafruit_SSD1306 &d, double curval, double x , double y , double w, double h , double loval , double hival , double inc , double dig, String label, bool &Redraw)
{
  double stepval, my, level, i, data;

  if (Redraw) {
    Redraw = false;
    d.fillRect(0, 0,  127 , 14, SSD1306_WHITE);
    d.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    d.setTextSize(1);
    d.setCursor(2, 4);
    d.println(label);
    // step val basically scales the hival and low val to the height
    // deducting a small value to eliminate round off errors
    // this val may need to be adjusted
    stepval = ( inc) * (double (h) / (double (hival - loval))) - .001;
    for (i = 0; i <= h; i += stepval) {
      my =  y - h + i;
      d.drawFastHLine(x + w + 1, my,  5, SSD1306_WHITE);
      // draw lables
      d.setTextSize(1);
      d.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      d.setCursor(x + w + 12, my - 3 );
      data = hival - ( i * (inc / stepval));
      d.print(data, dig);
    }
  }
  // compute level of bar graph that is scaled to the  height and the hi and low vals
  // this is needed to accompdate for +/- range
  level = (h * (((curval - loval) / (hival - loval))));
  // draw the bar graph
  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
  d.drawRect(x, y - h, w, h, SSD1306_WHITE);
  d.fillRect(x, y - h, w, h - level,  SSD1306_BLACK);
  d.drawRect(x, y - h, w, h, SSD1306_WHITE);
  d.fillRect(x, y - level, w,  level, SSD1306_WHITE);
  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  d.display();

}

/*
 * Draw a horizontal chart
 */
void PotLCD::DrawBarChartH(Adafruit_SSD1306 &d, double curval, double x , double y , double w, double h , double loval , double hival , double inc , double dig, String label, bool &Redraw)
{
  double stepval, mx, level, i, data;

  if (Redraw) {
    Redraw = false;
    d.fillRect(0, 0,  127 , 16, SSD1306_WHITE);
    d.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    d.setTextSize(1);
    d.setCursor(2, 4);
    d.println(label);
    // step val basically scales the hival and low val to the width
    stepval =  inc * (double (w) / (double (hival - loval))) - .00001;
    // draw the text
    for (i = 0; i <= w; i += stepval) {
      d.drawFastVLine(i + x , y ,  5, SSD1306_WHITE);
      // draw lables
      d.setTextSize(1);
      d.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      d.setCursor(i + x , y + 10);
      // addling a small value to eliminate round off errors
      // this val may need to be adjusted
      data =  ( i * (inc / stepval)) + loval + 0.00001;
      d.print(data, dig);
    }
  }
  // compute level of bar graph that is scaled to the width and the hi and low vals
  // this is needed to accompdate for +/- range capability
  // draw the bar graph
  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
  level = (w * (((curval - loval) / (hival - loval))));
  d.fillRect(x + level, y - h, w - level, h,  SSD1306_BLACK);
  d.drawRect(x, y - h, w,  h, SSD1306_WHITE);
  d.fillRect(x, y - h, level,  h, SSD1306_WHITE);
  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  d.display();

}

/*
 * Draw a cartesian graph
 */
void PotLCD::DrawCGraph(Adafruit_SSD1306 &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, double dig, String title, boolean &Redraw) {

  double i;
  double temp;
  int rot, newrot;

  if (Redraw == true) {
    Redraw = false;
    d.fillRect(0, 0,  127 , 16, SSD1306_WHITE);
    d.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    d.setTextSize(1);
    d.setCursor(2, 4);
    d.println(title);
    _ox = (_x - xlo) * ( w) / (xhi - xlo) + gx;
    _oy = (_y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    d.setTextSize(1);
    d.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      // note my transform funcition is the same as the map function, except the map uses long and we need doubles
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
      if (i == 0) {
        d.drawFastHLine(gx - 3, temp, w + 3, SSD1306_WHITE);
      }
      else {
        d.drawFastHLine(gx - 3, temp, 3, SSD1306_WHITE);
      }
      d.setCursor(gx - 27, temp - 3);
      d.println(i, dig);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {
      // compute the transform
      d.setTextSize(1);
      d.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.drawFastVLine(temp, gy - h, h + 3, SSD1306_WHITE);
      }
      else {
        d.drawFastVLine(temp, gy, 3, SSD1306_WHITE);
      }
      d.setCursor(temp, gy + 6);
      d.println(i, dig);
    }
  }

  // graph drawn now plot the data
  // the entire plotting code are these few lines...

  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawLine(_ox, _oy, _x, _y, SSD1306_WHITE);
  d.drawLine(_ox, _oy - 1, _x, _y - 1, SSD1306_WHITE);
  _ox = _x;
  _oy = _y;

  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  d.display();

}
