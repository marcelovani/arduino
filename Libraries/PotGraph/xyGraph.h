#include "Arduino.h"
#include <Adafruit_SSD1306.h>

#ifndef xyGraph_h
#define xyGraph_h

class xyGraph {
  public:
    double _x, _y;

    xyGraph(void);

    void draw(Adafruit_SSD1306 &screen, int value);

    /*
      function to draw a cartesian coordinate system and plot whatever data you want
      just pass x and y and the graph will be drawn huge arguement list
    
      &display to pass the display object, mainly used if multiple displays are connected to the MCU
      x = x data point
      y = y datapont
      gx = x graph location (lower left)
      gy = y graph location (lower left)
      w = width of graph
      h = height of graph
      xlo = lower bound of x axis
      xhi = upper bound of x asis
      xinc = division of x axis (distance not count)
      ylo = lower bound of y axis
      yhi = upper bound of y asis
      yinc = division of y axis (distance not count)
      title = title of graph
      &redraw = flag to redraw graph on fist call only
    */
    void drawCGraph(Adafruit_SSD1306 &display, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, double dig, String title, boolean &Redraw);

  private:
    uint8_t _w;
    uint8_t _h;
    double _ox, _oy;
    
    bool _redraw = true;
    bool _drawing = false;
};

#endif
