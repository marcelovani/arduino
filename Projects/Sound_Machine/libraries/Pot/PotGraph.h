/*
  LCD driver for OLED Diplay

  This program provides functions to draw:
  1. horizontal bar graph
  2. vertical bar graph
  3. dial
  4. cartesian graph

  It requires an microcrontrioller Arduino, teensy and a 0.96 display (1306 driver chip)

  display. sources
  https://www.amazon.com/Diymall-Yellow-Arduino-display.-Raspberry/dp/B00O2LLT30/ref=pd_lpo_vtph_147_bs_t_1?_encoding=UTF8&psc=1&refRID=BQAPE07SVJQNDKEVMTQZ
  https://www.amazon.com/dp/B06XRCQZRX/ref=sspa_dk_detail_0?psc=1&pd_rd_i=B06XRCQZRX&pd_rd_wg=aGuhK&pd_rd_r=1WJPXAG68XFSADGDPNZR&pd_rd_w=DAAsB

  Adafruit libraries
  https://github.com/adafruit/Adafruit-GFX-Library/archive/master.zip
  https://github.com/adafruit/Adafruit_SSD1306

  Revisions
  rev     date        author      description
  1       12-5-2017   kasprzak    Initial creation
  2       11-09-2019  marcelovani Rewrite as a library

  Pin settings:
  Arduino   LCD
  5V        Vin
  GND       GND
  A4        SDA on the display. or use dedicated pin on board if provided
  A5        SCL on the display. use dedicated pin on board if provided
*/

#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

#ifndef PotGraph_h
#define PotGraph_h

#define PotGraphTypeDial 0x1
#define PotGraphTypeChartV 0x2
#define PotGraphTypeChartH 0x3

class PotGraph
{
  public:
    PotGraph(void);
    bool PotGraph::begin(Adafruit_SSD1306 &display);

    void PotGraph::clearDisplay();

    /*
      Constructor
    */
    //PotGraph(Adafruit_SSD1306 display, uint8_t addr=0x3C,short int type=PotGraphTypeDial);
    //PotGraph(Adafruit_SSD1306 display, uint8_t addr=0x3C,short int type=PotGraphTypeDial);

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

//    void display(int value);
    
    short int getType();
    
    //Adafruit_SSD1306 _display;
    bool _redraw;
    double _x, _y;

  private:
    bool _initialized=false;
    int8_t _rst_pin; // Normally -1 for shared or A4, etc
    uint8_t _w;
    uint8_t _h;
    uint8_t _addr;
    short int _type;
    double _ox, _oy;
};

#endif
