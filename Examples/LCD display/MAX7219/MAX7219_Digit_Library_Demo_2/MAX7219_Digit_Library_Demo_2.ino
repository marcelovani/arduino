
/***************************************************************************************************************************/
/*
      Pin connections
      Name      Arduino     ESP8266         MAX7219 7 Segment display
      -----     -------     -------         -------------------------
                +5V         5V              VCC
                GND         GND             GND
      DIN       D11/MOSI    GPIO13 (D7)     DIN
      CS        *D10/SS      *GPIO15 (D8)    CS
      CLK       D13/SCK     GPIO14 (D5)     CLK
*/
/***************************************************************************************************************************/

#include <SPI.h>
//#include <ESP8266WiFi.h>                    // Needed for EPS8266
//#include <WiFiClient.h>               // WiFi client

#include <MAX7219_Digits.h>

MAX7219_Digit My_Display(10);  // Make an instance of MAX7219_Digit called My_Display and set CS pin

void setup() {

  Serial.begin(115200);

  My_Display.Begin();   // Set's all the registers and clears the display
  delay(1000);
  Serial.println("Setup");
  My_Display.Brightness(8);   // Set brightness

  for (int ii = 1; ii < 9; ii++) {
    delay(1000);
    My_Display.MAX7219_Write(ii, 0x01);
  } // end of loop
  Serial.println("Setup end");
  
} // end of setup




void loop() {
/*
  Serial.println("1");
  delay(1000);
  //My_Display.Display_Text(2, 0x0A, 0x0B, 0x0C, 0x0D, 0b1111); //            Select top or bottom display and display the numbers for digits 1-4
  
  Serial.println("2");
  delay(1000);
  My_Display.Display_Text(1, 0b01000011, 0x02, 0x03, 0x04, 0b1111);

  Serial.println("128");
  delay(1000);
  My_Display.MAX7219_Write(7, 128);

  Serial.println("64");
  delay(1000);
  My_Display.MAX7219_Write(7, 64);

  Serial.println("32");
  delay(1000);
  My_Display.MAX7219_Write(7, 32);

  Serial.println("16");
  delay(1000);
  My_Display.MAX7219_Write(7, 16);

  Serial.println("0");
  delay(1000);
  My_Display.MAX7219_Write(7, 0);

  Serial.println("Display value");
  delay(1000);
  //My_Display.Display_Value(2, 1, 1, 0x01);

  //My_Display.Clear();
    for (int ii = 1; ii < 9; ii++) {
      delay(10);
    My_Display.MAX7219_Write(ii, 0x01);
  } // end of loop

/*
 * 
 */
/*
  for (int f = 0; f < 1000; f++) {
    My_Display.Display_Value(1, (0 - f), 0, 0x00);
    My_Display.Display_Value(2, f, 0, 0x00);
    delay(10);
  }
*/
    
//  for (int f = 0; f < 1000; f++) {
//    My_Display.Display_Value(1, (0 - f), 0, 0x01);
//
//    float g = f/3.1515926;
//    //Serial.println(g);
//    My_Display.Display_Value(2, g, 1, 0x11);
//    delay(10);
//  }



} // end of loop
