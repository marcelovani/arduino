
#include "Arduino.h"
#include <SPI.h>
#include "MAX7219_Digits.h"

/***************************************************************************************************************************/
/*
  Constructor
*/
/***************************************************************************************************************************/
MAX7219_Digit::MAX7219_Digit(int Pin) {

  // Set load pin to output
  pinMode(Pin, OUTPUT);
  _Pin = Pin;

  // Reverse the SPI transfer to send the MSB first
  SPI.setBitOrder(MSBFIRST);

  // Start SPI, SPI slow on ESP8266 https://github.com/esp8266/Arduino/issues/2624
  SPI.begin();

#if defined(__AVR_ATmega168__) ||defined(__AVR_ATmega168P__) ||defined(__AVR_ATmega328P__)
  Serial.println("Hello UNO");
#else
  Serial.println("Hello ESP8266");
  SPI.setFrequency(15000000L);    // Only needed for ESP8266, does not work with UNO
#endif


} // end of function


/***************************************************************************************************************************/
/*
  Write data to MAX7219
*/
/***************************************************************************************************************************/
void MAX7219_Digit::MAX7219_Write(uint8_t Address, uint8_t Data) {

  // Serial.print(Address); Serial.print("  "); Serial.println(Data);

  digitalWrite(_Pin, LOW);  // Take CS Low

  SPI.transfer(Address);    // Send the register address
  SPI.transfer(Data);    // Send the value

  digitalWrite(_Pin, HIGH);  // Take CS High

} // end Function


/***************************************************************************************************************************/
/*
  Begin and initialize all MAX chips
*/
/***************************************************************************************************************************/
void MAX7219_Digit::Begin() {

  // Initialize all MAX7219 chips
  MAX7219_Write(MAX7219_DecodeMode, 0x00);
  MAX7219_Write(MAX7219_Intensity, 0x08);
  MAX7219_Write(MAX7219_ScanLimit, 0x07);
  MAX7219_Write(MAX7219_Displaytest, 0x00);
  MAX7219_Write(MAX7219_Shutdown, 0x01);
  // Clear display
  Clear();

} // end of function


/***************************************************************************************************************************/
/*
  Clear display
*/
/***************************************************************************************************************************/
void MAX7219_Digit::Clear() {

  // Loop through the display registers and write 0x00
  for (int ii = 1; ii < 9; ii++) {
    MAX7219_Write(ii, 0x00);
  } // end of loop

} // end of function


/***************************************************************************************************************************/
/*
  Set brightness
*/
/***************************************************************************************************************************/
void MAX7219_Digit::Brightness(int ii) {

  // Range check the brightness value
  if (ii > -1 && ii < 16) {
    MAX7219_Write(MAX7219_Intensity, ii);
  } // end of range check
} // end of function


/***************************************************************************************************************************/
/*
  Write a text message to the display, either line 1 or 2. Options = Line number, Char1 (left), Char2, Char3, Char4 (right),
*/
/***************************************************************************************************************************/
void MAX7219_Digit::Display_Text(int Display_Num, int Char_1, int Char_2, int Char_3, int Char_4, int dec_p) {

  // make an array of the display data
  int Disp_Val[] = {Char_1, Char_2, Char_3, Char_4};

  // Find the first digit register
  int Start_Digit = 1;
  if (Display_Num != 1) {
    Start_Digit = 5;
  } // end of first digit search

  for (int tt = 0; tt < 4; tt++) {
    int a = pgm_read_byte(&Char_Set[Disp_Val[tt]]);

    // test for decimal point
    if (bitRead(dec_p, tt) > 0) {
      a = a + 128;
    }

    // write the display data and incrument ready for the next
    MAX7219_Write(Start_Digit, a); Start_Digit++;

  } // end

} //end of function


/***************************************************************************************************************************/
/*
  Write a numeric message to the display, either line 1 or 2. Options = Line number, Value, Decimal places, Suffix Character
*/
/***************************************************************************************************************************/
void MAX7219_Digit::Display_Value(int Display_Num, double Display_Value, int Display_DecP, int Suffix) {

  // Mkae s string of the value with x number of decimal places
  String Display_String  =  String(Display_Value, Display_DecP);

  // Test suffix character required if so pad the end with a space
  if (Suffix > 0) {
    Display_String = Display_String + " ";
  }

  // Padd the message to 6 characters
  int Padding = 6 - Display_String.length();
  // Pad the message to 6 characters
  for (int a = 0; a < Padding; a++) {
    Display_String = " " + Display_String;
  }

  // Test for overrange
  // Test either digit 0 (numbers with a D.p.) or 1 (Without D.p.)
  int Overrange = 0;
  int a = 1;
  if (Display_DecP > 0) {
    a = 0;
  }
  if (Display_String.charAt(a) != 0x20) {

    Overrange = 1;  // Set overrange flag

  } // end of overrange test

  // Write to display
  // Start by finding the first digit, line 1 or 2
  int Start_Digit = 8;
  if (Display_Num != 2) {

    Start_Digit = 4;

  } // end of first digit search

  int Display_End = Start_Digit - 4;

  // Loop through the message
  for (int a = 5; a >= 0; a--) {
    // test if suffix present
    if (Suffix > 0 && a == 5) {

      // Display the suffix character
      MAX7219_Write(Start_Digit, pgm_read_byte(&Char_Set[Suffix]));
      Start_Digit--; // next digit to the left
    } // end of suffix test

    // Suffix finished or not required
    else {

      int b = Display_String.charAt(a); // Get the asscii value at the location a

      // Decimal point test
      // If character not a '.' then update display
      if (b != 0x2E) {

        // test for space
        int z = 0x00; // Blank for display

        // If not a space
        if (b != 0x20) {
          z = pgm_read_byte(&Char_Set[b - 48]);
          //      Serial.println(z);

          if (Display_String.charAt(a + 1) == 0x2E) {
            //          Serial.println("DP FOUND");
            z = z + 128;
          }

        } // end of space test

        // Test for and add a minus sign
        if (b == 0x2D) {
          z = 0x01; // Light up the G
        }

        // Remember this loops 6 times, below test to make sure you don't write to other registers!
        if (Start_Digit > Display_End) {

          if (Overrange == 0) {
            MAX7219_Write(Start_Digit, z);
          }
          else {
            MAX7219_Write(Start_Digit, 0x01); // Display a dash for over range
          }
          //Serial.println(Start_Digit);
        }

        Start_Digit--; // next digit to the left

      } // end of not '.' test

    } // end of no suffix required

  } // Finished writting the message

} // end of function


/***************************************************************************************************************************/
/*
  Write a clock with or without colon
*/
/***************************************************************************************************************************/
void MAX7219_Digit::Clock_Display(int Display_Num, String value, int colon, int colon_id) {

  // blank colon if not required (flashing)
  if (bitRead(colon, 0) == 0) {
    colon_id = 0;
  }

  // pad the string if before 10:00am
  if (value.length() == 3) {
    value = "*" + value;
  }

  // test if message length ok
  if (value.length() == 4) {

    // Find the first digit register
    int Start_Digit = 1;
    if (Display_Num != 1) {
      Start_Digit = 5;
    } // end of first digit search

    // make an array of the clock value message
    char value_array[4];
    value.toCharArray(value_array, (value.length() + 1));

    for (int zz = 0; zz < 4; zz++) {

      int a = (value_array[zz] - 0x30);

      // if first digit not valid (i.e. time before 10:00am) blank the digit
      if (a > -1) {
        a = pgm_read_byte(&Char_Set[a]);
      }
      else {
        a = 0;
      }

      // add the decimal point or colon
      if (bitRead(colon_id, zz) > 0) {
        a = a + 128;
      }

      MAX7219_Write(Start_Digit, a); Start_Digit++;

    } // end of display update

  } // end of range check

} // end of function



