#include "PotGraph.h"

/*
    Constructor
*/
PotGraph::PotGraph(void) {
}

/*
   Draw graphs
*/
void PotGraph::draw(Adafruit_SSD1306 &screen, Pot &pot) {
//  if (pot.knobMoving()) {
//    return;
//  }
  //  if (_drawing) {
  //    return;
  //  }

  switch (pot.type) {
    case PotGraphTypeDial:
      {
        int inc = 1; // Calculate increment
        if (pot.max > 10) {
          inc = pot.max / 10;
        }
        drawDial(screen, pot.value, 65, 53, 25, 0, pot.max, inc, 0, 180, pot.label, _redraw);
      }
      break;

    case PotGraphTypeChartV:
      {
        drawBarChartV(screen, pot.value, 10, 45, 100, 20, 0, 5, 1, 0, pot.label, _redraw);
      }
      break;

    case PotGraphTypeChartH:
      {
        drawBarChartH(screen, pot.value, 10, 45, 100, 20, 0, 5, 1, 0, pot.label, _redraw);
      }
      break;

    default:
      break;
  }
}

/*
   Draw a dial
*/
void PotGraph::drawDial(Adafruit_SSD1306 &display, double curval, int cx, int cy, int r, double loval , double hival , double inc, double dig, double sa, String label, bool &Redraw) {
  double ix, iy, ox, oy, tx, ty, lx, rx, ly, ry, i, Offset, stepval, data, angle;
  double degtorad = .0174532778;
  static double pix = cx, piy = cy, plx = cx, ply = cy, prx = cx, pry = cy;

  if (Redraw) {
    Redraw = false;
    // draw the dial only one time--this will minimize flicker
    if (INVERT_DIAL_LABEL) {
      display.fillRect(0, 0,  127 , 16, SSD1306_WHITE);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else {
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    }
    display.setTextSize(1);
    display.setCursor(2, 4);
    display.println(label);

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
      display.drawLine(ox, oy, ix, iy, SSD1306_WHITE);
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      display.setCursor(tx - 10, ty );
      data = hival - ( i * (inc / stepval)) ;
      display.println(data, dig);
    }
    for (i = 0; i <= sa; i ++) {
      angle = ( i  * degtorad);
      angle = Offset - angle ;
      ox =  (r - 2) * cos(angle) + cx;
      oy =  (r - 2) * sin(angle) + cy;
      display.drawPixel(ox, oy, SSD1306_WHITE);
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
  display.fillTriangle (pix, piy, plx, ply, prx, pry, SSD1306_BLACK);

  // then draw the new needle
  display.fillTriangle (ix, iy, lx, ly, rx, ry, SSD1306_WHITE);

  // draw a cute little dial center
  display.fillCircle(cx, cy, 3, SSD1306_WHITE);

  //save all current to old so the previous dial can be hidden
  pix = ix;
  piy = iy;
  plx = lx;
  ply = ly;
  prx = rx;
  pry = ry;
  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  display.display();
}

/*
   Draw a vertical bar chart
*/
void PotGraph::drawBarChartV(Adafruit_SSD1306 &display, double curval, double x , double y , double w, double h , double loval , double hival , double inc , double dig, String label, bool &Redraw)
{
  double stepval, my, level, i, data;

  if (Redraw) {
    Redraw = false;
    display.fillRect(0, 0,  127 , 14, SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(2, 4);
    display.println(label);
    // step val basically scales the hival and low val to the height
    // deducting a small value to eliminate round off errors
    // this val may need to be adjusted
    stepval = ( inc) * (double (h) / (double (hival - loval))) - .001;
    for (i = 0; i <= h; i += stepval) {
      my =  y - h + i;
      display.drawFastHLine(x + w + 1, my,  5, SSD1306_WHITE);
      // draw lables
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      display.setCursor(x + w + 12, my - 3 );
      data = hival - ( i * (inc / stepval));
      display.print(data, dig);
    }
  }
  // compute level of bar graph that is scaled to the  height and the hi and low vals
  // this is needed to accompdate for +/- range
  level = (h * (((curval - loval) / (hival - loval))));
  // draw the bar graph
  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
  display.drawRect(x, y - h, w, h, SSD1306_WHITE);
  display.fillRect(x, y - h, w, h - level,  SSD1306_BLACK);
  display.drawRect(x, y - h, w, h, SSD1306_WHITE);
  display.fillRect(x, y - level, w,  level, SSD1306_WHITE);
  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  display.display();
}

/*
   Draw a horizontal chart
*/
void PotGraph::drawBarChartH(Adafruit_SSD1306 &display, double curval, double x , double y , double w, double h , double loval , double hival , double inc , double dig, String label, bool &Redraw)
{
  double stepval, level, i, data;

  if (Redraw) {
    Redraw = false;
    display.fillRect(0, 0,  127 , 16, SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(2, 4);
    display.println(label);
    // step val basically scales the hival and low val to the width
    stepval =  inc * (double (w) / (double (hival - loval))) - .00001;
    // draw the text
    for (i = 0; i <= w; i += stepval) {
      display.drawFastVLine(i + x , y ,  5, SSD1306_WHITE);
      // draw lables
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      display.setCursor(i + x , y + 10);
      // addling a small value to eliminate round off errors
      // this val may need to be adjusted
      data =  ( i * (inc / stepval)) + loval + 0.00001;
      display.print(data, dig);
    }
  }
  // compute level of bar graph that is scaled to the width and the hi and low vals
  // this is needed to accompdate for +/- range capability
  // draw the bar graph
  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
  level = (w * (((curval - loval) / (hival - loval))));
  display.fillRect(x + level, y - h, w - level, h,  SSD1306_BLACK);
  display.drawRect(x, y - h, w,  h, SSD1306_WHITE);
  display.fillRect(x, y - h, level,  h, SSD1306_WHITE);
  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  display.display();

}

/*
   Draw a cartesian graph
*/
void PotGraph::drawCGraph(Adafruit_SSD1306 &display, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, double dig, String title, boolean &Redraw) {

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
