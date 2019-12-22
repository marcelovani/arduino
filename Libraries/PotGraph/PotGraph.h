#include "Arduino.h"
#include <Adafruit_SSD1306.h>
#include "Pot.h"
#include "config.h"

#ifndef PotGraph_h
#define PotGraph_h

const int8_t PotGraphTypeDial = 0x1;
const int8_t PotGraphTypeChartV = 0x2;
const int8_t PotGraphTypeChartH = 0x3;

class PotGraph {
  public:
    double _x, _y;

    PotGraph(void);

    void draw(Adafruit_SSD1306 &screen, Pot &pot);

    /*
      This method will draw a dial-type graph for single input
      it has a rather large arguement list and is as follows
    
      &display to pass the display object, mainly used if multiple displays are connected to the MCU
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
    void drawDial(Adafruit_SSD1306 &display, double curval, int cx, int cy, int r, double loval , double hival , double inc, double dig, double sa, String label, bool &Redraw);

  private:
    uint8_t _w;
    uint8_t _h;
    double _ox, _oy;
    
    bool _redraw = true;
    bool _drawing = false;
    int8_t _id;
};

#endif
