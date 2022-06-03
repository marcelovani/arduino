#include "Arduino.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

#ifndef PotGraph_h
#define PotGraph_h

#define PotGraphTypeDial 0x1
#define PotGraphTypeChartV 0x2
#define PotGraphTypeChartH 0x3

class PotGraph {
  public:
    double _x, _y;

    PotGraph(void);

    PotGraph(short int type, int8_t pin, int max, String label);

    bool attach(Adafruit_SSD1306 &screen);

    void clear(Adafruit_SSD1306 &screen);

    void splash(Adafruit_SSD1306 &screen);

    int read();

    // Check if potentiometer is being moved
    bool knobMoving();

    void draw(Adafruit_SSD1306 &screen);

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

    /*
      This method will draw a vertical bar graph for single input
      it has a rather large arguement list and is as follows
    
      &d to pass the display object, mainly used if multiple displays are connected to the MCU
      curval = date to graph (must be between loval and hival)
      x = position of bar graph (lower left of bar)
      y = position of bar (lower left of bar
      w = width of bar graph
      h =  height of bar graph (does not need to be the same as the max scale)
      loval = lower value of the scale (can be negative)
      hival = upper value of the scale
      inc = scale division between loval and hival
      dig = format control to set number of digits to display. (not includeing the decimal)
      label = bottom lable text for the graph
      redraw = flag to redraw display. only on first pass (to reduce flickering)
    */
    void drawBarChartV(Adafruit_SSD1306 &display, double curval, double x , double y , double w, double h , double loval , double hival , double inc , double dig, String label, bool &Redraw);
    
    /*
      This method will draw a horizontal bar graph for single input
      it has a rather large arguement list and is as follows
    
      &display to pass the display object, mainly used if multiple displays are connected to the MCU
      x = position of bar graph (upper left of bar)
      curval = date to graph (must be between loval and hival)
      y = position of bar (upper left of bar (add some vale to leave room for label)
      w = width of bar graph (does not need to be the same as the max scale)
      h =  height of bar graph
      loval = lower value of the scale (can be negative)
      hival = upper value of the scale
      inc = scale division between loval and hival
      dig = format control to set number of digits to display. (not includeing the decimal)
      label = bottom lable text for the graph
      redraw = flag to redraw display. only on first pass (to reduce flickering)
    */
    void drawBarChartH(Adafruit_SSD1306 &display, double curval, double x , double y , double w, double h , double loval , double hival , double inc , double dig, String label, bool &Redraw);

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
    bool _attached = false;

    //int8_t rst_pin; // Normally -1 for shared or A4, etc
    uint8_t _w;
    uint8_t _h;
    //uint8_t _addr;
    //short int _type;
    double _ox, _oy;

    bool _redraw = true;
    bool _drawing = false;
    short int _type;
    int8_t _pin;
    int _max;
    String _label;
    short int _value;
    int _prevValue=-9999;
    int _moveStart;
    int _timer;
};

#endif
