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

  // Redraw when switching between pots.
  if (_id != pot.getPin()) {
    _id = pot.getPin();
    _redraw = true;
  }
  Serial.print(_id);
  Serial.print("\t");

  switch (pot.getType()) {
    case PotGraphTypeDial:
      {
        int inc = 1; // Calculate increment
        if (pot.getMax() > 10) {
          inc = pot.getMax() / 10;
        }
        drawDial(screen, pot.getValue(), 65, 53, 25, 0, pot.getMax(), inc, 0, 180, pot.getLabel(), _redraw);
      }
      break;

    case PotGraphTypeChartV:
      {
        //drawBarChartV(screen, pot.value, 10, 45, 100, 20, 0, 5, 1, 0, pot.label, _redraw);
      }
      break;

    case PotGraphTypeChartH:
      {
        //drawBarChartH(screen, pot.value, 10, 45, 100, 20, 0, 5, 1, 0, pot.label, _redraw);
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
