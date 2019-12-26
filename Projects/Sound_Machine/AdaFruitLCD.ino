#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define READ_PIN            A0
#define OLED_RESET          -1 // -1 or A4

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

double ox , oy ;
bool Redraw = true;

// Initialize LCD display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void AdaFruitLCDSetup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
  splash();
  delay(1000);
  display.clearDisplay();
  display.display();

  DrawCGraph(1, 2, 30, 50, 75, 30, 0, 100, 25, 0, 1024, 512, 0, "Bits vs Seconds", Redraw);
}

/*
   Splash screen
*/
//void splash() {
//  display.setTextSize(1);
//  display.setTextColor(SSD1306_WHITE);
//  display.setCursor(0, 0);
//  display.print("PotGraph v1.0\nCopyright (c) 2019\nBy MarlovaSoft Tm");
//  display.display();
//}

/*
  This method will draw a dial-type graph for single input
  it has a rather large arguement list and is as follows

  curval = date to graph (must be between loval and hival)
  cx = center position of dial
  cy = center position of dial
  r = radius of the dial
  loval = lower value of the scale (can be negative)
  hival = upper value of the scale
  inc = scale division between loval and hival
  sa = sweep angle for the dials scale
  dig = format control to set number of digits to display. (not includeing the decimal)
  label = bottom lable text for the graph
  redraw = flag to redraw display. only on first pass (to reduce flickering)
*/

//void DrawDial(double curval, int cx, int cy, int r, double loval , double hival , double inc, double dig, double sa, String label, bool &Redraw) {
//
//  double ix, iy, ox, oy, tx, ty, lx, rx, ly, ry, i, Offset, stepval, data, angle;
//  double degtorad = .0174532778;
//  static double pix = cx, piy = cy, plx = cx, ply = cy, prx = cx, pry = cy;
//
//  if (Redraw) {
//    Redraw = false;
//    // draw the dial only one time--this will minimize flicker
//    display.fillRect(0, 0,  127 , 16, SSD1306_WHITE);
//    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
//    display.setTextSize(1);
//    display.setCursor(2, 4);
//    display.println(label);
//    // center the scale about the vertical axis--and use this to offset the needle, and scale text
//    Offset = (270 +  sa / 2) * degtorad;
//    // find hte scale step value based on the hival low val and the scale sweep angle
//    // deducting a small value to eliminate round off errors
//    // this val may need to be adjusted
//    stepval = ( inc) * (double (sa) / (double (hival - loval))) + .00;
//    // draw the scale and numbers
//    // note draw this each time to repaint where the needle was
//    for (i = 0; i <= sa; i += stepval) {
//      angle = ( i  * degtorad);
//      angle = Offset - angle ;
//      ox =  (r - 2) * cos(angle) + cx;
//      oy =  (r - 2) * sin(angle) + cy;
//      ix =  (r - 10) * cos(angle) + cx;
//      iy =  (r - 10) * sin(angle) + cy;
//      tx =  (r + 10) * cos(angle) + cx + 8;
//      ty =  (r + 10) * sin(angle) + cy;
//      display.drawLine(ox, oy, ix, iy, SSD1306_WHITE);
//      display.setTextSize(1);
//      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
//      display.setCursor(tx - 10, ty );
//      data = hival - ( i * (inc / stepval)) ;
//      display.println(data, dig);
//    }
//    for (i = 0; i <= sa; i ++) {
//      angle = ( i  * degtorad);
//      angle = Offset - angle ;
//      ox =  (r - 2) * cos(angle) + cx;
//      oy =  (r - 2) * sin(angle) + cy;
//      display.drawPixel(ox, oy, SSD1306_WHITE);
//    }
//  }
//  // compute and draw the needle
//  angle = (sa * (1 - (((curval - loval) / (hival - loval)))));
//  angle = angle * degtorad;
//  angle = Offset - angle  ;
//  ix =  (r - 10) * cos(angle) + cx;
//  iy =  (r - 10) * sin(angle) + cy;
//  // draw a triangle for the needle (compute and store 3 vertiticies)
//  lx =  2 * cos(angle - 90 * degtorad) + cx;
//  ly =  2 * sin(angle - 90 * degtorad) + cy;
//  rx =  2 * cos(angle + 90 * degtorad) + cx;
//  ry =  2 * sin(angle + 90 * degtorad) + cy;
//
//  // blank out the old needle
//  display.fillTriangle (pix, piy, plx, ply, prx, pry, SSD1306_BLACK);
//
//  // then draw the new needle
//  display.fillTriangle (ix, iy, lx, ly, rx, ry, SSD1306_WHITE);
//
//  // draw a cute little dial center
//  display.fillCircle(cx, cy, 3, SSD1306_WHITE);
//
//  //save all current to old so the previous dial can be hidden
//  pix = ix;
//  piy = iy;
//  plx = lx;
//  ply = ly;
//  prx = rx;
//  pry = ry;
//  // up until now print sends data to a video buffer NOT the screen
//  // this call sends the data to the screen
//  display.display();
//
//}

void DrawCGraph(double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, double dig, String title, boolean &Redraw) {

  double i;
  double temp;

  if (Redraw == true) {
    Redraw = false;
    display.fillRect(0, 0,  127 , 16, SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(2, 4);
    display.println(title);
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
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
  display.drawLine(ox, oy, x, y, SSD1306_WHITE);
  display.drawLine(ox, oy - 1, x, y - 1, SSD1306_WHITE);
  ox = x;
  oy = y;

  // up until now print sends data to a video buffer NOT the screen
  // this call sends the data to the screen
  display.display();

}
